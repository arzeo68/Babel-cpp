//
// Created by alexis on 04/10/2020.
//


#include <iostream>
#include "PackageTcp.hpp"

const char *PackageTcp::toString2(Common::PackageServer *send) {
    char *str = (char *)send;
    delete send;
    return str;
}

Common::Response PackageTcp::toPackage(std::string &string) {
    return *(Common::Response *)string.data();
}

std::string PackageTcp::toString(Common::PackageServer *send) {
    std::string str((char *)send, sizeof(Common::PackageServer));
    return str;
}
