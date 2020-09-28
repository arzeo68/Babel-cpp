/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include "Connection.hpp"

Server::Connection::Connection(unsigned int port) : _socket(std::make_shared<boost::asio::ip::tcp::socket>(_service)),
                                                    _acceptor(std::make_shared<boost::asio::ip::tcp::acceptor>(_service, boost::asio::ip::tcp::endpoint(
                                                        boost::asio::ip::tcp::v4(),
                                                        port))) {
}

void Server::Connection::Run() {
    try {
        printf("Waiting for new client on %u...\n", this->_acceptor->local_endpoint().port());
        this->_acceptor->async_accept(*this->_socket, [](const boost::system::error_code& error) {
            if (error) {
                std::cout << "Can't accept connection, error occured" << std::endl;
            } else {
                printf("A connection is coming\n");
            }
        });
        this->_service.run(_err);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

std::string Server::Connection::ReadBuffer() {
    std::array<char, 128> buffer;
    boost::system::error_code err;
    size_t size = this->_socket->read_some(boost::asio::buffer(buffer), err);
    if (err == boost::asio::error::eof)
        printf("Connection closed by peer");
    //else if (err) {
    //    printf("Err?\n");
    //    throw boost::system::system_error(err);
    //}
    //std::cout << "Message??: " << buffer.data() << std::endl;
    //std::cout.write(buffer.data(), size);
    printf("Msg: '%s' & %zu\n", std::string(buffer.data()).c_str(), size);
    //printf("Read %lu -> '%s'\n", size, reinterpret_cast<char *>(buffer.data().data()));
    return ("");
}
