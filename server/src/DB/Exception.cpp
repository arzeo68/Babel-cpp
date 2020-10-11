/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Exceptions related to the database
*/

#include <string>
#include <cstdint>
#include "Database.hpp"

Server::Database::Exception::Opening::Opening(uint32_t code) : _code(code) {
}

const char *Server::Database::Exception::Opening::what() const noexcept {
    static std::string message =
        "The database cannot be created ; error code: " +
        std::to_string(this->_code);
    return (message.c_str());
}

Server::Database::Exception::Query::Query(uint32_t code, char *error,
                                          const std::string &query) : _code(
    code), _error(error), _query(query) {
    sqlite3_free(error);
}

const char *Server::Database::Exception::Query::what() const noexcept {
    static std::string msg =
        "An error occurred during executing a SQL query: '" + this->_error +
        "'. Code: " + std::to_string(this->_code) + " - Query: '" +
        this->_query + "'";
    return (msg.c_str());
}

