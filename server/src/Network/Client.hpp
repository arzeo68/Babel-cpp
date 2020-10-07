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
#include "common/TCP/CommonPackages.hpp"
#include "Network.hpp"
#include "server/src/DB/Database.hpp"
#include "server/src/User/User.hpp"

namespace Server::Network {
    class Client : public std::enable_shared_from_this<Client> {
        public:
        typedef std::shared_ptr<boost::asio::ip::tcp::socket> SharedPtrSocket_t;
        typedef std::array<char, sizeof(Common::PackageServer)> MessageArr_t;

        explicit Client(Server::Database::Database& database,
                        Server::Router& router,
                        Network *network,
                        Common::Log::Log& logger);
        ~Client();
        Client(const Client& obj) = delete;

        SharedPtrSocket_t GetSocket();
        Network* GetNetwork();
        void StartRead();
        void Write(const Common::Response& response);
        Server::Database::Database &GetDatabase();
        void Shutdown();
        User::User& GetUserData();

        private:
        void Read(const boost::system::error_code &error,
                  std::size_t bytes_transferred,
                  const std::shared_ptr<MessageArr_t>& message);

        SharedPtrSocket_t _socket;
        Server::Database::Database& _database;
        Server::Router& _router;
        Network* _network_parent;
        Common::Log::Log& _logger;
        User::User _user;
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
