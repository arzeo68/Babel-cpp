/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include <boost/asio/error.hpp>
#include "server/src/Router/Router.hpp"
#include "Network.hpp"
#include "Client.hpp"
#include "../User/Pool.hpp"


Server::Network::Network::Network(uint32_t port, Common::Log::Log& logger) :
    _acceptor(_service,
              boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    _signalSet(_service, SIGINT),
    _database(logger),
    _logger(logger) {
    this->_router = std::make_shared <Server::Router>();
    this->_pool = std::make_shared<Server::User::Pool>();
}

void Server::Network::Network::Run() {
    this->_is_running = true;
    this->_signalSet.async_wait(
        [self = shared_from_this()](const boost::system::error_code &error,
                                    int /*signal*/) {
            if (error)
                std::cerr << "Error during catching signals: " << error
                          << std::endl;
            if (self->_is_running)
                self->Stop();
        });
    try {
        SharedPtrClient_t client = std::make_shared <Client>(this->_service,
                                                             this->_database,
                                                             *this->_router,
                                                             this,
                                                             this->_logger);
        this->_clients.emplace_back(client);
        this->_logger.Debug(client.get(), " - Waiting for new client on ",
                            this->_acceptor.local_endpoint().port(), "...");
        this->_acceptor.async_accept(*client->GetSocket(),
                                     [self = this->shared_from_this(), client](
                                         const boost::system::error_code &err) {
                                         self->AcceptClient(err, client);
                                     });
        this->_service.run();
    }
    catch (const InternalError &e) {
        auto errorCode = e.GetError();
        if (errorCode != boost::asio::error::eof &&
            errorCode != boost::asio::error::operation_aborted)
            this->_logger.Error(e.what());
    }
    catch (const std::exception &e) {
        this->_logger.Error("Fatal error occurred: ", e.what());
        this->Stop();
    }
}

void
Server::Network::Network::AcceptClient(const boost::system::error_code &error,
                                       SharedPtrClient_t client) {
    if (error) {
        this->_logger.Error("Err accept client: ", error.message());
        throw InternalError(error);
    }
    this->_logger.Info(client.get(), " - Incoming connection from: ",
                       client->GetSocket()->remote_endpoint().address().to_string());
    client->GetUserData().SetUserIp(client->GetSocket()->remote_endpoint().address().to_string());
    client->StartRead();
    this->Run();
}

void Server::Network::Network::Stop() {
    if (!this->_is_running)
        return;
    this->_mutex.lock();
    this->_logger.Info("Server start to shut down.");
    this->_logger.Info("Stopping all services...");
    this->_is_running = false;
    if (this->_acceptor.is_open())
        this->_acceptor.close();
    this->_service.stop();
    this->_service.reset();
    this->_logger.Info("Closing all sockets...");
    for (auto &i : this->_clients) {
        i->Shutdown();
    }
    this->_clients.clear();
    this->_mutex.unlock();
    this->_logger.Info("Server stopped!");
}

uint32_t
Server::Network::Network::AddUserToPool(const std::shared_ptr<Client> &client) {
    if (!this->_mutex.try_lock())
        throw std::exception();
    uint32_t id = this->_pool->AddClient(client);
    this->_mutex.unlock();
    return (id);
}

void Server::Network::Network::RemoveUserFromPool(const Client *client) {
    this->_pool->RemoveClient(client);
}

void Server::Network::Network::RemoveClient(const Client *client) {
    this->_mutex.lock();
    for (auto &i : this->_clients)
        if (i.get() == client) {
            i->Shutdown();
            this->RemoveUserFromPool(client);
            this->_clients.remove(i);
            this->_mutex.unlock();
            return;
        }
    this->_mutex.unlock();
}
