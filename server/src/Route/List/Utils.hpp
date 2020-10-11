/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_ROUTE_LISTING_CALL_UTILS
#define SRC_ROUTE_LISTING_CALL_UTILS

#include "server/src/Route/Route.hpp"
#include "server/src/Network/Client/Client.hpp"
#include "server/src/Route/Arguments.hpp"

namespace Server::Route::Listing::Utils {
    Common::Response ChangeStateCall(
        const std::shared_ptr<Server::Network::Client> &client,
        const std::shared_ptr<Server::Network::Client> &opponent,
        Common::CallState state
    );

    enum class UserState : uint8_t {
        DISCONNECTED = 0,
        CONNECTED = 1,
        BUSY = 2
    };
    Common::Response NotifyUserStatusToFriends(
        const std::shared_ptr<Server::Network::Client> &client,
        UserState state
    );
}

#endif
