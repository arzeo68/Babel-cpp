/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include <boost/asio/error.hpp>
#include "server/src/API/Router/Router.hpp"
#include "Network.hpp"
#include "Client.hpp"
#include "../User/Pool.hpp"

bool Server::Network::Network::SERVER_RUNNING = false;

Server::Network::Network::Network(unsigned int port) : _acceptor(_service,
                                                                 boost::asio::ip::tcp::endpoint(
                                                                     boost::asio::ip::tcp::v4(),
                                                                     port)),
                                                                     _signalSet(_service, SIGINT, SIGTERM){
    this->_router = std::make_shared<Server::Router>();
    //this->_pool = std::make_shared<Server::User::Pool>();
    Server::Network::Network::Start();
}

void Server::Network::Network::Run() {
    this->_signalSet.async_wait([self = shared_from_this()] (const boost::system::error_code& error, int signal)  {
        printf("Catch signal: %i\n", signal);
        if (error)
           std::cerr << "Error during catching signals: " << error << std::endl;
        if (Server::Network::Network::SERVER_RUNNING)
            self->Stop();
    });
    while (Server::Network::Network::SERVER_RUNNING) {
        try {
            SharedPtrClient_t client = std::make_shared<Client>(this->_service,
                                                                this->_database,
                                                                *this->_router,
                                                                this->shared_from_this());
            this->_clients.emplace_back(client);
            printf("Client list size: %zu\n", this->_clients.size());
            printf("%p - Waiting for new client on %u...\n", client.get(),
                   this->_acceptor.local_endpoint().port());
            this->_acceptor.async_accept(*client->GetSocket(),
                                         [self = this->shared_from_this(), client](
                                             const boost::system::error_code &err) {
                                             std::cout << "start lambda" << std::endl;
                                             self->AcceptClient(err, client);
                                             std::cout << "end lambda" << std::endl;
                                         });
            this->_service.run();
        }
        catch (const InternalError &e) {
            auto errorCode = e.GetError();
            if (errorCode == boost::asio::error::eof) {
                std::cerr << "A client has exited the server" << std::endl;
            } else if (errorCode == boost::asio::error::operation_aborted) {
                std::cerr << "The server doesn't accept connections anymore"
                          << std::endl;
            } else {
                std::cout << e.what() << std::endl;
                //this->Stop();
            }
        }
        catch (const std::exception &e) {
            std::cout << "Fatal error occurred: " << e.what() << std::endl;
            this->Stop();
        }
    }
}

void
Server::Network::Network::AcceptClient(const boost::system::error_code &error,
                                       SharedPtrClient_t client) {
    if (error)
        throw InternalError(error);
    std::cerr << this << " - Incoming connection from: "
              << client->GetSocket()->remote_endpoint().address().to_string()
              << std::endl;
    client->StartRead();
    //this->Run();
}

void Server::Network::Network::Start() {
    Server::Network::Network::SERVER_RUNNING = true;
}

void Server::Network::Network::Stop() {
    this->_mutex.lock();
    std::cerr << "The server is being shut down..." << std::endl;
    Server::Network::Network::SERVER_RUNNING = false;
    this->_acceptor.cancel();
    this->_service.stop();
    this->_service.reset();
    for (auto &i : this->_clients) {
        boost::system::error_code ec;
        i->GetSocket()->close(ec);
    }
    this->_clients.clear();
    this->_mutex.unlock();
    std::cerr << "Server stopped!" << std::endl;
}

uint32_t
Server::Network::Network::AddUserToPool(const std::shared_ptr<Client> &client) {
    //if (!this->_mutex.try_lock())
        throw std::exception();
    //uint32_t id = this->_pool->AddClient(client);
    //this->_mutex.unlock();
    return (0);
    //return (id);
}

Server::Network::Network::~Network() {
    std::cout << "network dstr is called" << std::endl;
}
