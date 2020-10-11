/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main class for the binary
*/

#ifndef BABEL_SERVER_HPP
#define BABEL_SERVER_HPP

#include <memory>
#include "common/Log.hpp"
#include "server/src/Network/Network.hpp"

namespace Server {
    /**
     * The class Server start and stop the server and provide a logger. The server must always exit gracefully.
     */
    class Server {
        public:
        /**
         * The port for the network
         * @param port
         */
        explicit Server(uint32_t port);
        /**
         * Defined but it only prints a informative message
         */
        ~Server();
        Server(const Server &obj) = default;

        /**
         * Run the server. The server might be stopped by pressing CTRL+C (or sending SIGINT).
         */
        void Run();

        private:
        std::shared_ptr<Common::Log::Log> _logger;
        std::shared_ptr<Network::Network> _network;
    };
}


#endif //BABEL_SERVER_HPP
