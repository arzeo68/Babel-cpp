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

        explicit Client(Server::Database::Database &database,
                        Server::Router &router,
                        std::shared_ptr<Network> network,
                        std::shared_ptr<Common::Log::Log> logger,
                        boost::asio::io_service &service,
                        std::shared_ptr<Worker> worker);
        ~Client();
        Client(const Client &obj) = delete;

        SharedPtrSocket_t GetSocket();
        std::shared_ptr<Network> GetNetwork();
        void Read();
        void Write(const Common::Response &response);
        Server::Database::Database &GetDatabase();
        void Shutdown();
        User::User &GetUserData();
        std::shared_ptr<Worker> GetWorker();

        private:
        void ExecRead(const boost::system::error_code &error,
                      std::size_t bytes_transferred,
                      const std::shared_ptr<MessageArr_t> &message);
        SharedPtrSocket_t _socket;
        Server::Database::Database &_database;
        Server::Router &_router;
        std::shared_ptr<Network> _network_parent;
        std::shared_ptr<Common::Log::Log> _logger;
        User::User _user;
        std::shared_ptr<Worker> _worker;
    };

    template<class E>
    class InternalError : public std::exception {
        public:
        explicit InternalError(const E &err) : _error(err) {
        }

        ~InternalError() override = default;

        E GetError() const {
            return (_error);
        }

        const char *what() const noexcept override {
            static std::string message =
                "A fatal error occurred for a client. Error code: " +
                this->_error.message();
            return (message.c_str());
        }

        private:
        E _error;
    };
}


#endif //BABEL_CLIENT_HPP
