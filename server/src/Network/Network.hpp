/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main class for the server's network
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <mutex>
#include <optional>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include "INetwork.hpp"
#include "common/TCP/CommonPackages.hpp"
#include "common/Log.hpp"
#include "server/src/DB/Database.hpp"

namespace Server {
    class Router;

    class Worker;
}

namespace Server::Network {
    class Client;

    /**
     * Network is the main class for the whole server's network. It includes client with their socket. The class inherit from ANetwork.
     */
    class Network
        : public std::enable_shared_from_this<Network>, public ANetwork {
        public:

        /**
         * Initialize main structure: boost's acceptor, signal set and database. The database tables are registered in the constructor
         * @param port Port which the network is listening
         * @param logger Shared instance of a logger
         */
        explicit Network(uint32_t port,
                         const std::shared_ptr<Common::Log::Log> &logger);

        ~Network() override = default;
        Network(const Network &network) = delete;

        void Run() override;
        /**
         * PreRun calls setup function for the worker
         */
        void PreRun();
        void Stop() override;
        void RemoveClient(const std::shared_ptr<Client> &client) override;
        /**
         * Check if client is connected to the server
         * @param name Client's name
         * @return true if the client is connected, otherwise returns false
         */
        bool IsUserConnected(const std::string &name);
        /**
         * Get the client shared instance from his name
         * @param name user's name
         * @return A client shared instance
         */
        std::optional<std::shared_ptr<Client>>
        GetClientFromName(const std::string &name);
        std::list<SharedPtrClient_t> GetClients() override;

        private:
        void AcceptClient(const boost::system::error_code &error,
                          SharedPtrClient_t client);

        boost::asio::io_service _service;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::shared_ptr<Server::Router> _router;
        boost::asio::signal_set _signalSet;
        Server::Database::Database _database;
        std::shared_ptr<Common::Log::Log> _logger;
        std::shared_ptr<Worker> _worker;
    };
}


#endif //BABEL_NETWORK_HPP
