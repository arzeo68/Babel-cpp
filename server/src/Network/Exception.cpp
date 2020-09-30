/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Client.hpp"

Server::Network::InternalError::InternalError(
    const boost::system::error_code &error) : _error(error) {
}

const char *Server::Network::InternalError::what() const noexcept {
    static std::string message = "A fatal error occurred for a client. Error code: " + this->_error.message();
    return (message.c_str());
}

boost::system::error_code Server::Network::InternalError::GetError() const {
    return (this->_error);
}

