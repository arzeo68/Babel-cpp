/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <algorithm>
#include "Route.hpp"

Server::API::Route::Route(const std::string &name,
                          Server::API::Route::RouteHandler_t handler) :
                          _name(name), _handler(handler) {
}

Server::API::HTTPCodes::HTTPCodes_t
Server::API::Route::ExecuteHandler(const char **args) const {
    return (this->_handler(args));
}

std::string Server::API::Route::GetName() const {
    return (this->_name);
}

bool Server::API::Route::operator==(const std::string& name) {
    return (this->_name == name);
}

bool Server::API::Route::operator==(const std::string& name) const {
    return (this->_name == name);
}


Server::API::RouteContainer::RouteContainer(const Server::API::Route &&route) {
    this->_container.push_back(route);
}

Server::API::RouteContainer::RouteContainer(const std::list<Route> &&route) {
    this->_container = route;
}

void Server::API::RouteContainer::PushBackRoute(const Server::API::Route &route) {
    this->_container.push_back(route);
}

void Server::API::RouteContainer::PushBackRoute(const Server::API::Route &&route) {
    this->_container.push_back(route);
}

std::list<Server::API::Route>::iterator Server::API::RouteContainer::begin() {
    return (this->_container.begin());
}

std::list<Server::API::Route>::iterator Server::API::RouteContainer::end() {
    return (this->_container.end());
}

bool Server::API::RouteContainer::Exists(const std::string& RouteName) {
    return (std::find(this->_container.begin(), this->_container.end(), RouteName) != this->_container.end());
}

Server::API::HTTPCodes::HTTPCodes_t
Server::API::RouteContainer::ExecuteRouteHandler(const std::string &route, Route::RouteHandlerArgs_t args) {
    auto r = std::find(this->_container.begin(), this->_container.end(), route);
    if (r == this->_container.end())
        throw Exception::InvalidRoute(route);
    return (r->ExecuteHandler(args));
}

Server::API::Exception::InvalidRoute::InvalidRoute(const std::string &name) : _name(name) {
}

const char *Server::API::Exception::InvalidRoute::what() const noexcept {
    static std::string msg = "Route named '" + this->_name + "' is invalid";
    return (msg.c_str());
}
