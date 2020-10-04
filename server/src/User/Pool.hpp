/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_POOL_HPP
#define BABEL_POOL_HPP

#include <map>
#include <memory>
#include "server/src/Network/Client.hpp"

namespace Server::User {
    class Pool {
        public:
        Pool() = default;

        ~Pool() = default;

        uint32_t AddClient(const std::shared_ptr<Network::Client> &client);

        void RemoveClient(uint32_t id);

        private:
        std::map<uint32_t, std::shared_ptr<Network::Client>> _pool;
    };
    namespace Exception {
        class NoMoreSpace : public std::exception {
            public:
            NoMoreSpace() = default;

            const char *what() const noexcept override;
        };
    }
}


#endif //BABEL_POOL_HPP
