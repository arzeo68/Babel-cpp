/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Class handling database connection and stuffs w/ sqlite
*/

#include <iostream>
#include "Database.hpp"

Server::Database::Database::Database() : _handler(nullptr) {
    uint32_t rtn = sqlite3_open("database.db", &this->_handler);
    if (rtn != SQLITE_OK)
        throw Exception::Opening(rtn);
    std::cout << "Connected to the database" << std::endl;
    this->RegisterTables();
}

Server::Database::Database::~Database() {
    sqlite3_close(this->_handler);
    this->_handler = nullptr;
}


void Server::Database::Database::ExecuteQuery(const std::string &query, DatabaseCallback_t callback, void *callback_arg) {
    char *error_msg = nullptr;
    uint32_t code = sqlite3_exec(this->_handler, query.c_str(), callback,
                                 callback_arg, &error_msg);
    if (code != SQLITE_OK || error_msg != nullptr)
        throw Exception::Query(code, error_msg, query);
}

void Server::Database::Database::RegisterTables() {
    this->ExecuteQuery("CREATE TABLE IF NOT EXISTS \"" +
                       std::string(
                           Server::Database::Database::USER_TABLE) +
                       "\" (\n"
                       "    'id'       INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\n"
                       "    'name'     TEXT                              NOT NULL,\n"
                       "    'password' TEXT                              NOT NULL,\n"
                       "    'status'   TEXT\n"
                       ");");
    std::cout << "Tables created in the database" << std::endl;
}

void Server::Database::Database::AddUser(const std::string &name,
                                         const std::string &password) {
    this->ExecuteQuery(
        "INSERT INTO " + std::string(Server::Database::Database::USER_TABLE) +
        "('name', 'password') VALUES ('" + name + "', '" + password + "');");
    std::cout << "User " + name + " added to the database" << std::endl;
}

void Server::Database::Database::UpdateStatus(uint16_t id, const std::string& status) {
    this->ExecuteQuery(
        "UPDATE " + std::string(Server::Database::Database::USER_TABLE) +
        " SET 'status'='" + status + "' WHERE 'id'=" + std::to_string(id));
}

[[maybe_unused]] void Server::Database::Database::DeleteUsers() {
    this->ExecuteQuery("DELETE FROM '" + USER_TABLE_STR + "';" +
                       "DELETE FROM SQLITE_SEQUENCE WHERE name='"+USER_TABLE_STR+"';");
}

bool Server::Database::Database::UserExists(const std::string& name) {
    bool exists = false;
    this->ExecuteQuery(
        "SELECT * FROM " + USER_TABLE_STR + " WHERE name='" + name + "';",
        [] (void *arg, int size, char **, char **) -> int {
            bool *existing = reinterpret_cast<bool*>(arg);
            *existing = size != 0;
            return (0);
        }, &exists);
    return (exists);
}




