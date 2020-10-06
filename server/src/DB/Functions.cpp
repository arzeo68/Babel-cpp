/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Functions to interact with the database
*/

#include "Database.hpp"

bool Server::Database::Database::AddUser(const std::string& name,
                                         const std::string& password) {
    this->_logger.Debug("Checking if user " + name + " exists in the database...");
    if (this->UserExists(name))
        return (false);
    this->ExecuteQuery(
        "INSERT INTO " + std::string(Server::Database::Database::USER_TABLE) +
        "('name', 'password') VALUES ('" + name + "', '" + password + "');");
    this->_logger.Info("User " + name + " added to the database");
    return (true);
}

void Server::Database::Database::UpdateStatus(uint16_t id,
                                              const std::string& status) {
    this->ExecuteQuery(
        "UPDATE " + std::string(Server::Database::Database::USER_TABLE) +
        " SET 'status'='" + status + "' WHERE 'id'=" + std::to_string(id));
}

[[maybe_unused]] void Server::Database::Database::DeleteUsers() {
    this->ExecuteQuery("DELETE FROM '" + USER_TABLE_STR + "';" +
                       "DELETE FROM SQLITE_SEQUENCE WHERE name='" +
                       USER_TABLE_STR + "';");
}

bool Server::Database::Database::UserExists(const std::string& name) {
    bool exists = false;
    this->ExecuteQuery(
        "SELECT * FROM " + USER_TABLE_STR + " WHERE name='" + name + "';",
        [](void *arg, int size, char **, char **) -> int {
            bool *existing = reinterpret_cast<bool *>(arg);
            *existing = size != 0;
            return (0);
        }, &exists);
    return (exists);
}

// https://github.com/mpdn/sqlite-digest/blob/master/digest.c
// Encoding SHA526
bool Server::Database::Database::ConnectUser(const std::string& name,
                                             const std::string& password) {
    bool exists = false;
    this->ExecuteQuery(
        "SELECT * FROM " + USER_TABLE_STR + " WHERE name='" + name + "'"
                                                                     "AND password='" +
        password + "';",
        [](void *arg, int size, char **, char **) -> int {
            bool *existing = reinterpret_cast<bool *>(arg);
            *existing = size != 0;
            return (0);
        }, &exists);
    return (exists);
}
