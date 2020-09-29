/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Network/Network.hpp"

int main (__attribute__((unused)) int ac, __attribute__((unused)) char **av) {
    setvbuf(stdout, nullptr, _IONBF, 0);
    Server::Network::Network c(4242);
    printf("Launching connection...\n");
    c.Run();
    printf("SERVER EXIT GRACEFULLY\n");
    return (0);
}
