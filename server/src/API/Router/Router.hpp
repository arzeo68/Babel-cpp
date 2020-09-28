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

        bool addRoute(Route const &route);
        bool handler(std::string const &routePath, Route::RouteHandlerArgs_t args);
    private:
        std::map<std::string, std::shared_ptr<Route> > _Routes;
    };
}


#endif //BABEL_ROUTER_HPP
