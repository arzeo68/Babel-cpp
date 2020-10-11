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
    /**
     * User stock different data for the user
     */
    class User {
        public:
        /**
         * Set the user's name
         * @param name User's name
         */
        void SetUserName(const std::string &name);
        /**
         * Set the user's IP
         * @param ip User's IP
         */
        void SetUserIp(const std::string &ip);

        /**
         * Get user's name
         * @return User's name
         */
        std::string GetName();
        /**
         * Get user's IP
         * @return User's IP
         */
        std::string GetIP();
        /**
         * Get the current caller name. It could be the current addressee or one in pending
         * @return
         */
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
