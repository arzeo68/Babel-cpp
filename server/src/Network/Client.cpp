/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <iostream>
#include <boost/bind.hpp>
#include "Client.hpp"
#include "server/src/API/Router/Router.hpp"

Server::Network::Client::Client(boost::asio::io_service &service,
                                Server::Database::Database &database,
                                Server::Router &router,
                                const std::shared_ptr<Network> &network)
    : _database(database),
      _router(router),
      _network_parent(network) {
    this->_socket = Network::SharedPtrSocket_t(
        std::make_shared<boost::asio::ip::tcp::socket>(service));
}

Server::Network::Network::SharedPtrSocket_t
Server::Network::Client::GetSocket() {
    return (this->_socket);
}


void Server::Network::Client::StartRead() {
    Network::SharedPtrMessageArr_t message = std::make_shared <Network::MessageArr_t>();

    this->_socket->async_receive(boost::asio::buffer(*message),
                                 [self = shared_from_this(), message](
                                     const boost::system::error_code &err,
                                     std::size_t bytes_transferred) {
                                     self->Read(err, bytes_transferred,
                                                message);
                                 });
}

void Server::Network::Client::Read(const boost::system::error_code &error,
                                   std::size_t bytes_transferred,
                                   const Network::SharedPtrMessageArr_t& message) {
    std::cerr << "Bytes transferred: " << std::to_string(bytes_transferred) << std::endl;
    if (error)
        throw InternalError(error);
    auto protocol = Server::Router::FormatRouteArgs(
        std::string(message->begin(), message->end()));
    auto response = this->_router.Execute(protocol,
                          Server::Router::SplitRawData(protocol),
                          *this);
    this->Write(response);
    this->StartRead();
}

void Server::Network::Client::Write(const Common::Response& response) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&response, sizeof(response)));
    this->_socket->async_send(buffers,
                              [](const boost::system::error_code &error,
                                 std::size_t) {
                                  if (error)
                                      throw InternalError(error);
                              });
}

Server::Database::Database &Server::Network::Client::GetDatabase() {
    return (this->_database);
}
