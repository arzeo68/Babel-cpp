//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_GUICONTROLLER_HPP
#define BABEL_GUICONTROLLER_HPP


#include <map>
#include <iostream>
#include "client/src/GUI/MainWindow.hpp"
#include "client/src/Network/TCP/PackageManagerTcp.hpp"
#include "client/src/Network/TCP/NetworkTcp.hpp"
#include "common/TCP/CommonPackages.hpp"

class GUIController {
public:
    GUIController();

    int run();

    // GUI Receiver / Sender
    void handler(std::string &str);
    void handleNotifications(Common::Response res);
    void call(Common::Method method, uint8_t route, Common::PackageServer *pkg);

    // Routes Callback
    void User(Common::Response r, Common::Method m);
    void Login(Common::Response r, Common::Method m);
    void Register(Common::Response r, Common::Method m);
    void UpdateStatus(Common::Response r, Common::Method m);
    void Friends(Common::Response r, Common::Method m);
    void FriendIsConnected(Common::Response r, Common::Method m);

    // SubRoutes Callback
    void PutFriend(Common::Response r, Common::Method m);
    void PostFriend(Common::Response r, Common::Method m);
    void DeleteFriend(Common::Response r, Common::Method m);
    void GetFriends(Common::Response r, Common::Method m);

private:

    NetworkTcp _network;
    PackageTcp _package;
    MainWindow _mainWindow;

    std::queue<uint8_t> _routes;
    std::queue<Common::Method> _methods;

    std::map<uint8_t , void (GUIController::*)(Common::Response, Common::Method)> _fctPtr;
    std::map<std::string, void (GUIController::*)(Common::Response)> _notificationHandlers;
    std::map<Common::Method, void (GUIController::*)(Common::Response, Common::Method)> _friendsHandlers;
};


#endif //BABEL_GUICONTROLLER_HPP
