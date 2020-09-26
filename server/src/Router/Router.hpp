//
// Created by Jean-Gaël Choppe on 26/09/2020.
//

#ifndef BABEL_ROUTER_HPP
#define BABEL_ROUTER_HPP

#include <string>
#include <vector>

namespace Server {
    namespace API {
        class Router {
        public:
            Router();
            ~Router();

            bool addRoute();
            bool handler();
        private:
            std::vector<Route> _Routes;
        };
    }
}


#endif //BABEL_ROUTER_HPP
