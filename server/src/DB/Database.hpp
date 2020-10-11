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

        /**
         * An enumeration that corresponds to the column order in the database.
         */
        enum Data : uint8_t {
            /**
             * User database
             */
            ID = 0,
            NAME = 1,
            PASSWORD = 2,
            STATUS = 3,

            /**
             * Friend database
             */
            F_NAME = 0,
            F_FRIEND = 1,
            F_STATUS = 2,
        };
    }

    /**
     * The class database inherit from the interface IDatabase.
     * The main purpose is to handle any operation related to SQLite3
     */
    class Database : public IDatabase {
        public:
        /**
         * The constructor open a SQLITE3 database and keep the handler w/ it
         * @param logger Shared pointer to log error or info messages
         */
        explicit Database(std::shared_ptr<Common::Log::Log> logger);
        /**
         * The destructor close the SQLITE3 handler
         */
        ~Database() override;

        void RegisterTables() override;
        bool ConnectUser(const std::string &name,
                         const std::string &password) override;
        bool
        AddUser(const std::string &name, const std::string &password) override;
        bool UserExists(const std::string &name) override;
        void UpdateStatus(const std::string &name,
                          const std::string &status) override;
        Common::FriendStatus
        GetFriendStatus(const std::string &name,
                        const std::string &opponent) override;
        bool AddFriend(const std::string &name,
                       const std::string &addressee) override;
        void
        DeleteFriend(const std::string &name,
                     const std::string &addressee) override;
        void UpdateFriendStatus(const std::string &name,
                                const std::string &addressee,
                                const Common::FriendStatus &status) override;
        FriendListData_t GetFriends(const std::string &author) override;

        private:
        /**
         * DatabaseCallback_t is a function pointer used by SQLITE3 when a SQL statement requires response.
         * @param callback_arg The custom argument passed to the callback
         * @param max_size The number of column for the selected table
         * @param data Data from the current row with the size of 'max_size'
         * @param column_names All the column names with the size of 'max_size'
         */
        typedef int (*DatabaseCallback_t)(void *callback_arg, int max_size,
                                          char **data, char **column_names);

        /**
         * Handler to the SQL database
         */
        sqlite3 *_handler;

        /**
         * Shared pointer corresponds to the server's logger
         */
        std::shared_ptr<Common::Log::Log> _logger;

        /**
         * A private function that execute a query and redirect the output on a callback if needed that can take a custom argument of any type
         * @param query SQL query
         * @param callback A function that will be called when the query end. Only SELECT SQL statement call this function
         * @param callback_arg Custom argument passed to the callback function
         */
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
