//
// Created by alexis on 04/10/2020.
//


#include "PackageTcp.hpp"

const std::string &PackageTcp::toString(Common::PackageServer *send) {
    std::string str((char *)send);
    return str;
}

Common::Response *PackageTcp::toPackage(std::string &string) {
    return (Common::Response *)string.c_str();
}
