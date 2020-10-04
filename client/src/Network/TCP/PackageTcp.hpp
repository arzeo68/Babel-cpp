//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include "../INetwork.hpp"

class PackageTcp: public IPackage<std::string>
{
    public:
    std::string toString(std::string t) override;

    std::string toPackage(const std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP
