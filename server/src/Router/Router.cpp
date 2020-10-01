/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Router
*/

#include "Router.hpp"

Server::Router::Router() = default;

bool Server::Router::AddRoute(const Route &route) {
    _routes[route.GetName()] = route;
    return true;
}

Server::Response Server::Router::Handler(std::string const &routePath, Server::Route::RouteHandlerArgs const &args) {
    Server::Response res;
    if (_routes.find(routePath) != _routes.end()) {
        res = _routes[routePath].ExecuteHandler(args);
    } else {
        res.code = HTTPCodes::HTTPCodes_e::NOT_FOUND;
        res.msg = "Unknown route";
    }
    return res;
}
