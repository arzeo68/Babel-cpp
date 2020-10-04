/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_ROUTE_DATA_
#define SRC_ROUTE_DATA_

#include "server/src/API/Route/Route.hpp"
#include "server/src/Network/Client.hpp"

namespace Server::Route::Listing {
    Common::Response User(Server::Network::Client &client,
                          const Common::RouteHandlerArgs &arg);

    Common::Response Login(Server::Network::Client &client,
                           const Common::RouteHandlerArgs &arg);

    Common::Response Register(Server::Network::Client &client,
                              const Common::RouteHandlerArgs &arg);
}

#endif
