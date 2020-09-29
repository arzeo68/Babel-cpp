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
#include <map>
#include <vector>

namespace Server {
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
        enum Method : uint8_t {
            GET,
            DELETE,
            POST,
            PUT
        };
        struct RouteHandlerArgs {
            Method method;
            std::string body;
            std::string token;
        };
        typedef Server::Error (*RouteHandler_t)(RouteHandlerArgs);

        Route(const std::string& name, RouteHandler_t handler);
        ~Route() = default;

        Server::Error ExecuteHandler(RouteHandlerArgs const &args) const;
        std::string GetName() const;

        bool operator==(const std::string& name) const;
        bool operator==(const std::string& name);

        private:
        std::string _name;
        RouteHandler_t _handler;
        Method _method;
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
        Server::Error ExecuteRouteHandler(const std::string& route,
                                                   Route::RouteHandlerArgs const &args);

        RouteList_t::iterator begin();
        RouteList_t::iterator end();

        private:
        RouteList_t _container;
    };
}


#endif //BABEL_ROUTE_HPP
