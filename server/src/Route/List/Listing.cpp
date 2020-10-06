/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "common/TCP/CommonPackages.hpp"
#include "Listing.hpp"

void Server::Route::Listing::CopyCString(char* dest, const char* source) {
    #ifdef _WIN32
        strcpy_s(dest, sizeof(dest), source);
    #else
        strcpy(dest, source);
    #endif
}

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
                CopyCString(response.msg, "true");
            else
                CopyCString(response.msg, "false");
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::Login(Server::Network::Client &client,
                              const Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::OK,
        "false",
    };
    uint32_t id;

    switch (arg.method) {
        case Common::POST:
            if (arg.body.size() < 2)
                return Common::BadRequestTemplate;
            id = client.GetNetwork()->AddUserToPool(client.shared_from_this());
            CopyCString(response.msg, std::string(std::to_string(id)).c_str());
            return response;
        default:
            return Common::InvalidMethodTemplate;
    }
}

