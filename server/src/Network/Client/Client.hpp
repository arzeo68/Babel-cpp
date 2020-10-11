/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Handle incoming connection inside a client
*/

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <memory>
#include <mutex>
#include "Socket.hpp"
#include "common/TCP/CommonPackages.hpp"
#include "server/src/Network/Network.hpp"
#include "server/src/DB/Database.hpp"
#include "server/src/User/User.hpp"

namespace Server::Network {
    /**
     * This class represent someone connected to the server. It means the application has established a connection to the server and a socket has been created.
     */
    using Socket_t = boost::asio::ip::tcp::socket;

    class Client
        :
            public std::enable_shared_from_this<Client>, ASocket<Socket_t> {
        public:
        /*
         * SharedPtrSocket_t is a shared pointer of Socket_t.
         */
        typedef std::shared_ptr<Socket_t> SharedPtrSocket_t;
        /**
         * MessageArr_t is an array of char with the size of PackageManager. The size is dynamic and depends on PackageManager.
         */
        typedef std::array<char, sizeof(Common::PackageServer)> MessageArr_t;

        /**
         * Constructor for the client. The constructor will create the socket and remain some important elements: logger, worker and the network himself.
         * @tparam S Template with the type of the service that will be used to create the socket
         * @param database A reference to the database
         * @param router Router contains all known route and function to redirect at
         * @param network Network is the direct parent of the client containing all important data
         * @param logger A shared instance of the parent logger
         * @param service The service that will be used to construct the socket
         * @param worker A shared instance of the worker. Mainly used to add tasks.
         */
        template<class S>
        explicit Client(Server::Database::Database &database,
                        Server::Router &router,
                        std::shared_ptr<Network> network,
                        std::shared_ptr<Common::Log::Log> logger,
                        S &service,
                        std::shared_ptr<Worker> worker)
            :
            _database(database),
            _router(router),
            _network_parent(std::move(network)),
            _logger(std::move(logger)),
            _worker(std::move(worker)) {
            this->_socket = std::make_shared<Socket_t>(service);
            this->_logger->Debug("Client constructor, ptr: ", this);
        }
        /**
         * Destructor for the client. It only print a message.
         */
        ~Client() override;
        /**
         * Deleted copy constructor to make each client unique.
         * @param obj Right operand part
         */
        Client(const Client &obj) = delete;

        SharedPtrSocket_t GetSocket() override;
        /**
         * Return the shared instance of the network
         * @return Shared pointer of the network
         */
        std::shared_ptr<Network> GetNetwork();

        /**
         * Create an array of MessageArr_t type and do an asynchronous read
         */
        void Read();

        /**
         * Asynchronous write on the socket with a pre-formatted response
         * @param response The query to write
         */
        void Write(const Common::Response &response);

        /**
         * Get the current database instance stocked
         * @return database instance stocked
         */
        Server::Database::Database &GetDatabase();
        void Shutdown() override;

        /**
         * Get the user's data instance
         * @return the user's data instance
         */
        User::User &GetUserData();

        /**
         * Get the shared worker instance
         * @return a shared pointer on the worker instance
         */
        std::shared_ptr<Worker> GetWorker();

        private:
        void ExecRead(const boost::system::error_code &error,
                      std::size_t bytes_transferred,
                      const std::shared_ptr<MessageArr_t> &message);
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
