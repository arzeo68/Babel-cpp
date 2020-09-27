//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#include "Router.hpp"

Server::API::Router::Router() = default;

bool Server::API::Router::addRoute(Route const &route) {
    _Routes[route.GetName()] = std::make_shared<Route>(route);
    return true;
}

bool Server::API::Router::handler(std::string const &routePath, Route::RouteHandlerArgs_t args) {
    if (_Routes.find(routePath) != _Routes.end()) {
        _Routes[routePath]->ExecuteHandler(args);
    } else {
        return true;
    }
    return false;
}
