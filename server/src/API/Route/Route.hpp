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
#include "HTTPCodes.hpp"
#include "Error.hpp"

namespace Server::API {
    namespace Exception {
        class InvalidRoute : std::exception {
            public:
            explicit InvalidRoute(const std::string& name);
            ~InvalidRoute() override = default;

            const char* what() const noexcept override;

            private:
            std::string _name;
        };
    }
    class Route {
        public:
        typedef const char** RouteHandlerArgs_t;
        typedef Server::API::Error (*RouteHandler_t)(RouteHandlerArgs_t);

        Route(const std::string& name, RouteHandler_t handler);
        ~Route() = default;

        Server::API::Error ExecuteHandler(RouteHandlerArgs_t args) const;
        std::string GetName() const;

        bool operator==(const std::string& name) const;
        bool operator==(const std::string& name);

        private:
        std::string _name;
        RouteHandler_t _handler;
    };

    class RouteContainer {
        public:
        typedef std::list<Route> RouteList_t;

        RouteContainer() = default;
        RouteContainer(const Route&& route);
        RouteContainer(const RouteList_t&& route);
        ~RouteContainer() = default;

        void PushBackRoute(const Route& route);
        void PushBackRoute(const Route&& route);

        bool Exists(const std::string& RouteName);
        HTTPCodes::HTTPCodes_t ExecuteRouteHandler(const std::string& route,
                                                   Route::RouteHandlerArgs_t args);

        RouteList_t::iterator begin();
        RouteList_t::iterator end();

        private:
        RouteList_t _container;
    };
}


#endif //BABEL_ROUTE_HPP
