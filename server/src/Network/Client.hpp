/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <memory>
#include <mutex>
#include "Network.hpp"
#include "server/src/DB/Database.hpp"

namespace Server::Network {
    class Client : public std::enable_shared_from_this<Client> {
        public:
        explicit Client(boost::asio::io_service &service,
                        Server::Database::Database &database,
                        Server::Router &router,
                        const std::shared_ptr<Network> &network);

        Network::SharedPtrSocket_t GetSocket();

        //std::string &GetReadBuffer();
        void StartRead();

        void Write(const std::string &message);

        Server::Database::Database &GetDatabase();

        private:
        void Read(const boost::system::error_code &error,
                  std::size_t bytes_transferred,
                  Network::SharedPtrMessageArr_t message);

        Network::SharedPtrSocket_t _socket;
        Server::Database::Database &_database;
        Server::Router &_router;
        std::shared_ptr<Network> _network_parent;
    };

    class InternalError : public std::exception {
        public:
        explicit InternalError(const boost::system::error_code& err);
        ~InternalError() override = default;
        boost::system::error_code GetError() const;

        const char *what() const noexcept override;
        private:
        boost::system::error_code _error;
    };
}


#endif //BABEL_CLIENT_HPP
