//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#ifndef BABEL_ROUTER_HPP
#define BABEL_ROUTER_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Server {
    namespace API {
        class Router {
        public:
            Router();

            bool addRoute(std::shared_ptr<Route>);
            bool handler(std::string routePath);
        private:
            std::map<std::string, std::shared_ptr<Route> > _Routes;
        };
    }
}


#endif //BABEL_ROUTER_HPP
