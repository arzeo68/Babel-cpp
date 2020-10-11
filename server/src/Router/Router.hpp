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
#include "server/src/Route/List/Callback.hpp"

namespace Server {
    /**
     * Router register all route, retrieve raw data, parse it and dispatch it in the aimed route
     */
    class Router {
        public:
        static const constexpr uint8_t MAX_ROUTE_ID = 8;

        /**
         * From a string, the function parse and retrieve data that will be stored in the returned structure
         * @param string Raw string for the client's input
         * @return A server package
         */
        static Common::PackageServer FormatRouteArgs(const std::string &string);
        /**
         * From an higher data level, the function retrieve the arguments and return it in the a structure
         * @param protocol Server package retrieved by the previous function: FormatRouteArgs
         * @return A structure with all the route's arguments
         */
        static Route::Arguments::RouteHandlerArgs
        SplitRawData(const Common::PackageServer &protocol);
        /**
         * Execute the route's handler
         * @param protocol Package server with the route data
         * @param args The route's arguments
         * @param client Client, caller of the route
         * @return A response from the route
         */
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
