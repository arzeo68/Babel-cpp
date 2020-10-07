/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main file for the server part
*/

#include <iostream>
#include "Server.hpp"
#include "server/src/DB/Database.hpp"

int main (const int ac, const char **av) {
    uint32_t port = 4242;
    if (ac != 1)
        port = std::stoi(av[1], nullptr);

    try {
        Server::Server server(port);
        server.Run();
    } catch (const Server::Database::Exception::Query &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
