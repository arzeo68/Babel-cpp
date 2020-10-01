/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <iostream>
#include <boost/bind.hpp>
#include "Client.hpp"
#include "server/src/API/Route/Data/Data.hpp"

Server::Network::Client::Client(boost::asio::io_service &service,
                                Server::Database::Database& database) : _database(database) {
    this->_socket = Network::SharedPtrSocket_t(
        std::make_shared<boost::asio::ip::tcp::socket>(service));
}

Server::Network::Network::SharedPtrSocket_t
Server::Network::Client::GetSocket() {
    return (this->_socket);
}


void Server::Network::Client::StartRead() {
    Network::SharedPtrMessageArr_t message = std::make_shared<Network::MessageArr_t>();

    this->_socket->async_receive(boost::asio::buffer(*message),
                                 [this, message](
                                     const boost::system::error_code &err,
                                     std::size_t bytes_transferred) {
                                     this->Read(err, bytes_transferred,
                                                message);
                                 });
}

void Server::Network::Client::Read(const boost::system::error_code &error,
                                   std::size_t,
                                   Network::SharedPtrMessageArr_t message) {
    //std::cerr << "Bytes transferred: " << std::to_string(bytes_transferred) << std::endl;
    if (error)
        throw InternalError(error);
    std::cout << "text read: '" << std::string(message->begin(), message->end())
              << "'"
              << "from :" << this << std::endl;
    Server::API::Route::Login(*this, {
       .method = Route::GET,
       .body = "user",
       .token = "token"
    });
    this->StartRead();
}

void Server::Network::Client::Write(const std::string &message) {
    this->_socket->async_send(boost::asio::buffer(message),
                              [](const boost::system::error_code &error,
                                 std::size_t) {
                                  if (error)
                                      throw InternalError(error);
                              });
}

Server::Database::Database &Server::Network::Client::GetDatabase() {
    return (this->_database);
}
