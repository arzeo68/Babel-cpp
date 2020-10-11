/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "User.hpp"

void Server::User::User::SetUserName(const std::string &name) {
    this->_mutex.lock();
    this->_name = name;
    this->_mutex.unlock();
}

void Server::User::User::SetUserIp(const std::string &ip) {
    this->_mutex.lock();
    this->_ip = ip;
    this->_mutex.unlock();
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
void Server::User::User::SetCallState(Common::CallState state,
                                      const std::string &caller) {
    this->_mutex.lock();
    if (!caller.empty())
        this->_caller = caller;
    if (state == Common::CallState::NONE || state == Common::CallState::ENDED ||
        state == Common::CallState::DECLINED)
        this->_caller.clear();
    if (state == Common::CallState::ENDED ||
        state == Common::CallState::DECLINED)
        state = Common::CallState::NONE;
    this->_inCall = state;
    this->_mutex.unlock();
}

Common::CallState Server::User::User::GetCallState() {
    return (this->_inCall);
}
std::string Server::User::User::GetCallerName() {
    return (this->_caller);
}
