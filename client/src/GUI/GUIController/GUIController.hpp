//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_GUICONTROLLER_HPP
#define BABEL_GUICONTROLLER_HPP


#include "common/TCP/CommonPackages.hpp"
#include <map>
#include <iostream>

class GUIController {
public:
    GUIController() = default;
    typedef bool (*callback)(Common::Response, Common::Method);


    bool handler(Common::Response response, Common::Method method, std::string const &route);

    // Routes Callback
    static bool User(Common::Response r, Common::Method m);
    static bool Login(Common::Response r, Common::Method m);
    static bool Register(Common::Response r, Common::Method m);

private:
    std::map<std::string, callback> _fctPtr = {
            {"user", User},
            {"login", Login},
            {"register", Register},
    };
};


#endif //BABEL_GUICONTROLLER_HPP
