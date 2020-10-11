/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
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

    class Network
        : public std::enable_shared_from_this<Network>, public ANetwork {
        public:

        explicit Network(uint32_t port,
                         const std::shared_ptr<Common::Log::Log> &logger);

        ~Network() override = default;
        Network(const Network &network) = delete;

        void Run() override;
        void PreRun();
        void Stop() override;
        void RemoveClient(const std::shared_ptr<Client> &client) override;
        bool IsUserConnected(const std::string &name);
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
