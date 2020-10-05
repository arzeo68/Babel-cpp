/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Pool.hpp"

uint32_t
Server::User::Pool::AddClient(const std::shared_ptr<Network::Client> &client) {
    uint32_t id = 0;
    while (id < UINT32_MAX) {
        if (this->_pool.count(id) == 0) {
            this->_pool[id] = client;
            return (id);
        }
        id++;
    }
    throw Exception::NoMoreSpace();
}

void Server::User::Pool::RemoveClient(const Server::Network::Client *client) {
    for (auto &i: this->_pool) {
        if (i.second.get() == client) {
            this->_pool.erase(i.first);
            return;
        }
    }
}

const char *Server::User::Exception::NoMoreSpace::what() const noexcept {
    return ("No more space for user available, please retry later");
}
