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
#include "server/src/DB/Database.hpp"

namespace Server {
    class Router;
}

namespace Server::Network {
    class Client;
    class Network {
        public:
        static bool SERVER_RUNNING;
        const static constexpr uint16_t MESSAGE_SIZE_LENGTH = 256u;
        typedef std::shared_ptr<boost::asio::ip::tcp::socket> SharedPtrSocket_t;
        typedef std::shared_ptr<Client> SharedPtrClient_t;
        typedef std::array<char, MESSAGE_SIZE_LENGTH> MessageArr_t;
        typedef std::shared_ptr<MessageArr_t> SharedPtrMessageArr_t;

        explicit Network(uint32_t port);

        void Run();
        static void Start();
        void Stop();

        private:
        void AcceptClient(const boost::system::error_code& error, SharedPtrClient_t client);
        boost::asio::io_service _service;
        boost::asio::ip::tcp::acceptor _acceptor;
        //std::list<SharedPtrClient_t> _clients;
        Server::Database::Database _database;
        std::shared_ptr<Server::Router> _router;
    };
}


#endif //BABEL_NETWORK_HPP
