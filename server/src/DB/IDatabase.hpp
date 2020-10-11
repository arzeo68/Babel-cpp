/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Database interface for the database encapsulation
*/

#ifndef SRC_BABEL_IDATABASE_HPP_
#define SRC_BABEL_IDATABASE_HPP_

#include <string>
#include "common/FriendStatus.hpp"

namespace Server::Database {
    class IDatabase {
        public:
        // Vector1: Friend name - Vector2: Friendship status
        /**
         * FriendListData_t returns a pair of 2 vectors:
         *  1) A vector with the friends name
         *  2) A vector with the friendship status within the friend at the same index from the first vector
         */
        typedef std::pair<std::vector<std::string>, std::vector<std::string>> FriendListData_t;
        virtual ~IDatabase() = default;

        /**
         * Register all needed SQL tables. There is actually 2 tables: 'user' and 'friends'.
         */
        virtual void RegisterTables() = 0;
        /**
         * Try to connect an user by using a name and a password. The password isn't encrypted.
         * @param name User's name
         * @param password User's password
         * @return true if the credentials are correct
         * @return false if one or both given credentials are incorrect
         */
        virtual bool ConnectUser(const std::string &name,
                                 const std::string &password) = 0;
        /**
         * Add a new user to the database using a name and a password.
         * @param name User's name
         * @param password User's password
         * @return true if the user has been successfully added to the database
         * @return false if the user already exists in the database
         */
        virtual bool
        AddUser(const std::string &name, const std::string &password) = 0;

        /**
         * Check in the database if an user exists by his name
         * @param name User's name to search for
         * @return true if the user exists otherwise, false
         */
        virtual bool UserExists(const std::string &name) = 0;

        /**
         * Update an user's status in the database
         * @param name User's name
         * @param status User's status
         */
        virtual void UpdateStatus(const std::string &name,
                                  const std::string &status) = 0;

        /**
         * Get a friendship status. The status are defined in common/FriendStatus.hpp
         * @param name User's name
         * @param addressee Friend's name
         * @return A value from the enumerator FriendStatus
         */
        virtual Common::FriendStatus GetFriendStatus(const std::string &name,
                                                     const std::string &addressee) = 0;

        /**
         * Add a friend and set the status of the relationship on Pending
         * @param name User's name
         * @param addressee Friend's name
         * @return true if the friend has been added
         * @return false if addressee doesn't exists in the database
         */
        virtual bool
        AddFriend(const std::string &name, const std::string &addressee) = 0;

        /**
         * Delete a friend in the database
         * @param name User's name
         * @param addressee Friend's name
         */
        virtual void
        DeleteFriend(const std::string &name, const std::string &addressee) = 0;

        /**
         * Update a friendship status
         * @param name User's name
         * @param addressee Friend's name
         * @param status New status to set
         */
        virtual void UpdateFriendStatus(const std::string &name,
                                        const std::string &addressee,
                                        const Common::FriendStatus &status) = 0;

        /**
         * Get a list of all friends
         * @param author User's name
         * @return See FriendListData_t
         */
        virtual FriendListData_t GetFriends(const std::string &author) = 0;
    };
}

#endif
