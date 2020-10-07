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
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include "common/TCP/CommonPackages.hpp"
#include "common/Log.hpp"
#include "server/src/DB/Database.hpp"
#include "INetwork.hpp"

namespace Server {
    class Router;
    namespace User {
        class Pool;
    }
}

namespace Server::Network {
    template<typename S>
    class Client;

    template<typename S>
    class Network
        : public std::enable_shared_from_this<Network<S>>, public INetwork<S> {
        public:
        typedef std::shared_ptr<Client<S>> SharedPtrClient_t;

        explicit Network(uint32_t port, Common::Log::Log& logger);
        ~Network() override = default;
        Network(const Network& network) = delete;

        void Run() override;
        void Stop() override;
        uint32_t
        AddUserToPool(const std::shared_ptr<Client<S>>& client) override;
        void RemoveUserFromPool(const Client<S> *client) override;
        void RemoveClient(const Client<S> *client) override;

        private:
        void AcceptClient(const boost::system::error_code& error,
                          SharedPtrClient_t client);

        bool _is_running = false;
        boost::asio::io_service _service;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::list<SharedPtrClient_t> _clients;
        std::shared_ptr<Server::Router> _router;
        boost::asio::signal_set _signalSet;
        Server::Database::Database _database;
        std::mutex _mutex;
        std::shared_ptr<User::Pool> _pool;
        Common::Log::Log& _logger;
    };
}


#endif //BABEL_NETWORK_HPP
