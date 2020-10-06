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
        "INSERT INTO 'user' ('name', 'password')"
        " VALUES ('" + name + "', '" + password + "');");
    this->_logger.Info("User " + name + " added to the database");
    return (true);
}

[[maybe_unused]] void Server::Database::Database::DeleteUsers() {
    this->ExecuteQuery("DELETE FROM 'user';"
                       "DELETE FROM SQLITE_SEQUENCE WHERE name='user';");
}

bool Server::Database::Database::UserExists(const std::string& name) {
    bool exists = false;
    this->ExecuteQuery(
        "SELECT * FROM user WHERE name='" + name + "';",
        [](void *arg, int, char **, char **) -> int {
            bool *existing = reinterpret_cast<bool *>(arg);
            *existing = true;
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
        "SELECT * FROM user WHERE name = '" + name + "' AND password='" +
        password + "';",
        [](void *arg, int, char **, char **) -> int {
            bool *existing = reinterpret_cast<bool *>(arg);
            *existing = true;
            return (0);
        }, &exists);
    return (exists);
}

void Server::Database::Database::UpdateStatus(const std::string &name,
                                              const std::string &status) {
    this->ExecuteQuery("UPDATE 'user' SET status = '" +
        status + "' WHERE name = '" + name + "';");
}
