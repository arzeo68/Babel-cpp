/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "common/TCP/CommonPackages.hpp"
#include "Listing.hpp"
#include "server/src/Network/Worker.hpp"

void Server::Route::Listing::_strcpyC(char *dest, const char *source) {
    #ifdef _WIN32
    strcpy_s(dest, sizeof(dest), source);
    #else
    strcpy(dest, source);
    #endif
}

Common::Response
Server::Route::Listing::UserExists(
    std::shared_ptr <Server::Network::Client> client,
    const Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::HTTP_OK,
        "false",
    };
    switch (arg.method) {
        case Common::HTTP_GET:
            if (arg.body.empty())
                return Common::BadRequestTemplate;
            if (client->GetDatabase().UserExists(arg.body[0]))
                _strcpyC(response.msg, "true");
            else
                _strcpyC(response.msg, "false");
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::Login(std::shared_ptr <Server::Network::Client> client,
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
            if (client->GetUserData().IsConnected() ||
                !client->GetDatabase().ConnectUser(arg.body[0], arg.body[1]))
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            id = client->GetNetwork()->AddUserToPool(
                client->shared_from_this());
            client->GetUserData().SetUserName(arg.body[0]);
            _strcpyC(response.msg,
                     std::string(std::to_string(id)).c_str());
            return response;
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::Register(
    std::shared_ptr <Server::Network::Client> client,
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
            if (client->GetUserData().IsConnected() ||
                !client->GetDatabase().AddUser(arg.body[0], arg.body[1]))
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            id = client->GetNetwork()->AddUserToPool(
                client->shared_from_this());
            client->GetUserData().SetUserName(arg.body[0]);
            _strcpyC(response.msg,
                     std::string(std::to_string(id)).c_str());
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response
Server::Route::Listing::SetStatus(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    Common::Response response {
        Common::HTTPCodes_e::HTTP_OK,
        "true",
    };

    switch (arg.method) {
        case Common::HTTP_POST:
            if (arg.body.empty())
                return Common::BadRequestTemplate;
            if (!client->GetUserData().IsConnected())
                return (Common::Response {
                    Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                    "false",
                });
            client->GetDatabase().UpdateStatus(client->GetUserData().GetName(),
                                               arg.body[0]);
            return (response);
        default:
            return Common::InvalidMethodTemplate;
    }
}

Common::Response Server::Route::Listing::HandleFriend(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    if (arg.body.empty())
        return Common::BadRequestTemplate;
    if (arg.method != Common::HTTP_GET) {
        if (!client->GetUserData().IsConnected())
            return (Common::Response {
                Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
                "false",
            });
        if (client->GetUserData().GetName() == arg.body[0])
            return (Common::Response {
                Common::HTTPCodes_e::HTTP_FORBIDDEN,
                "false",
            });
    }
    std::array <Common::Response (*)(std::shared_ptr <Server::Network::Client>,
                                     const Server::Route::Arguments::RouteHandlerArgs &), 5> arr = {
        &Friend::Get,
        &Friend::Delete,
        &Friend::UpdateStatus,
        &Friend::Add
    };
    return (arr[arg.method](client, arg));
}

Common::Response Server::Route::Listing::IsFriendConnected(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    if (arg.body.empty())
        return Common::BadRequestTemplate;
    if (arg.method != Common::HTTP_GET)
        return Common::InvalidMethodTemplate;
    if (!client->GetUserData().IsConnected())
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_UNAUTHORIZED,
            "false",
        });
    auto userName = client->GetUserData().GetName();
    if (userName == arg.body[0])
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_FORBIDDEN,
            "false",
        });
    if (client->GetDatabase().GetFriendStatus(userName, arg.body[0]) !=
        Common::FriendStatus::ACCEPTED)
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_NOT_FOUND,
            "false",
        });
    for (auto &k: client->GetNetwork()->GetClients())
        if (k->GetUserData().GetName() == arg.body[0] &&
            k->GetUserData().IsConnected())
            return (Common::Response {
                Common::HTTPCodes_e::HTTP_OK,
                "true",
            });
    return (Common::Response {
        Common::HTTPCodes_e::HTTP_OK,
        "false",
    });
}
