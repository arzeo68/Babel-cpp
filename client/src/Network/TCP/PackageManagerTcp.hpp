//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_PACKAGEMANAGERTCP_HPP
#define BABEL_PACKAGEMANAGERTCP_HPP


#include "client/src/GUI/GUIController/GUIController.hpp"
#include "PackageTcp.hpp"
#include <queue>

class PackageManagerTcp {
public:
    PackageManagerTcp(GUIController guiController);

    const char *addRoute(Common::PackageServer *pkg, std::string &str, Common::Method m);
    bool decodePackage(std::string &str);
private:
    GUIController _guiController;
    PackageTcp _package;
    std::queue<std::string> _routes;
    std::queue<Common::Method> _methods;
};


#endif //BABEL_PACKAGEMANAGERTCP_HPP
