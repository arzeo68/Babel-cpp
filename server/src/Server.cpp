/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Server.hpp"

Server::Server::Server(uint32_t port) :
    _logger(std::make_shared<Common::Log::Log>("server", "server.log",
                                               Common::Log::Log::g_AllLogLevel,
                                               std::ios_base::trunc)),
    _network(std::make_shared<Network::Network>(port,
                                                this->_logger->shared_from_this())) {
    this->_logger->Info("Launching server...");
}

void Server::Server::Run() {
    try {
        this->_network->PreRun();
        this->_network->Run();
    } catch (const Database::Exception::Query &e) {
        this->_logger->Error(e.what());
    }
}

Server::Server::~Server() {
    this->_logger->Info("Server exited gracefully.");
}
