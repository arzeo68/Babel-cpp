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
    Server::Network::Network network(port);
    printf("Launching server...\n");
    try {
        network.Run();
    } catch (const Server::Database::Exception::Query &e) {
        std::cerr << e.what() << std::endl;
    }
    printf("Server exited gracefully.\n");
    return (0);
}
