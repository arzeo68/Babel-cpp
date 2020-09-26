//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#include "Router.hpp"

Server::API::Router::Router() {

}

bool Server::API::Router::addRoute(std::shared_ptr<Route> route) {
    _Routes[route.getName()] = route;
    return true;
}

bool Server::API::Router::handler(std::string routePath) {
    if (_Routes.find(routePath) != _Routes.end()) {
        _Routes[routePath]->handler();
    } else {
        return true;
    }
    return false;
}
