/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "common/TCP/CommonPackages.hpp"
#include "Listing.hpp"
#include "server/src/Network/Worker.hpp"

Common::Response Server::Route::Listing::Friend::Add(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    std::string userName = client->GetUserData().GetName();
    Common::Response notification = {
        Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
        "FRIEND|",
    };
    if (client->GetDatabase().GetFriendStatus(userName, arg.body[0]) !=
        Common::FriendStatus::NONE)
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_NOT_FOUND,
            "false",
        });
    if (!client->GetDatabase().AddFriend(userName, arg.body[0]))
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_OK,
            "false",
        });
    else {
        Server::Route::Listing::_strcpyC(notification.msg, std::string(
            "FRIEND|REQUEST|" + userName).c_str());
        client->GetWorker()->AddNotification(notification, arg.body[0]);
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_OK,
            "true",
        });
    }
}

Common::Response Server::Route::Listing::Friend::UpdateStatus(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    if (arg.body.size() != 2)
        return Common::BadRequestTemplate;
    std::string userName = client->GetUserData().GetName();
    Common::Response notification = {
        Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
        "FRIEND|",
    };
    auto status = static_cast<Common::FriendStatus>(std::atoi(
        arg.body[1].c_str()));
    if (client->GetDatabase().GetFriendStatus(userName, arg.body[0]) !=
        Common::FriendStatus::PENDING)
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_NOT_FOUND,
            "false",
        });
    client->GetDatabase().UpdateFriendStatus(userName, arg.body[0], status);
    Server::Route::Listing::_strcpyC(notification.msg, std::string(
        "FRIEND|STATUS|" + userName + "|" + arg.body[1]).c_str());
    client->GetWorker()->AddNotification(notification, arg.body[0]);
    return (Common::Response {
        Common::HTTPCodes_e::HTTP_OK,
        "true"
    });
}

Common::Response Server::Route::Listing::Friend::Delete(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    std::string userName = client->GetUserData().GetName();
    Common::Response notification = {
        Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
        "FRIEND|",
    };
    if (client->GetDatabase().GetFriendStatus(userName, arg.body[0]) !=
        Common::FriendStatus::ACCEPTED)
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_NOT_FOUND,
            "false",
        });
    client->GetDatabase().DeleteFriend(userName, arg.body[0]);
    Server::Route::Listing::_strcpyC(notification.msg, std::string(
        "FRIEND|REMOVE|" + userName).c_str());
    client->GetWorker()->AddNotification(notification, arg.body[0]);
    return (Common::Response {
        Common::HTTPCodes_e::HTTP_OK,
        "true"
    });
}

Common::Response Server::Route::Listing::Friend::Get(
    std::shared_ptr <Server::Network::Client> client,
    const Server::Route::Arguments::RouteHandlerArgs &) {
    Common::Response response = {
        Common::HTTPCodes_e::HTTP_OK,
        "FRIEND|",
    };
    auto friendList = client->GetDatabase().GetFriends(
        client->GetUserData().GetName());
    std::string formattedFriendList = "FRIEND|LIST|";
    for (auto &i: friendList) {
        if ((formattedFriendList.size() + i.size()) >
            Common::g_maxMessageLength) {
            formattedFriendList.erase(formattedFriendList.end() - 1);
            Server::Route::Listing::_strcpyC(response.msg,
                                             formattedFriendList.c_str());
            response.code = Common::HTTPCodes_e::FAKE_HTTP_PAGINATION;
            client->GetWorker()->AddNotification(response,
                                                 client->GetUserData().GetName());
            formattedFriendList = "FRIEND|LIST|";
        }
        formattedFriendList += i + "-";
    }
    formattedFriendList.erase(formattedFriendList.end() - 1);
    Server::Route::Listing::_strcpyC(response.msg, formattedFriendList.c_str());
    if (response.code == Common::HTTPCodes_e::FAKE_HTTP_PAGINATION)
        response.code = Common::HTTPCodes_e::FAKE_HTTP_END_PAGINATION;
    return (response);
}
