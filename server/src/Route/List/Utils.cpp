/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "server/src/Network/Worker.hpp"
#include "Callback.hpp"
#include "Utils.hpp"

Common::Response Server::Route::Listing::Utils::ChangeStateCall(
    const std::shared_ptr<Server::Network::Client> &client,
    const std::shared_ptr<Server::Network::Client> &opponent,
    Common::CallState state) {
    Common::Response notification = {
        Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
        "",
    };
    Server::Route::Listing::_strcpyC(notification.msg, std::string(
        "CALL|STATUS|" + client->GetUserData().GetName() + "|" +
        std::to_string(static_cast<uint8_t>(state))).c_str());
    if (state == Common::ACCEPTED)
        Utils::NotifyUserStatusToFriends(client, Utils::UserState::BUSY);
    opponent->GetUserData().SetCallState(state);
    client->GetUserData().SetCallState(state);
    client->GetWorker()->AddNotification(notification,
                                         opponent->GetUserData().GetName());
    return (Common::Response{
        Common::HTTPCodes_e::HTTP_OK,
        "true"
    });
}

Common::Response Server::Route::Listing::Utils::NotifyUserStatusToFriends(
    const std::shared_ptr<Server::Network::Client> &client, UserState state) {
    auto userName = client->GetUserData().GetName();
    auto friendList = client->GetDatabase().GetFriends(userName);
    for (auto &i: friendList.first) {
        std::string friendName = i.first == userName ? i.second : i.first;
        if (auto target = client->GetNetwork()->GetClientFromName(friendName)) {
            Common::Response notification {
                Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
                ""
            };
            switch (state) {
                case UserState::DISCONNECTED:
                    _strcpyC(notification.msg, std::string(
                        "FRIEND|DISCONNECT|" + userName).c_str());
                    break;
                case UserState::CONNECTED:
                    _strcpyC(notification.msg,
                             std::string("FRIEND|CONNECT|" + userName).c_str());
                    break;
                case UserState::BUSY:
                    _strcpyC(notification.msg,
                             std::string("FRIEND|BUSY|" + userName).c_str());
                    break;
            }
            (*target)->GetWorker()->AddNotification(notification, friendName);
        }
    }
    return (Common::Response {
        Common::HTTPCodes_e::HTTP_OK,
        "true"
    });
}
