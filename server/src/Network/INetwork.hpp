/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_BABEL_INETWORK_
#define SRC_BABEL_INETWORK_

#include <memory>
#include <cstdint>

namespace Server::Network {
    class Client;

    class INetwork {
        public:
        virtual ~INetwork() = default;
        virtual void Run() = 0;
        virtual void Stop() = 0;
        virtual uint32_t
        AddUserToPool(const std::shared_ptr<Client> &) = 0;
        virtual void RemoveUserFromPool(const Client *) = 0;
        virtual void RemoveClient(const Client *) = 0;

    };
}

#endif
