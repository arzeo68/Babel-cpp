//
// Created by whosdad on 05/10/2020.
//

#include <iostream>
#include "GUIController.hpp"

bool GUIController::handler(Common::Response response, Common::Method method, std::string const &route) {
    if (_fctPtr.find(route) != _fctPtr.end()) {
        std::string msg(response.msg);
        //if (msg != "Unknown route")
            return _fctPtr[route](response, method);
    }
    return false;
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
