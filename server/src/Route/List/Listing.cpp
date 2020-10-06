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
        Common::HTTPCodes_e::HTTP_OK,
        "false",
    };
    switch (arg.method) {
        case Common::HTTP_GET:
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
        Common::HTTPCodes_e::HTTP_OK,
        "false",
    };
    uint32_t id;

    switch (arg.method) {
        case Common::HTTP_POST:
            if (arg.body.size() != 2)
                return Common::BadRequestTemplate;
            if (client.GetUserData().IsConnected() ||
                !client.GetDatabase().ConnectUser(arg.body[0], arg.body[1]))
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            id = client.GetNetwork()->AddUserToPool(client.shared_from_this());
            client.GetUserData().SetUserName(arg.body[0]);
            CopyCString(response.msg, std::string(std::to_string(id)).c_str());
            return response;
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::Register(Server::Network::Client &client,
                                 const Server::Route::Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::HTTP_OK,
        "false",
    };
    uint32_t id;

    switch (arg.method) {
        case Common::HTTP_POST:
            if (arg.body.size() != 2)
                return Common::BadRequestTemplate;
            if (client.GetUserData().IsConnected() ||
                !client.GetDatabase().AddUser(arg.body[0], arg.body[1]))
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            id = client.GetNetwork()->AddUserToPool(client.shared_from_this());
            client.GetUserData().SetUserName(arg.body[0]);
            CopyCString(response.msg, std::string(std::to_string(id)).c_str());
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::SetStatus(Server::Network::Client &client,
                                  const Server::Route::Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::HTTP_OK,
        "true",
    };

    switch (arg.method) {
        case Common::HTTP_POST:
            if (arg.body.empty())
                return Common::BadRequestTemplate;
            if (!client.GetUserData().IsConnected())
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            client.GetDatabase().UpdateStatus(client.GetUserData().GetName(), arg.body[0]);
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

