/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Generic classes used to create the routes for the API
*/

#include <algorithm>
#include "Route.hpp"

Server::Route::Route(const std::string &name,
                          Server::Route::RouteHandler_t handler) :
                          _name(name), _handler(handler) {
}

Server::Response
Server::Route::ExecuteHandler(Server::Route::RouteHandlerArgs const &args) const {
    return (this->_handler(args));
}

std::string Server::Route::GetName() const {
    return (this->_name);
}

bool Server::Route::operator==(const std::string &name) {
    return (this->_name == name);
}

bool Server::Route::operator==(const std::string &name) const {
    return (this->_name == name);
}

Server::Route::Route(const Route &obj) {
    this->_handler = obj._handler;
    this->_name = obj._name;
    this->_method = obj._method;
}


Server::RouteContainer::RouteContainer(const Server::Route &&route) {
    this->_container.push_back(route);
}

Server::RouteContainer::RouteContainer(const RouteList_t &&route) {
    this->_container = route;
}

void Server::RouteContainer::PushBackRoute(const Server::Route &route) {
    this->_container.push_back(route);
}

void Server::RouteContainer::PushBackRoute(const Server::Route &&route) {
    this->_container.push_back(route);
}

Server::RouteContainer::RouteList_t::iterator Server::RouteContainer::begin() {
    return (this->_container.begin());
}

Server::RouteContainer::RouteList_t::iterator Server::RouteContainer::end() {
    return (this->_container.end());
}

bool Server::RouteContainer::Exists(const std::string& RouteName) {
    return (std::find(this->_container.begin(), this->_container.end(), RouteName) != this->_container.end());
}

Server::Response
Server::RouteContainer::ExecuteRouteHandler(const std::string &route, Route::RouteHandlerArgs const &args) {
    auto r = std::find(this->_container.begin(), this->_container.end(), route);
    if (r == this->_container.end())
        throw Exception::InvalidRoute(route);
    return (r->ExecuteHandler(args));
}

Server::Exception::InvalidRoute::InvalidRoute(const std::string &name) : _name(name) {
}

const char *Server::Exception::InvalidRoute::what() const noexcept {
    static std::string msg = "Route named '" + this->_name + "' is invalid";
    return (msg.c_str());
}
