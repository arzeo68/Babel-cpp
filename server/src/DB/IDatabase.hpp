/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Database interface for the database encapsulation
*/

#ifndef SRC_BABEL_IDATABASE_HPP_
#define SRC_BABEL_IDATABASE_HPP_

#include <string>

namespace Server::Database {
    class IDatabase {
        public:
        virtual ~IDatabase() = default;

        virtual bool
        ConnectUser(const std::string& name, const std::string& password) = 0;
        virtual bool
        AddUser(const std::string& name, const std::string& password) = 0;
        virtual bool UserExists(const std::string& name) = 0;
        virtual void
        UpdateStatus(const std::string& name, const std::string& status) = 0;
    };
}

#endif
