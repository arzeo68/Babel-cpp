//
// Created by whosdad on 05/10/2020.
//

#include "PackageManagerTcp.hpp"

PackageManagerTcp::PackageManagerTcp(GUIController guiController) : _guiController(guiController)
{

}

bool PackageManagerTcp::decodePackage(std::string &str) {
    std::string const r = _routes.front();
    Common::Method m = _methods.front();
    _routes.pop();
    _methods.pop();
    return _guiController.handler(_package.toPackage(str), m, r);
}

const char *PackageManagerTcp::addRoute(Common::PackageServer *pkg, std::string &route, Common::Method method) {
    _routes.push(route);
    _methods.push(method);
    std::string string = _package.toString(pkg);
    return string.c_str();
}
