/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include <boost/asio/error.hpp>
#include <thread>
#include "server/src/Router/Router.hpp"
#include "server/src/DB/Database.hpp"
#include "Network.hpp"
#include "Client.hpp"
#include "../User/Pool.hpp"
#include "Worker.hpp"


Server::Network::Network::Network(uint32_t port,
                                  std::shared_ptr<Common::Log::Log> logger) :
    _acceptor(_service,
              boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    _signalSet(_service, SIGINT),
    _database(logger->shared_from_this()),
    _logger(logger) {
    this->_database.RegisterTables();
    this->_router = std::make_shared<Server::Router>();
    this->_pool = std::make_shared<Server::User::Pool>();
    this->_worker = std::make_shared<Server::Worker>(this->_mutex,
                                                     this->_logger->shared_from_this());
}

void Server::Network::Network::Run() {
    this->_is_running = true;

    this->_signalSet.async_wait(
        [self = this->shared_from_this()](
            const boost::system::error_code &error,
            int /*signal*/) {
            if (error)
                std::cerr << "Error during catching signals: " << error
                          << std::endl;
            if (self->_is_running)
                self->Stop();
        });
    try {
        SharedPtrClient_t client = std::make_shared<Client>(this->_database,
                                                            *this->_router,
                                                            this->shared_from_this(),
                                                            this->_logger->shared_from_this(),
                                                            this->_service,
                                                            this->_worker->shared_from_this());
        this->_clients.emplace_back(client);
        this->_logger->Debug(client.get(), " - Waiting for new client on ",
                             this->_acceptor.local_endpoint().port(), "...");
        this->_acceptor.async_accept(*client->GetSocket(),
                                     [self = this->shared_from_this(), client](
                                         const boost::system::error_code &err) {
                                         self->AcceptClient(err, client);
                                     });
        this->_service.run();
    }
    catch (const InternalError<boost::system::error_code> &e) {
        auto errorCode = e.GetError();
        if (errorCode != boost::asio::error::eof &&
            errorCode != boost::asio::error::operation_aborted)
            this->_logger->Error(e.what());
    }
    catch (const std::exception &e) {
        this->_logger->Error("Fatal error occurred: ", e.what());
        this->Stop();
    }
}

void Server::Network::Network::AcceptClient(
    const boost::system::error_code &error,
    SharedPtrClient_t client) {
    if (error) {
        this->_logger->Error("Err accept client: ", error.message());
        throw InternalError(error);
    }
    this->_logger->Info(client.get(), " - Incoming connection from: ",
                        client->GetSocket()->remote_endpoint().address().to_string());
    client->GetUserData().SetUserIp(
        client->GetSocket()->remote_endpoint().address().to_string());
    client->Read();
    this->Run();
}

void Server::Network::Network::Stop() {
    if (!this->_is_running)
        return;
    this->_logger->Info("Server start to shut down.");
    this->_logger->Info("Stopping all services...");
    this->_worker->Stop();
    this->_is_running = false;
    if (this->_acceptor.is_open())
        this->_acceptor.close();
    this->_service.stop();
    this->_service.reset();
    this->_logger->Info("Closing all sockets...");
    for (auto &i : this->_clients) {
        i->Shutdown();
    }
    this->_clients.clear();
    this->_logger->Info("Server stopped!");
}

uint32_t Server::Network::Network::AddUserToPool(
    const std::shared_ptr<Client> &client) {
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

void Server::Network::Network::PreRun() {
    this->_logger->Debug("Pre-run launched");
    this->_worker->SetNetwork(this->shared_from_this());
}

bool Server::Network::Network::IsUserConnected(const std::string &name) {
    bool locked = this->_mutex.try_lock();
    auto find = std::find_if(this->_clients.begin(), this->_clients.end(),
                             [&name](const std::shared_ptr<Client> &client) {
                                 return (client->GetUserData().GetName() ==
                                         name);
                             });
    if (locked)
        this->_mutex.unlock();
    return (find != this->_clients.end());
}

std::optional<std::shared_ptr<Server::Network::Client>>
Server::Network::Network::GetClientFromName(const std::string &name) {
    bool locked = this->_mutex.try_lock();
    auto find = std::find_if(this->_clients.begin(), this->_clients.end(),
                             [&name](const std::shared_ptr<Client> &client) {
                                 return (client->GetUserData().GetName() ==
                                         name);
                             });
    if (locked)
        this->_mutex.unlock();
    return (find != this->_clients.end()
            ? std::optional<std::shared_ptr<Client>> {*find} : std::nullopt);
}
std::list<Server::Network::Network::SharedPtrClient_t> &
Server::Network::Network::GetClients() {
    return (this->_clients);
}

