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
                             const Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::OK,
        "false",
    };
    switch (arg.method) {
        case Common::GET:
            if (arg.body.empty())
                return Common::BadRequestTemplate;
            if (client.GetDatabase().UserExists(arg.body[0]))
                strcpy(response.msg, "true");
            else
                strcpy(response.msg, "false");
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}
//
//Common::Response
//Server::Route::Listing::Login(Server::Network::Client &client,
//                              const RouteHandlerArgs &arg) {
//    switch (arg.method) {
//        case Common::POST:
//            if (arg.body.size() < 2)
//                return Common::BadRequestTemplate;
//            return Common::Response{
//                .code = Common::HTTPCodes_e::OK,
//                .msg = client.GetDatabase().ConnectUser(args.body[0],
//                                                        args.body[1]),
//            };
//        default:
//            return Common::InvalidMethodTemplate;
//    }
//}

