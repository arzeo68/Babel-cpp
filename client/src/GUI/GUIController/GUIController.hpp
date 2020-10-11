//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_GUICONTROLLER_HPP
#define BABEL_GUICONTROLLER_HPP


#include <map>
#include <iostream>
#include "client/src/Network/UDP/NetworkUdp.hpp"
#include "client/src/GUI/MainWindow.hpp"
#include "client/src/Network/TCP/PackageManagerTcp.hpp"
#include "client/src/Network/TCP/NetworkTcp.hpp"
#include "common/TCP/CommonPackages.hpp"

//! GUIController class
/*!
  The GUI Controller is the main class of the GUI, it manage all GUI:
  - Network
  - Scenes
  - Window
*/
class GUIController {
public:
    GUIController();

    void run();

    // GUI Receiver / Sender
    void handler(std::string &str);
    void handleNotifications(Common::Response res);
    void call(Common::Method method, uint8_t route, Common::PackageServer *pkg);

    // Routes Callback
    void User(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void Login(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void Register(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void UpdateStatus(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void Friends(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void FriendIsConnected(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void StartCall(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);
    void EndCall(Common::Response r /**< [in] the response sent by the server. */, Common::Method m /**< [in] the method initially called */);

    // SubRoutes Callback
    void PutFriend(Common::Response r /**< [in] the response sent by the server. */);
    void PostFriend(Common::Response r /**< [in] the response sent by the server. */);
    void DeleteFriend(Common::Response r /**< [in] the response sent by the server. */);
    void GetFriends(Common::Response r /**< [in] the response sent by the server. */);

    // Notifications Callback
    void FriendRequest(Common::Response r /**< [in] the response sent by the server. */);
    void FriendStatus(Common::Response r /**< [in] the response sent by the server. */);
    void FriendRemoved(Common::Response r /**< [in] the response sent by the server. */);
    void FriendList(Common::Response r /**< [in] the response sent by the server. */);
    void FriendConnect(Common::Response r /**< [in] the response sent by the server. */);
    void FriendDisconnect(Common::Response r /**< [in] the response sent by the server. */);
    void FriendBusy(Common::Response r /**< [in] the response sent by the server. */);
    void CallStart(Common::Response r /**< [in] the response sent by the server. */);
    void CallStatus(Common::Response r /**< [in] the response sent by the server. */);

private:

    NetworkTcp _network; //!< manage TCP Communication (sender/receiver)
    PackageTcp _package; //!< encode and decode packages send and received
    MainWindow _mainWindow; //!< manage GUI

    std::queue<uint8_t> _routes; //!< queue of actual routes called
    std::queue<Common::Method> _methods; //!<queue of actual methods called

    std::map<uint8_t , void (GUIController::*)(Common::Response, Common::Method)> _fctPtr; //!< map of functions ptr for simple routes
    std::map<std::string, void (GUIController::*)(Common::Response)> _notificationHandlers; //!< map of functions ptr for notifications
    std::map<Common::Method, void (GUIController::*)(Common::Response)> _friendsHandlers; //!< map of functions ptr for sub-routes friends (GET, PUT, DELETE...)
};


#endif //BABEL_GUICONTROLLER_HPP
