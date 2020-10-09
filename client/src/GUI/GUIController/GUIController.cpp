//
// Created by whosdad on 05/10/2020.
//

#include <iostream>
#include "GUIController.hpp"

GUIController::GUIController() : _network(this) {
    _fctPtr[0] = &GUIController::User;
    _fctPtr[1] = &GUIController::Login;
    _fctPtr[2] = &GUIController::Register;
    _network.startConnection("", "");
}

void GUIController::handler(std::string &str) {
    uint8_t const r = _routes.front();
    Common::Method m = _methods.front();
    Common::Response res = _package.toPackage(str);

    _routes.pop();
    _methods.pop();
    if (_fctPtr.find(r) != _fctPtr.end()) {
        std::string msg(res.msg);
        //if (msg != "Unknown route")
            (this->*_fctPtr[r])(res, m);
    }
}

void GUIController::call(Common::Method method, uint8_t route, Common::PackageServer *pkg) {
    std::string string = _package.toString(pkg);

    _routes.push(route);
    _methods.push(method);
    _network.write(string.c_str());
}

bool GUIController::User(Common::Response r, Common::Method m) {
    std::cout << "user callback: " << r.msg << std::endl;
    return false;
}

bool GUIController::Login(Common::Response r, Common::Method m) {
    std::cout << "login callback: " << r.msg << std::endl;
    return false;
}

bool GUIController::Register(Common::Response r, Common::Method m) {
    std::cout << "register callback: " << r.msg << std::endl;
    return false;
}