/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Server.hpp"

Server::Server::Server(uint32_t port) :
    _logger("server", "server.log",
            Common::Log::Log::g_AllLogLevel,
            std::ios_base::trunc),
    _network(std::make_shared<Network::Network>(port, this->_logger)) {
    this->_logger.Info("Launching server...");
}

void Server::Server::Run() {
    try {
        this->_network->Run();
    } catch (const Database::Exception::Query &e) {
        this->_logger.Error("Query error? ", e.what());
    }
}

Server::Server::~Server() {
    this->_logger.Info("Server exited gracefully.");
}
