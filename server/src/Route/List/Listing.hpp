/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
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
#include "server/src/Network/Client.hpp"
#include "server/src/Route/Arguments.hpp"

namespace Server::Route::Listing {
    void CopyCString(char* dest, const char* source);

    Common::Response User(Server::Network::Client &client,
                          const Arguments::RouteHandlerArgs &arg);

    Common::Response Login(Server::Network::Client &client,
                           const Arguments::RouteHandlerArgs &arg);

    Common::Response Register(Server::Network::Client &client,
                              const Arguments::RouteHandlerArgs &arg);

    Common::Response SetStatus(Server::Network::Client &client,
                              const Arguments::RouteHandlerArgs &arg);
}

#endif
