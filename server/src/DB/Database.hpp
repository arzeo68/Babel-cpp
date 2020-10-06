/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Class handling database connection and stuffs w/ sqlite
*/

#ifndef BABEL_DATABASE_HPP
#define BABEL_DATABASE_HPP

#include <exception>
#include <cstdint>
#include <string>
#include <sqlite3.h>
#include "common/Log.hpp"

namespace Server::Database {
    namespace User {
        enum Data : uint8_t {
            ID = 0,
            NAME = 1,
            PASSWORD = 2,
            STATUS = 3
        };
    }
    class Database {
        public:
        typedef int (*DatabaseCallback_t)(void*, int, char**, char**);
        explicit Database(Common::Log::Log& logger);
        ~Database();

        bool ConnectUser(const std::string& name, const std::string& password);

        bool AddUser(const std::string& name, const std::string& password);
        bool UserExists(const std::string& name);
        void UpdateStatus(uint16_t id, const std::string& status);
        //std::string GetStatus(uint16_t id);
        void DeleteUsers();

        private:
        sqlite3* _handler;
        Common::Log::Log _logger;
        void RegisterTables();
        void ExecuteQuery(const std::string& query,
                          DatabaseCallback_t callback = nullptr,
                          void *callback_arg = nullptr);

        static const constexpr char* USER_TABLE = "user";
        #define USER_TABLE_STR std::string(Server::Database::Database::USER_TABLE)
    };

    namespace Exception {
        class Opening : std::exception {
            public:
            explicit Opening(uint32_t code);
            ~Opening() override = default;
            const char *what() const noexcept override;

            private:
            uint32_t _code;
        };

        class Query : std::exception {
            public:
            Query(uint32_t code, char* error, const std::string& query);
            ~Query() override = default;
            const char *what() const noexcept override;

            private:
            uint32_t _code;
            std::string _error;
            std::string _query;
        };
    };
}


#endif //BABEL_DATABASE_HPP
