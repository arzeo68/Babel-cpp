//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#include "Router.hpp"

Server::Router::Router() = default;

bool Server::Router::addRoute(Route const &route) {
    _Routes[route.GetName()] = std::make_shared<Route>(route);
    return true;
}

bool Server::Router::handler(std::string const &routePath, Server::Route::RouteHandlerArgs_t args) {
    if (_Routes.find(routePath) != _Routes.end()) {
        _Routes[routePath]->ExecuteHandler(args);
    } else {
        return true;
    }
    return false;
}
