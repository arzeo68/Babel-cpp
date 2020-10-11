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
    std::shared_ptr<Server::Network::Client> &client,
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
    std::shared_ptr<Server::Network::Client> &client,
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
    std::shared_ptr<Server::Network::Client> &client,
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
    Server::Route::Listing::_strcpyC(notification.msg, arg.body[0].c_str());
    notification.code = Common::HTTPCodes_e::HTTP_OK;
    return (notification);
}

Common::Response Server::Route::Listing::Friend::Get(
    std::shared_ptr<Server::Network::Client> &client,
    const Server::Route::Arguments::RouteHandlerArgs &) {
    Common::Response response = {
        Common::HTTPCodes_e::HTTP_OK,
        "FRIEND|",
    };
    auto friendList = client->GetDatabase().GetFriends(
        client->GetUserData().GetName());
    std::string formattedFriendList = "FRIEND|LIST|";
    for (auto i = friendList.first.begin(); i != friendList.first.end(); ++i) {
        std::string encodeText =
            *i + "|" + friendList.second[i - friendList.first.begin()] + "|" +
            std::to_string(client->GetNetwork()->IsUserConnected(*i));
        if ((formattedFriendList.size() + encodeText.size()) >
            Common::g_maxMessageLength) {
            formattedFriendList.erase(formattedFriendList.end() - 1);
            Server::Route::Listing::_strcpyC(response.msg,
                                             formattedFriendList.c_str());
            response.code = Common::HTTPCodes_e::FAKE_HTTP_PAGINATION;
            client->GetWorker()->AddNotification(response,
                                                 client->GetUserData().GetName());
            formattedFriendList = "FRIEND|LIST|";
        }
        formattedFriendList += encodeText + "-";
    }
    formattedFriendList.erase(formattedFriendList.end() - 1);
    Server::Route::Listing::_strcpyC(response.msg, formattedFriendList.c_str());
    return (response);
}
