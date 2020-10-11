/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "server/src/Network/Worker.hpp"
#include "Listing.hpp"
#include "CallUtils.hpp"

Common::Response Server::Route::Listing::Utils::ChangeStateCall(
    const std::shared_ptr<Server::Network::Client> &client,
    const std::shared_ptr<Server::Network::Client> &opponent,
    Common::CallState state) {
    Common::Response notification = {
        Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
        "",
    };
    Server::Route::Listing::_strcpyC(notification.msg, std::string(
        "CALL|" + client->GetUserData().GetName() + "|" +
        std::to_string(static_cast<uint8_t>(state))).c_str());
    printf("Changing state call of (opp: '%s') & sender: '%s' w/ %i\n",
           client->GetUserData().GetName().c_str(),
           opponent->GetUserData().GetName().c_str(),
           (uint8_t) state);
    opponent->GetUserData().SetCallState(state);
    client->GetUserData().SetCallState(state);
    client->GetWorker()->AddNotification(notification,
                                         opponent->GetUserData().GetName());
    return (Common::Response {
        Common::HTTPCodes_e::HTTP_OK,
        "true"
    });
}
