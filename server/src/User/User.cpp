/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "User.hpp"

void Server::User::User::SetUserName(const std::string &name) {
    this->_name = name;
}

void Server::User::User::SetUserIp(const std::string &ip) {
    this->_ip = ip;
}

bool Server::User::User::IsConnected() {
    return (!this->_name.empty());
}

std::string Server::User::User::GetName() {
    return (this->_name);
}

std::string Server::User::User::GetIP() {
    return (this->_ip);
}
