//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#include "Router.hpp"

Server::Router::Router() = default;

bool Server::Router::AddRoute(Route const &route) {
    _routes[route.GetName()] = std::make_shared<Route>(route);
    return true;
}

bool Server::Router::Handler(std::string const &routePath, Server::Route::RouteHandlerArgs_t args) {
    if (_routes.find(routePath) != _routes.end()) {
        _routes[routePath]->ExecuteHandler(args);
    } else {
        return true;
    }
    return false;
}
