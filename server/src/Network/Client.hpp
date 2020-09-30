/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <memory>
#include <boost/enable_shared_from_this.hpp>
#include "Network.hpp"


namespace Server::Network {
    class Client {
        public:
        explicit Client(boost::asio::io_service &service);

        Network::SharedPtrSocket_t GetSocket();
        //std::string &GetReadBuffer();
        void StartRead();
        void Write(const std::string& message);

        private:
        void Read(const boost::system::error_code& error, std::size_t bytes_transferred, Network::SharedPtrMessageArr_t message);

        Network::SharedPtrSocket_t _socket;
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
