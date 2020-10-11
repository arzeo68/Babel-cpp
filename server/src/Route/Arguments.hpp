/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Route's basic data
*/

#ifndef SRC_SERVER_ROUTE_ARGUMENTS_
#define SRC_SERVER_ROUTE_ARGUMENTS_

#include "common/TCP/CommonPackages.hpp"

namespace Server::Route::Arguments {
    struct RouteHandlerArgs {
        /**
         * HTTP Method for the request
         */
        Common::Method method;
        /**
         * The body is a sequence of arguments
         */
        std::vector<std::string> body;
    };
}

#endif
