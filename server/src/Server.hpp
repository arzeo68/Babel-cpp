/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_SERVER_HPP
#define BABEL_SERVER_HPP

#include <memory>
#include "common/Log.hpp"
#include "server/src/Network/Network.hpp"

namespace Server {
    class Server {
        public:
        explicit Server(uint32_t port);
        ~Server();
        Server(const Server &obj) = default;

        void Run();

        private:
        Common::Log::Log _logger;
        std::shared_ptr<Network::Network<boost::asio::ip::tcp::socket>> _network;
    };
}


#endif //BABEL_SERVER_HPP
