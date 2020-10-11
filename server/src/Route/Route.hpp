/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Generic classes used to create the routes for the API
*/

#ifndef BABEL_ROUTE_HPP
#define BABEL_ROUTE_HPP

#include <exception>
#include <string>
#include <list>
#include <map>
#include <vector>
#include "common/TCP/CommonPackages.hpp"
#include "Arguments.hpp"
#include "server/src/Network/Client/Client.hpp"
#include "server/src/DB/Database.hpp"

namespace Server::Route {
    /**
     * Route is class that encapsulate the different API route
     */
    class Route {
        public:
        /**
         * Each route must have a handler that correspond to this signature
         */
        typedef Common::Response (*RouteHandler_t)(
            std::shared_ptr<Server::Network::Client> &,
            const Arguments::RouteHandlerArgs &);

        /**
         * Register a route with a name and a handler
         * @param name Route's name
         * @param handler Route's handler
         */
        Route(const std::string &name, RouteHandler_t handler);
        Route() = default;
        ~Route() = default;
        Route(const Route &obj);

        /**
         * The route's handler is executed with the generic argument below. The response is written on the client's socket
         * @param client Client that called the route
         * @param args Arguments retrieved from the client's request
         * @return The structure response with his data depending on the route behavior
         */
        Common::Response
        ExecuteHandler(std::shared_ptr<Server::Network::Client> &client,
                       const Arguments::RouteHandlerArgs &args) const;
        bool operator==(const std::string &name) const;
        bool operator==(const std::string &name);
        bool operator!=(const std::string &name) const;
        bool operator!=(const std::string &name);

        private:
        std::string _name;
        RouteHandler_t _handler;
        Common::Method _method;
    };
}


#endif //BABEL_ROUTE_HPP
