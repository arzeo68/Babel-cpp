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
#include "server/src/Network/Client.hpp"
#include "server/src/DB/Database.hpp"

namespace Server::Route {
    namespace Exception {
        class InvalidRoute : std::exception {
            public:
            explicit InvalidRoute(const std::string &name);
            ~InvalidRoute() override = default;
            const char *what() const noexcept override;

            private:
            std::string _name;
        };
    }
    class Route {
        public:
        typedef Common::Response (*RouteHandler_t)(
            std::shared_ptr<Server::Network::Client> &,
            const Arguments::RouteHandlerArgs &);

        Route(const std::string &name, RouteHandler_t handler);
        Route() = default;
        ~Route() = default;
        Route(const Route &obj);

        Common::Response
        ExecuteHandler(std::shared_ptr<Server::Network::Client> &client,
                       const Arguments::RouteHandlerArgs &args) const;
        std::string GetName() const;
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
