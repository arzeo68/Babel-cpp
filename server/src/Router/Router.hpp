//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

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
        bool Handler(std::string const &routePath, Route::RouteHandlerArgs_t args);
    private:
        std::map<std::string, std::shared_ptr<Route> > _routes;
    };
}


#endif //BABEL_ROUTER_HPP
