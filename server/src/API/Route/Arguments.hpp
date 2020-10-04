/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_SERVER_ROUTE_ARGUMENTS_
#define SRC_SERVER_ROUTE_ARGUMENTS_

#include "common/Protocol.hpp"

namespace Server::Route::Arguments {
    struct RouteHandlerArgs {
        Common::Method method;
        std::vector<std::string> body;
        std::string token;
    };
}

#endif
