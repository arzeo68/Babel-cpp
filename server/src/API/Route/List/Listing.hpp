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
#include "server/src/API/Route/Arguments.hpp"

namespace Server::Route::Listing {

    Common::Response User(Server::Network::Client &client,
                          const Arguments::RouteHandlerArgs &arg);

    //Common::Response Login(Server::Network::Client &client,
    //                       const RouteHandlerArgs &arg);
    //
    //Common::Response Register(Server::Network::Client &client,
    //                          const RouteHandlerArgs &arg);
}

#endif
