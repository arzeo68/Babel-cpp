/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main file for the server part
*/

#include <server/src/API/Route/Route.hpp>
#include <iostream>
#include "Network/Network.hpp"
#include "server/src/API/Router/Router.hpp"

int main (const int ac, const char **av) {
    setvbuf(stdout, nullptr, _IONBF, 0); // TODO: Remove be removed for the final version
    uint32_t port = 4242;
    if (ac != 1)
        port = std::stoi(av[0], nullptr);

    Common::Log::Log logger("SERVER", "server.log",
                            Common::Log::Log::g_AllLogLevel,
                            std::ios_base::trunc);
    std::shared_ptr <Server::Network::Network> network = std::make_shared<Server::Network::Network>(port, logger);
    logger.Info("Launching server...");
    try {
        network->Run();
    } catch (const Server::Database::Exception::Query &e) {
        logger.Error("Query error? ", e.what());
    }
    logger.Info("Server exited gracefully.");
    return (0);
}
