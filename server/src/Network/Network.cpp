/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include "server/src/API/Router/Router.hpp"
#include "Network.hpp"
#include "Client.hpp"

bool Server::Network::Network::SERVER_RUNNING = false;

Server::Network::Network::Network(unsigned int port) : _acceptor(_service, boost::asio::ip::tcp::endpoint(
    boost::asio::ip::tcp::v4(),
    port)) {
    this->_router = std::make_shared<Server::Router>();
    Server::Network::Network::Start();
}

void Server::Network::Network::Run() {
    while (Server::Network::Network::SERVER_RUNNING) {
        try {
            SharedPtrClient_t client = std::make_shared<Client>(this->_service, this->_database, *this->_router);
            printf("Waiting for new client on %u...\n",
                   this->_acceptor.local_endpoint().port());
            this->_acceptor.async_accept(*client->GetSocket(),
                                         [this, client] (const boost::system::error_code& err) {
                                             this->AcceptClient(err, client);
                                         });
            this->_service.run();
        }
        catch (const InternalError &e) {
            if (e.GetError() != boost::asio::error::eof) {
                std::cout << e.what() << std::endl;
                Server::Network::Network::Stop();
            } else {
                std::cerr << "A client has exited the server" << std::endl;
            }
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            Server::Network::Network::Stop();
        }
    }
}

void
Server::Network::Network::AcceptClient(const boost::system::error_code& error, SharedPtrClient_t client) {
    if (error)
        throw InternalError(error);
    std::cerr << "Incoming connection from: " << client->GetSocket()->remote_endpoint().address().to_string() << std::endl;
    client->StartRead();
    this->Run();
}

void Server::Network::Network::Start() {
    Server::Network::Network::SERVER_RUNNING = true;
}

void Server::Network::Network::Stop() {
    std::cerr << "The server is being shut down..." << std::endl;
    Server::Network::Network::SERVER_RUNNING = false;
    this->_service.stop();
}
