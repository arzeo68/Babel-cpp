/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Route's handler: non-specific route
*/

#ifndef SRC_ROUTE_DATA_
#define SRC_ROUTE_DATA_


#ifdef _WIN32
    #define __STDC_WANT_LIB_EXT1__ 1
    #include <string.h>
#else

    #include <cstring>

#endif

#include "server/src/Route/Route.hpp"
#include "server/src/Network/Client/Client.hpp"
#include "server/src/Route/Arguments.hpp"

namespace Server::Route::Listing {
    /**
     * This function encapsulate strcpy. This function is cross-plateforme.
     * @param dest String which the source will be copied in
     * @param source Source string
     */
    void _strcpyC(char *dest, const char *source);

    /**
     * Check if a user exists
     * @param client Caller
     * @param arg Route's main information
     * @return A response with a HTTP code and a message
     */
    Common::Response
    UserExists(std::shared_ptr<Server::Network::Client> &client,
               const Arguments::RouteHandlerArgs &arg);
    /**
     * Login an user with specified credentials
     * @param client
     * @param arg
     * @return
     */
    Common::Response Login(std::shared_ptr<Server::Network::Client> &client,
                           const Arguments::RouteHandlerArgs &arg);
    /**
     * Register and login a user using specified credentials
     * @param client
     * @param arg
     * @return
     */
    Common::Response Register(std::shared_ptr<Server::Network::Client> &client,
                              const Arguments::RouteHandlerArgs &arg);
    /**
     * Set the user's status
     * @param client
     * @param arg
     * @return
     */
    Common::Response SetStatus(std::shared_ptr<Server::Network::Client> &client,
                               const Arguments::RouteHandlerArgs &arg);
    /**
     * See in the namespace Friend below.
     * @param client
     * @param arg
     * @return
     */
    Common::Response
    HandleFriend(std::shared_ptr<Server::Network::Client> &client,
                 const Arguments::RouteHandlerArgs &arg);

    namespace Friend {
        /**
         * Add a friend and set the friendship status on pending
         * @param client
         * @param arg
         * @return
         */
        Common::Response Add(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
        /**
         * Update a friendship status: accept or decline the invitation
         * @param client
         * @param arg
         * @return
         */
        Common::Response
        UpdateStatus(std::shared_ptr<Server::Network::Client> &client,
                     const Server::Route::Arguments::RouteHandlerArgs &arg);
        /**
         * Delete a friendship
         * @param client
         * @param arg
         * @return
         */
        Common::Response
        Delete(std::shared_ptr<Server::Network::Client> &client,
               const Server::Route::Arguments::RouteHandlerArgs &arg);
        /**
         * Get a friend list
         * @param client
         * @param arg
         * @return
         */
        Common::Response Get(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
    }

    /**
     * Check if a friend is connected
     * @param client
     * @param arg
     * @return
     */
    Common::Response
    IsFriendConnected(std::shared_ptr<Server::Network::Client> &client,
                      const Server::Route::Arguments::RouteHandlerArgs &arg);

    /**
     * Start or accept a call depending on the current call state
     * @param client
     * @param arg
     * @return
     */
    Common::Response StartCall(std::shared_ptr<Server::Network::Client> &client,
                               const Server::Route::Arguments::RouteHandlerArgs &arg);
    /**
     * Hang on or decline a call depending on the current call state
     * @param client
     * @param arg
     * @return
     */
    Common::Response EndCall(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
}

#endif
