//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_GUICONTROLLER_HPP
#define BABEL_GUICONTROLLER_HPP


#include <map>
#include <iostream>
#include "client/src/Network/TCP/PackageManagerTcp.hpp"
#include "client/src/Network/TCP/NetworkTcp.hpp"
#include "common/TCP/CommonPackages.hpp"

class GUIController {
public:
    GUIController();

    typedef bool (*callback)(Common::Response, Common::Method);

    // GUI Receiver / Sender
    void handler(std::string &str);
    void call(Common::Method method, uint8_t route, Common::PackageServer *pkg);

    // Routes Callback
    bool User(Common::Response r, Common::Method m);
    bool Login(Common::Response r, Common::Method m);
    bool Register(Common::Response r, Common::Method m);

private:
    NetworkTcp _network;
    PackageTcp _package;

    std::queue<uint8_t> _routes;
    std::queue<Common::Method> _methods;

    std::map<uint8_t , bool (GUIController::*)(Common::Response, Common::Method)> _fctPtr;
};


#endif //BABEL_GUICONTROLLER_HPP
