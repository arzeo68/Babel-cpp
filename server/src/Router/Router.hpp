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
#include "server/src/API/Route/Route.hpp"
#include "server/src/API/Route/List/Listing.hpp"

namespace Server {
    class Router {
        public:
        Router() = default;
        ~Router() = default;

        static Common::Protocol FormatRouteArgs(const std::string& string);
        static Common::RouteHandlerArgs SplitRawData(const Common::Protocol& protocol);
        Common::Response Execute(const Common::Protocol &protocol,
                                 Common::RouteHandlerArgs const &args,
                                 Server::Network::Client& client);

        private:
        std::array<Route::Route, Common::MAX_ROUTE_ID> _routes = {
            {{"USER", &Route::Listing::User}},
        };
    };
}


#endif //BABEL_ROUTER_HPP
