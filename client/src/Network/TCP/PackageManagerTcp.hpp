//
// Created by whosdad on 05/10/2020.
//

#ifndef BABEL_PACKAGEMANAGERTCP_HPP
#define BABEL_PACKAGEMANAGERTCP_HPP


#include "PackageTcp.hpp"
#include <queue>

class PackageManagerTcp {
public:
    PackageManagerTcp();

    const char *addRoute(Common::PackageServer *pkg, std::string &str, Common::Method m);
    Common::Response decodePackage(std::string &str);

private:
    PackageTcp _package;
    std::queue<std::string> _routes;
    std::queue<Common::Method> _methods;
};


#endif //BABEL_PACKAGEMANAGERTCP_HPP
