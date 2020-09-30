/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Router
*/

#ifndef BABEL_ROUTER_HPP
#define BABEL_ROUTER_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "../Route/Route.hpp"

namespace Server {
    class Router {
    public:
        Router();

        bool AddRoute(Route const &route);
        Server::Response Handler(std::string const &routePath, Route::RouteHandlerArgs const &args);

    private:
        std::map<std::string, Route> _routes;
    };
}


#endif //BABEL_ROUTER_HPP
