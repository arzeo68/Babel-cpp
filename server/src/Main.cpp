/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Network/Network.hpp"

int main (const int ac, const char **av) {
    setvbuf(stdout, nullptr, _IONBF, 0); // TODO: Remove be removed for the final version
    uint32_t port = 4242;
    if (ac != 1)
        port = std::stoi(av[0], nullptr);
    Server::Network::Network c(port);
    printf("Launching server...\n");
    c.Run();
    printf("Server exited gracefully.\n");
    return (0);
}
