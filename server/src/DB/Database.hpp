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
#include <vector>
#include "common/Log.hpp"
#include "IDatabase.hpp"
#include "common/FriendStatus.hpp"

namespace Server::Database {
    namespace User {
        enum Data : uint8_t {
            ID = 0,
            NAME = 1,
            PASSWORD = 2,
            STATUS = 3,

            F_NAME = 0,
            F_FRIEND = 1,
            F_STATUS = 2,
        };
    }

    class Database : public IDatabase {
        public:
        explicit Database(std::shared_ptr<Common::Log::Log> logger);

        ~Database() override;

        void RegisterTables();
        bool ConnectUser(const std::string &name,
                         const std::string &password) override;
        bool
        AddUser(const std::string &name, const std::string &password) override;
        bool UserExists(const std::string &name) override;
        void UpdateStatus(const std::string &name,
                          const std::string &status) override;
        Common::FriendStatus
        GetFriendStatus(const std::string &name, const std::string &opponent);
        bool AddFriend(const std::string &name, const std::string &addressee);
        void
        DeleteFriend(const std::string &name, const std::string &addressee);
        void UpdateFriendStatus(const std::string &name,
                                const std::string &addressee,
                                const Common::FriendStatus &status);

        // Vector1: Friend name - Vector2: Friendship status
        typedef std::pair<std::vector<std::string>, std::vector<std::string>> FriendListData_t;
        FriendListData_t GetFriends(const std::string &author);

        private:
        typedef int (*DatabaseCallback_t)(void *, int, char **, char **);

        sqlite3 *_handler;
        std::shared_ptr<Common::Log::Log> _logger;

        void ExecuteQuery(const std::string &query,
                          DatabaseCallback_t callback = nullptr,
                          void *callback_arg = nullptr);
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
            Query(uint32_t code, char *error, const std::string &query);
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
