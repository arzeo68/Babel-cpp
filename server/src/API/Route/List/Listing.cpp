/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "common/Protocol.hpp"
#include "Listing.hpp"

Common::Response
Server::Route::Listing::User(Server::Network::Client &client,
                             const Common::RouteHandlerArgs &arg) {
    switch (arg.method) {
        case Common::GET:
            if (arg.body.empty())
                return Common::BadRequestTemplate;
            return Common::Response {
                .code = Common::HTTPCodes_e::OK,
                .msg = client.GetDatabase().UserExists(arg.body[0]) ? "true" : "false",
            };
        default: return Common::InvalidMethodTemplate;
    }
}
