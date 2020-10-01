/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_ROUTE_DATA_
#define SRC_ROUTE_DATA_

#include "server/src/API/Route/Response.hpp"
#include "server/src/API/Route/Route.hpp"
#include "server/src/Network/Client.hpp"

namespace Server::API::Route {
    Server::Response Login(Server::Network::Client &client, const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response Register(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response UserExist(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response Status(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response Friend(const Server::Route::RouteHandlerArgs &arg);
    //
    //static Server::Response PutFriend(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response PostFriend(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response DeleteFriend(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response GetFriends(const Server::Route::RouteHandlerArgs &arg);
    //
    //static Server::Response IsConnected(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response StartCall(const Server::Route::RouteHandlerArgs &arg);
    //static Server::Response EndCall(const Server::Route::RouteHandlerArgs &arg);
}

#endif
