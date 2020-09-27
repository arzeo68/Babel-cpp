/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_CONNECTION_HPP
#define BABEL_CONNECTION_HPP

#include <boost/asio.hpp>

namespace Server {
    class Connection {
        public:
        Connection(unsigned int port);

        void Run();

        private:
        boost::asio::io_service _service;
        boost::system::error_code _err;
        std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
        std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
        std::string ReadBuffer();
    };
}


#endif //BABEL_CONNECTION_HPP
