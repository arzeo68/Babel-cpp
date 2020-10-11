/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Functions to interact with the database
*/

#include "Database.hpp"

bool Server::Database::Database::AddUser(const std::string &name,
                                         const std::string &password) {
    this->_logger->Debug(
        "Checking if user " + name + " exists in the database...");
    if (this->UserExists(name))
        return (false);
    this->ExecuteQuery(
        "INSERT INTO 'user' ('name', 'password')"
        " VALUES ('" + name + "', '" + password + "');");
    this->_logger->Info("UserExists " + name + " added to the database");
    return (true);
}

bool Server::Database::Database::UserExists(const std::string &name) {
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
bool Server::Database::Database::ConnectUser(const std::string &name,
                                             const std::string &password) {
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

Common::FriendStatus
Server::Database::Database::GetFriendStatus(const std::string &name,
                                            const std::string &opponent) {
    Common::FriendStatus status = Common::FriendStatus::NONE;
    this->ExecuteQuery(
        "SELECT * FROM 'friend' WHERE (name='" + name + "' AND friend='" +
        opponent + "') OR"
                   "(name='" + opponent + "' AND friend='" + name +
        "') LIMIT 1;",
        [](void *arg, int count, char **data, char **) -> int {
            auto *status = reinterpret_cast<Common::FriendStatus *>(arg);
            if (count == 0)
                *status = Common::FriendStatus::NONE;
            else
                *status = static_cast<Common::FriendStatus>(std::atoi(
                    data[User::F_STATUS]));
            return (0);
        }, &status);
    return (status);
}

bool Server::Database::Database::AddFriend(const std::string &name,
                                           const std::string &addressee) {
    if (!this->UserExists(addressee))
        return (false);
    this->ExecuteQuery(
        "INSERT INTO 'friend' ('name', 'friend', 'status')"
        " VALUES ('" + name + "', '" + addressee + "', '1');");
    return (true);
}

void Server::Database::Database::DeleteFriend(const std::string &name,
                                              const std::string &addressee) {
    this->ExecuteQuery(
        "DELETE FROM 'friend' WHERE name='" + name + "' AND friend='" +
        addressee +
        "';");
}

void Server::Database::Database::UpdateFriendStatus(const std::string &name,
                                                    const std::string &addressee,
                                                    const Common::FriendStatus &status) {
    if (status != Common::FriendStatus::REJECTED) {
        this->ExecuteQuery("UPDATE 'friend' SET status='" +
                           std::to_string(static_cast<uint8_t>(status)) +
                           "' WHERE name='" + name + "' AND friend='" +
                           addressee +
                           "';");

    } else
        this->DeleteFriend(name, addressee);
}

Server::Database::Database::FriendListData_t
Server::Database::Database::GetFriends(const std::string &author) {
    std::pair<FriendListData_t, std::string> friendList = {
        {}, author
    };
    this->ExecuteQuery(
        "SELECT * FROM 'friend' WHERE name='" + author + "' OR friend='" +
        author + "';",
        [](void *arg, int, char **data, char **) -> int {
            auto *friendList = reinterpret_cast<std::pair<FriendListData_t, std::string> *>(arg);
            if (data[User::Data::F_NAME] == (*friendList).second)
                (*friendList).first.first.emplace_back(
                    std::string(data[User::Data::F_FRIEND]));
            else
                (*friendList).first.first.emplace_back(
                    std::string(data[User::Data::F_NAME]));
            (*friendList).first.second.emplace_back(
                std::string(data[User::Data::F_STATUS]));
            return (0);
        }, &friendList);
    return (friendList.first);
}
