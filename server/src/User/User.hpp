/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include <mutex>
#include <string>
#include "common/CallStatus.hpp"

namespace Server::User {
    class User {
        public:
        void SetUserName(const std::string &name);
        void SetUserIp(const std::string &ip);

        std::string GetName();
        std::string GetIP();
        std::string GetCallerName();
        void
        SetCallState(Common::CallState state, const std::string &caller = "");
        Common::CallState GetCallState();
        bool IsConnected();

        private:
        std::mutex _mutex;
        std::string _ip;
        std::string _name;
        Common::CallState _inCall = Common::CallState::NONE;
        std::string _caller;
    };
}


#endif //BABEL_USER_HPP
