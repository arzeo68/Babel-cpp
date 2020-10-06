/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <iostream>
#include <boost/bind.hpp>
#include "Client.hpp"
#include "server/src/Router/Router.hpp"

Server::Network::Client::Client(boost::asio::io_service &service,
                                Server::Database::Database &database,
                                Server::Router &router,
                                Network *network,
                                Common::Log::Log &logger)
    :
    _socket(std::make_shared <boost::asio::ip::tcp::socket>(service)),
    _database(database),
    _router(router),
    _network_parent(network),
    _logger(logger),
    _service(service) {
    this->_logger.Debug("Client constructor, ptr: ", this);
}

Server::Network::Client::SharedPtrSocket_t
Server::Network::Client::GetSocket() {
    return (this->_socket);
}


void Server::Network::Client::StartRead() {
    std::shared_ptr<MessageArr_t> message = std::make_shared<MessageArr_t>();

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
                                   const std::shared_ptr<MessageArr_t>& message) {
    if (error) {
        this->_logger.Error("[client] read: ", error.message());
        this->_network_parent->RemoveClient(this);
        throw InternalError(error);
    }
    this->_logger.Debug("Bytes transferred: ",
                        std::to_string(bytes_transferred), " - ", std::to_string(sizeof(Common::PackageServer)));
    if (bytes_transferred != sizeof(Common::PackageServer)) {
        this->Write(Common::Response {
            Common::HTTPCodes_e::FORBIDDEN,
            "Forbidden"
        });
    } else {
        auto protocol = Server::Router::FormatRouteArgs(
            std::string(message->begin(), message->end()));
        auto response = this->_router.Execute(protocol,
                                              Server::Router::SplitRawData(
                                                  protocol),
                                              *this);
        this->Write(response);
    }
    this->StartRead();
}

void Server::Network::Client::Write(const Common::Response &response) {
    std::vector <boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&response, sizeof(response)));
    this->_socket->async_send(buffers,
                              [this](const boost::system::error_code &error,
                                     std::size_t) {
                                  if (error) {
                                      std::cerr << "write " << error.message()
                                                << std::endl;
                                      this->_network_parent->RemoveClient(this);
                                  }
                              });
}

Server::Database::Database &Server::Network::Client::GetDatabase() {
    return (this->_database);
}

Server::Network::Client::~Client() {
    this->_logger.Debug(this, " [->|client] destructor called");
}

void Server::Network::Client::Shutdown() {
    if (this->_socket->is_open()) {
        boost::system::error_code ec;
        this->_socket->shutdown(
            boost::asio::socket_base::shutdown_type::shutdown_both, ec);
        if (ec)
            this->_logger.Error("Remove close: ", ec.message());
        this->_socket->cancel(ec);
        if (ec)
            this->_logger.Error("Remove cancel: ", ec.message());
        this->_socket->close(ec);
        if (ec)
            this->_logger.Error("Remove close: ", ec.message());
        this->_logger.Debug(this, " socket successfully closed");
    } else
        this->_logger.Debug(this, " socket already closed");
}

Server::Network::Network *Server::Network::Client::GetNetwork() {
    return (this->_network_parent);
}

Server::Network::Client::Client(Server::Network::Client &obj) :
    Client(obj._service, obj._database, obj._router, obj._network_parent,
           obj._logger) {
    this->_logger.Debug("COPY constructor, ptr: ", this);
}
