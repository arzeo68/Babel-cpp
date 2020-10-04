//
// Created by alexis on 04/10/2020.
//

#include "NetworkTcp.hpp"

bool NetworkTcp::startConnection(const std::string &ip, const std::string &port) {
    return false;
}

bool NetworkTcp::write(PackageTcp aPackage) {
    return false;
}

PackageTcp NetworkTcp::read() {
    return PackageTcp();
}
