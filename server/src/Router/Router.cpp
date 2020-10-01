/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Router
*/

#include <boost/algorithm/string.hpp>
#include "Router.hpp"

Common::Response Server::Router::Execute(const Common::Protocol &protocol,
                                         Common::RouteHandlerArgs const &args,
                                         Server::Network::Client& client) {
    if (protocol.routeId >= Common::MAX_ROUTE_ID)
        return (Common::Response {
            .code = Common::HTTPCodes_e::NOT_FOUND,
            .msg = "Unknown route"
        });
    else if (protocol.magicBytes != 0xFABA)
        return (Common::Response {
            .code = Common::HTTPCodes_e::FORBIDDEN,
            .msg = "Forbidden"
        });
    else
        return (this->_routes[protocol.routeId].ExecuteHandler(client, args));
}

Common::Protocol Server::Router::FormatRouteArgs(const std::string &string) {
    auto protocol = *(struct Common::Protocol *) string.data();
    return protocol;
}

Common::RouteHandlerArgs
Server::Router::SplitRawData(const Common::Protocol &protocol) {
    Common::RouteHandlerArgs handler;
    std::vector<std::string> subStr;
    boost::split(subStr, std::string(protocol.args), boost::is_any_of("|"));

    if (!subStr.empty())
        handler.token = subStr[0];
    if (subStr.size() > 1)
        for (auto k = subStr.begin() + 1; k != subStr.end(); ++k)
            handler.body.push_back(*k);
    handler.method = protocol.method;
    return (handler);
}
