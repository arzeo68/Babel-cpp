//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include "client/src/Network/INetwork.hpp"
#include "../../Package/IPackage.hpp"


class PackageTcp: public IPackage<std::string, std::string> {
    public:
    std::string toString(std::string t) override;

    std::string toPackage(const std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP
