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
#include "common/Protocol.hpp"
#include "server/src/Route/Arguments.hpp"
#include "server/src/Route/Route.hpp"
#include "server/src/Route/List/Listing.hpp"

namespace Server {
    class Router {
        public:
        Router() = default;
        ~Router() = default;

        static Common::PackageServer FormatRouteArgs(const std::string& string);
        static Route::Arguments::RouteHandlerArgs SplitRawData(const Common::PackageServer& protocol);
        Common::Response Execute(const Common::PackageServer &protocol,
                                 Route::Arguments::RouteHandlerArgs const &args,
                                 Server::Network::Client& client);

        private:
        std::array<Route::Route, Common::MAX_ROUTE_ID> _routes = {
            Route::Route{"USER", &Route::Listing::User},
            Route::Route{"LOGIN", &Route::Listing::Login},
        };
    };
}


#endif //BABEL_ROUTER_HPP
