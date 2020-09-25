/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <array>
#include <iostream>
#include "Connection.hpp"

Server::Connection::Connection(unsigned int port) : _context(std::make_shared<boost::asio::io_context>()),
                                                    _socket(std::make_shared<boost::asio::ip::tcp::socket>(*_context)),
                                                    _acceptor(std::make_shared<boost::asio::ip::tcp::acceptor>(*_context, boost::asio::ip::tcp::endpoint(
                                                        boost::asio::ip::tcp::v4(),
                                                        port))) {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port);

    //this->_socket->connect(ep);
}

void Server::Connection::Run() {
    printf("Waiting for connection...\n");
    try {
        this->_acceptor->accept(*this->_socket);
        printf("A new client has joined\n");
        sleep(5);
        this->ReadBuffer();
    } catch (const std::exception &e) {
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
