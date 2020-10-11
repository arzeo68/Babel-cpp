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
#include "common/TCP/CommonPackages.hpp"
#include "server/src/Route/Arguments.hpp"
#include "server/src/Route/Route.hpp"
#include "server/src/Route/List/Listing.hpp"

namespace Server {
    class Router {
        public:
        static const constexpr uint8_t MAX_ROUTE_ID = 8;

        static Common::PackageServer FormatRouteArgs(const std::string &string);
        static Route::Arguments::RouteHandlerArgs
        SplitRawData(const Common::PackageServer &protocol);
        Common::Response Execute(const Common::PackageServer &protocol,
                                 Route::Arguments::RouteHandlerArgs const &args,
                                 std::shared_ptr<Server::Network::Client> client);

        private:
        std::array<Route::Route, MAX_ROUTE_ID> _routes = {
            Route::Route {"USER", &Route::Listing::UserExists},
            Route::Route {"LOGIN", &Route::Listing::Login},
            Route::Route {"REGISTER", &Route::Listing::Register},
            Route::Route {"STATUS", &Route::Listing::SetStatus},
            Route::Route {"FRIEND", &Route::Listing::HandleFriend},
            Route::Route {"IS_CONNECTED", &Route::Listing::IsFriendConnected},
            Route::Route {"START_CALL", &Route::Listing::StartCall},
            Route::Route {"END_CALL", &Route::Listing::EndCall},
        };
    };
}


#endif //BABEL_ROUTER_HPP
