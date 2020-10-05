/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <list>
#include <memory>
#include <map>
#include <mutex>
#include "common/Protocol.hpp"
#include "common/Log.hpp"
#include "server/src/DB/Database.hpp"

namespace Server {
    class Router;
    namespace User {
        class Pool;
    }
}

namespace Server::Network {
    class Client;

    class Network : public std::enable_shared_from_this<Network> {
        public:
        typedef std::shared_ptr<Client> SharedPtrClient_t;

        explicit Network(uint32_t port, Common::Log::Log& logger);
        ~Network() = default;

        void Run();
        void Stop();
        uint32_t AddUserToPool(const std::shared_ptr<Client> &client);
        void RemoveUserFromPool(const Client *client);
        void RemoveClient(const Client *client);

        private:
        void AcceptClient(const boost::system::error_code &error,
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
