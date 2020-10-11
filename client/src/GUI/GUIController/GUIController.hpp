//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_GUICONTROLLER_HPP
#define BABEL_GUICONTROLLER_HPP


#include <map>
#include <iostream>
#include "client/src/Network/UDP/NetworkUdp.hpp"
#include "client/src/GUI/MainWindow.hpp"
#include "client/src/Network/TCP/NetworkTcp.hpp"
#include "common/TCP/CommonPackages.hpp"

/**
 * The GUI Controller is the main class of the GUI, it manage all GUI:
 * - Communication with the server
 * - Scenes
 * - Updates
 * - Window
 */
class GUIController {
public:

    /**
     * constructor
     */
    GUIController();

    /**
     * run GUI
     */
    void run();

    // GUI Receiver / Sender
    /**
     * handle the TCP server responses
     * @param str the encoded package received by the server
     */
    void handler(std::string &str);

    /**
     * handle the TCP server notifications responses
     * @param res the decoded package received by the server
     */
    void handleNotifications(Common::Response res);

    /**
     * make a request to the server
     * @param method the request method
     * @param route the request route
     * @param pkg the decoded package to send to the server
     */
    void call(Common::Method method, uint8_t route, Common::PackageServer *pkg);

    // Routes Callback
    /**
     * function response to the user request
     * @param r the request response decoded
     * @param m the request method
     */
    void User(Common::Response r, Common::Method m);

    /**
     * function response to the login request
     * @param r the request response decoded
     * @param m the request method
     */
    void Login(Common::Response r, Common::Method m);

    /**
     * function response to the register request
     * @param r the request response decoded
     * @param m the request method
     */
    void Register(Common::Response r, Common::Method m);

    /**
     * function response to the UpdateStatus request
     * @param r the request response decoded
     * @param m the request method
     */
    void UpdateStatus(Common::Response r, Common::Method m);

    /**
     * function response to the Friend's request
     * @param r the request response decoded
     * @param m the request method
     */
    void Friends(Common::Response r, Common::Method m);

    /**
     * function response to the FriendIsConnected request
     * @param r the request response decoded
     * @param m the request method
     */
    void FriendIsConnected(Common::Response r, Common::Method m);

    /**
     * function response to the StartCall request
     * @param r the request response decoded
     * @param m the request method
     */
    void StartCall(Common::Response r, Common::Method m);

    /**
     * function response to the EndCall request
     * @param r the request response decoded
     * @param m the request method
     */
    void EndCall(Common::Response r, Common::Method m);

    // SubRoutes Callback
    /**
     * function response to the PutFriend request
     * @param r the request response decoded
     */
    void PutFriend(Common::Response r);

    /**
     * function response to the PostFriend request
     * @param r the request response decoded
     */
    void PostFriend(Common::Response r);

    /**
     * function response to the DeleteFriend request
     * @param r the request response decoded
     */
    void DeleteFriend(Common::Response r);

    /**
     * function response to the GetFriends request
     * @param r the request response decoded
     */
    void GetFriends(Common::Response r);

    // Notifications Callback
    /**
     * function of the FriendRequest notification
     * @param r the request response decoded
     */
    void FriendRequest(Common::Response r);

    /**
     * function of the FriendStatus notification
     * @param r the request response decoded
     */
    void FriendStatus(Common::Response r);

    /**
     * function of the FriendRemoved notification
     * @param r the request response decoded
     */


    void FriendRemoved(Common::Response r);

    /**
     * function of the FriendList notification
     * @param r the request response decoded
     */
    void FriendList(Common::Response r);

    /**
     * function of the FriendConnect notification
     * @param r
     */
    void FriendConnect(Common::Response r);

    /**
     * function of the FriendDisconnect notification
     * @param r
     */
    void FriendDisconnect(Common::Response r);

    /**
     * function of the FriendBusy notification
     * @param r
     */
    void FriendBusy(Common::Response r);

    /**
     * function of the CallStart notification
     * @param r
     */
    void CallStart(Common::Response r);

    /**
     * function of the CallStatus notification
     * @param r
     */
    void CallStatus(Common::Response r);

private:

    NetworkTcp _network;
    PackageTcp _package;
    MainWindow _mainWindow;

    std::queue<uint8_t> _routes;
    std::queue<Common::Method> _methods;

    std::map<uint8_t , void (GUIController::*)(Common::Response, Common::Method)> _fctPtr;
    std::map<std::string, void (GUIController::*)(Common::Response)> _notificationHandlers;
    std::map<Common::Method, void (GUIController::*)(Common::Response)> _friendsHandlers;
};


#endif //BABEL_GUICONTROLLER_HPP
