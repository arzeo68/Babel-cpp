/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <boost/asio.hpp>
#include <list>
#include <memory>
#include <map>
#include <mutex>
#include "common/Protocol.hpp"
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
        static bool SERVER_RUNNING;
        typedef std::shared_ptr<boost::asio::ip::tcp::socket> SharedPtrSocket_t;
        typedef std::shared_ptr<Client> SharedPtrClient_t;
        typedef std::array<char, sizeof(Common::PackageServer)> MessageArr_t;
        typedef std::shared_ptr<MessageArr_t> SharedPtrMessageArr_t;

        explicit Network(uint32_t port);

        void Run();

        static void Start();

        void Stop();

        uint32_t AddUserToPool(const std::shared_ptr<Client> &client);

        private:
        void AcceptClient(const boost::system::error_code &error,
                          SharedPtrClient_t client);

        boost::asio::io_service _service;
        boost::asio::ip::tcp::acceptor _acceptor;
        //std::list<SharedPtrClient_t> _clients;
        Server::Database::Database _database;
        std::shared_ptr<Server::Router> _router;
        //std::mutex _mutex;
        //std::shared_ptr<User::Pool> _pool;
        //std::map<uint32_t, std::enable_shared_from_this<Network>> _pool; //
    };
}


#endif //BABEL_NETWORK_HPP
