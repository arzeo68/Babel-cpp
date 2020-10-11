//
// Created by whosdad on 05/10/2020.
//

#include <iostream>
#include "client/src/GUI/Scenes/MainScene.hpp"
#include "client/src/GUI/Scenes/LoginScene.hpp"
#include "GUIController.hpp"

GUIController::GUIController() : _network(this), _mainWindow(this) {
    // declare routes callback map ptr
    _fctPtr[0] = &GUIController::User;
    _fctPtr[1] = &GUIController::Login;
    _fctPtr[2] = &GUIController::Register;
    _fctPtr[3] = &GUIController::UpdateStatus;
    _fctPtr[4] = &GUIController::Friends;
    _fctPtr[5] = &GUIController::FriendIsConnected;
    _fctPtr[6] = &GUIController::StartCall;
    _fctPtr[7] = &GUIController::EndCall;

    // declare sub routes callback map ptr
    _friendsHandlers[Common::Method::HTTP_PUT] = &GUIController::PutFriend;
    _friendsHandlers[Common::Method::HTTP_POST] = &GUIController::PostFriend;
    _friendsHandlers[Common::Method::HTTP_DELETE] = &GUIController::DeleteFriend;
    _friendsHandlers[Common::Method::HTTP_GET] = &GUIController::GetFriends;

    // declare notifications callback map ptr
    _notificationHandlers["FRIEND|REQUEST"] = &GUIController::FriendRequest;
    _notificationHandlers["FRIEND|STATUS"] = &GUIController::FriendStatus;
    _notificationHandlers["FRIEND|REMOVE"] = &GUIController::FriendRemoved;
    _notificationHandlers["FRIEND|LIST"] = &GUIController::FriendList;
    _notificationHandlers["FRIEND|CONNECT"] = &GUIController::FriendConnect;
    _notificationHandlers["FRIEND|BUSY"] = &GUIController::FriendBusy;
    _notificationHandlers["FRIEND|DISCONNECT"] = &GUIController::FriendDisconnect;
    _notificationHandlers["CALL|START"] = &GUIController::CallStart;
    _notificationHandlers["CALL|STATUS"] = &GUIController::CallStatus;
    _network.startConnection("", "");
}

void GUIController::handler(std::string &str) {
    std::cout << "GUIController handler..." << std::endl;
    Common::Response res = _package.toPackage(str);

    std::string msg(res.msg);
    std::cout << msg << std::endl;
    std::cout << std::to_string((int)res.code) << std::endl;
    if ((res.code != Common::HTTPCodes_e::HTTP_OK && res.code != Common::HTTPCodes_e::FAKE_HTTP_PAGINATION && res.code != Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION)
    && msg.find("FRIEND") == 0) {
        std::cout << "Bad pagination" << std::endl;
        return;
    }
    if (res.code == Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION ||
        res.code == Common::HTTPCodes_e::FAKE_HTTP_PAGINATION) {
        handleNotifications(res);
        return;
    }
    uint8_t const r = _routes.front();
    Common::Method m = _methods.front();
    if (_fctPtr.find(r) != _fctPtr.end()) {
        _routes.pop();
        _methods.pop();
        (this->*_fctPtr[r])(res, m);
    }
}

void GUIController::handleNotifications(Common::Response res) {
    std::cout << "handleNotifications..." << std::endl;
    std::string msg(res.msg);

    std::string msg1 = msg.substr(msg.find_first_of('|') + 1);
    std::string notification = msg.substr(0,msg.find_first_of('|') + msg1.find_first_of('|') + 1);

    std::cout << notification << std::endl;

    if (_notificationHandlers.find(notification) != _notificationHandlers.end()) {
        (this->*_notificationHandlers[notification])(res);
    }
}

void GUIController::call(Common::Method method, uint8_t route, Common::PackageServer *pkg) {
    std::string string = _package.toString(pkg);

    if (route == 4 && method == Common::Method::HTTP_GET) {
        std::cout << "Call will return pagination..." << std::endl;
    } else {
        std::cout << "Call will not return pagination..." << std::endl;
        _routes.push(route);
        _methods.push(method);
    }
    std::cout << "Call..." << std::endl;
    _network.write(string.c_str());
}

void GUIController::run() {
    _mainWindow.show();
}

void GUIController::User(Common::Response r, Common::Method m) {
    (void)m;
    dynamic_cast<LoginScene *>(_mainWindow.getSceneManager().getScenes().at("login"))->userExist(r);
    std::cout << "user callback: " << r.msg << std::endl;
}

void GUIController::Login(Common::Response r, Common::Method m) {
    (void)m;
    dynamic_cast<LoginScene *>(_mainWindow.getSceneManager().getScenes().at("login"))->userLogin(r);
    std::cout << "login callback: " << r.msg << std::endl;
}

void GUIController::Register(Common::Response r, Common::Method m) {
    (void)m;
    dynamic_cast<LoginScene *>(_mainWindow.getSceneManager().getScenes().at("login"))->userLogin(r);
    std::cout << "register callback: " << r.msg << std::endl;
}

void GUIController::UpdateStatus(Common::Response r, Common::Method m) {
    (void)m;
    std::cout << "update status callback: " << r.msg << std::endl;
}

void GUIController::Friends(Common::Response r, Common::Method m) {
    std::cout << "friends callback: " << r.msg << std::endl;
    if (_friendsHandlers.find(m) != _friendsHandlers.end()) {
        (this->*_friendsHandlers[m])(r);
    }
}

void GUIController::FriendIsConnected(Common::Response r, Common::Method m) {
    (void)m;
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->friendIsConnected(r);
    std::cout << "friend is connected callback: " << r.msg << std::endl;
}

void GUIController::PutFriend(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->fillFriend(r);
    std::cout << "putFriends callback: " << r.msg << std::endl;
}

void GUIController::PostFriend(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->responseRequest(r);
    std::cout << "postFriends callback: " << r.msg << std::endl;
}

void GUIController::DeleteFriend(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->deleteFriend(r);
    std::cout << "deleteFriends callback: " << r.msg << std::endl;
}

void GUIController::GetFriends(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->fillFriendsList(r);
    std::cout << "getFriends callback: " << r.msg << std::endl;
}

void GUIController::FriendRequest(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->requestFriend(r);
    std::cout << "Notification friend request" << std::endl;
}

void GUIController::FriendStatus(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->responseRequestFriend(r);
    std::cout << "Notification friend status" << std::endl;
}

void GUIController::FriendRemoved(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->deleteFriendNotif(r);
    std::cout << "Notification friend Remove" << std::endl;
}

void GUIController::FriendList(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->fillFriendsList(r);
    std::cout << "Notification friend list" << std::endl;
}

void GUIController::CallStart(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->callNotification(r);
    std::cout << "Notification call start" << std::endl;
}

void GUIController::CallStatus(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getCallGUI()->acceptedCall(r);
    std::cout << "Notification call status" << std::endl;
}

void GUIController::StartCall(Common::Response r, Common::Method m) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->infosCall(r);
}

void GUIController::EndCall(Common::Response r, Common::Method m) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->endCall(r);
}

void GUIController::FriendConnect(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->friendConnectedNotif(r);
    std::cout << "Notification call connect" << std::endl;
}

void GUIController::FriendDisconnect(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->friendDisonnectedNotif(r);
    std::cout << "Notification call disconnect" << std::endl;
}

void GUIController::FriendBusy(Common::Response r) {
    dynamic_cast<MainScene *>(_mainWindow.getSceneManager().getScenes().at("main"))->getFriendsList()->friendBusyNotif(r);
    std::cout << "Notification call busy" << std::endl;
}

NetworkUDP &GUIController::getUdp() {
    return _udp;
}
