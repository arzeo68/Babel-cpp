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
#include "server/src/Network/Client/Client.hpp"
#include "server/src/Route/Arguments.hpp"

namespace Server::Route::Listing {
    void _strcpyC(char *dest, const char *source);

    Common::Response
    UserExists(std::shared_ptr<Server::Network::Client> &client,
               const Arguments::RouteHandlerArgs &arg);
    Common::Response Login(std::shared_ptr<Server::Network::Client> &client,
                           const Arguments::RouteHandlerArgs &arg);
    Common::Response Register(std::shared_ptr<Server::Network::Client> &client,
                              const Arguments::RouteHandlerArgs &arg);
    Common::Response SetStatus(std::shared_ptr<Server::Network::Client> &client,
                               const Arguments::RouteHandlerArgs &arg);
    Common::Response
    HandleFriend(std::shared_ptr<Server::Network::Client> &client,
                 const Arguments::RouteHandlerArgs &arg);

    namespace Friend {
        Common::Response Add(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
        Common::Response
        UpdateStatus(std::shared_ptr<Server::Network::Client> &client,
                     const Server::Route::Arguments::RouteHandlerArgs &arg);
        Common::Response
        Delete(std::shared_ptr<Server::Network::Client> &client,
               const Server::Route::Arguments::RouteHandlerArgs &arg);
        Common::Response Get(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
    }

    Common::Response
    IsFriendConnected(std::shared_ptr<Server::Network::Client> &client,
                      const Server::Route::Arguments::RouteHandlerArgs &arg);

    Common::Response StartCall(std::shared_ptr<Server::Network::Client> &client,
                               const Server::Route::Arguments::RouteHandlerArgs &arg);

    Common::Response EndCall(std::shared_ptr<Server::Network::Client> &client,
                             const Server::Route::Arguments::RouteHandlerArgs &arg);
}

#endif
