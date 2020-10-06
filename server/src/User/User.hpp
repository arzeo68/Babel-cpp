/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include <string>

namespace Server::User {
    class User {
        public:
        void SetUserName(const std::string& name);
        void SetUserIp(const std::string& ip);

        std::string GetName();
        std::string GetIP();

        bool IsConnected();
        private:
        std::string _ip;
        std::string _name;
        bool _inCall = false;
    };
}


#endif //BABEL_USER_HPP
