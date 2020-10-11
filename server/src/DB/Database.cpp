/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Class handling database connection and stuffs w/ sqlite
*/

#include <iostream>
#include <utility>
#include "Database.hpp"

Server::Database::Database::Database(std::shared_ptr<Common::Log::Log> logger)
    : _handler(nullptr), _logger(std::move(logger)) {
    uint32_t code = sqlite3_open("database.db", &this->_handler);
    if (code != SQLITE_OK)
        throw Exception::Opening(code);
    this->_logger->Info("Successfully connected to the database");
    this->RegisterTables();
}

Server::Database::Database::~Database() {
    sqlite3_close(this->_handler);
}

void Server::Database::Database::ExecuteQuery(const std::string &query,
                                              DatabaseCallback_t callback,
                                              void *callback_arg) {
    char *error_msg = nullptr;
    uint32_t code = sqlite3_exec(this->_handler, query.c_str(), callback,
                                 callback_arg, &error_msg);
    if (code != SQLITE_OK || error_msg != nullptr)
        throw Exception::Query(code, error_msg, query);
    sqlite3_free(error_msg);
}

void Server::Database::Database::RegisterTables() {
    this->ExecuteQuery("CREATE TABLE IF NOT EXISTS \"user\" (\r\n"
                       "    'id'       INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\r\n"
                       "    'name'     TEXT                              NOT NULL,\r\n"
                       "    'password' TEXT                              NOT NULL,\r\n"
                       "    'status'   TEXT NOT NULL DEFAULT ''\r\n"
                       ");"
                       "CREATE TABLE IF NOT EXISTS \"friend\" (\r\n"
                       "    'name'       TEXT NOT NULL,\r\n"
                       "    'friend'     TEXT NOT NULL,\r\n"
                       "    'status'     INTEGER NOT NULL DEFAULT '0'\r\n"
                       ");");
    this->_logger->Info("Tables created in the database");
}
