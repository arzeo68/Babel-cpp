//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include "client/src/Network/INetwork.hpp"
#include "client/src/Network/IPackage.hpp"


class PackageTcp: public IPackage<std::string &, std::string &> {
    public:
    const std::string &toString(std::string &send) override;

    std::string &toPackage(std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP
