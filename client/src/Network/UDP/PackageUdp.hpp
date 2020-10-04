//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGEUDP_HPP
#define BABEL_PACKAGEUDP_HPP

#include <client/src/Network/INetwork.hpp>

class PackageUdp: public IPackage<std::string>
{
    public:
    std::string toString(std::string t) override;

    std::string toPackage(const std::string &string) override;
};

#endif //BABEL_PACKAGEUDP_HPP
