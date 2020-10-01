/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Data.hpp"

Server::Response
Server::API::Route::Login(Server::Network::Client &client,
                          const Server::Route::RouteHandlerArgs &arg) {

    if (arg.method == Server::Route::GET) {
        bool user = client.GetDatabase().UserExists(arg.body);
        printf("User '%s' exists: %i?\n", arg.body.c_str(), user);
    }
    return {};
}

//Server::Response Server::API::Route::Register(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::UserExist(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::Status(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::Friend(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::PutFriend(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::PostFriend(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::DeleteFriend(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::GetFriends(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::IsConnected(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::StartCall(const Server::Route::RouteHandlerArgs &arg) {
//}

//Server::Response Server::API::Route::EndCall(const Server::Route::RouteHandlerArgs &arg) {
//}
