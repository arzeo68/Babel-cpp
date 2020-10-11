/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <iostream>
#include <boost/bind.hpp>
#include <utility>
#include "Client.hpp"
#include "server/src/Router/Router.hpp"
#include "server/src/Network/Worker.hpp"
#include "server/src/Route/List/Utils.hpp"

void Server::Network::Client::Read() {
    std::shared_ptr<MessageArr_t> message = std::make_shared<MessageArr_t>();

    this->_socket->async_receive(boost::asio::buffer(*message),
                                 [self = shared_from_this(), message](
                                     const boost::system::error_code &err,
                                     std::size_t bytes_transferred) {
                                     self->ExecRead(err, bytes_transferred,
                                                    message);
                                 });
}

void Server::Network::Client::ExecRead(const boost::system::error_code &error,
                                       std::size_t bytes_transferred,
                                       const std::shared_ptr<MessageArr_t> &message) {
    if (error) {
        this->_logger->Warning("[client] ExecRead: ", error.message());
        this->_network_parent->RemoveClient(this->shared_from_this());
        throw InternalError<boost::system::error_code>(error);
    }
    this->_logger->Debug("Bytes transferred: ",
                         std::to_string(bytes_transferred), " - ",
                         std::to_string(sizeof(Common::PackageServer)));
    if (bytes_transferred != sizeof(Common::PackageServer)) {
        this->Write(Common::Response {
            Common::HTTPCodes_e::HTTP_FORBIDDEN,
            "Forbidden"
        });
    } else {
        auto protocol = Server::Router::FormatRouteArgs(
            std::string(message->begin(), message->end()));
        auto response = this->_router.Execute(protocol,
                                              Server::Router::SplitRawData(
                                                  protocol),
                                              this->shared_from_this());
        this->Write(response);
    }
    this->Read();
}

void Server::Network::Client::Write(const Common::Response &response) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&response, sizeof(response)));
    this->_socket->async_send(buffers,
                              [this](const boost::system::error_code &error,
                                     std::size_t) {
                                  if (error) {
                                      this->_logger->Error("[client->] write ",
                                                           error.message());
                                      this->_network_parent->RemoveClient(
                                          this->shared_from_this());
                                  }
                              });
}

Server::Database::Database &Server::Network::Client::GetDatabase() {
    return (this->_database);
}

Server::Network::Client::~Client() {
    this->_logger->Debug(this, " [->|client] destructor called");
}

void Server::Network::Client::Shutdown() {
    if (this->_socket->is_open()) {
        if (this->_user.GetCallState() != Common::CallState::NONE)
            if (auto i = this->_network_parent->GetClientFromName(
                this->_user.GetCallerName()))
                Route::Listing::Utils::ChangeStateCall(this->shared_from_this(),
                                                       *i,
                                                       Common::CallState::ENDED);
        Server::Route::Listing::Utils::NotifyUserStatusToFriends(
            this->shared_from_this(),
            Route::Listing::Utils::UserState::DISCONNECTED);
        boost::system::error_code ec;
        this->_socket->shutdown(
            boost::asio::socket_base::shutdown_type::shutdown_both, ec);
        if (ec)
            this->_logger->Error("[client->] Remove close: ", ec.message());
        this->_socket->cancel(ec);
        if (ec)
            this->_logger->Error("[client->] Remove cancel: ", ec.message());
        this->_socket->close(ec);
        if (ec)
            this->_logger->Error("[client->] Remove close: ", ec.message());
        this->_logger->Debug(this, " socket successfully closed");
    } else
        this->_logger->Debug(this, " socket already closed");
}

std::shared_ptr<Server::Network::Network>
Server::Network::Client::GetNetwork() {
    return (this->_network_parent);
}

Server::User::User &Server::Network::Client::GetUserData() {
    return (this->_user);
}

std::shared_ptr<Server::Worker> Server::Network::Client::GetWorker() {
    return (this->_worker->shared_from_this());
}

Server::Network::Client::SharedPtrSocket_t
Server::Network::Client::GetSocket() {
    return (this->_socket);
}
