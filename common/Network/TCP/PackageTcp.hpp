//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include "client/src/Network/INetwork.hpp"
<<<<<<<< HEAD:common/Network/TCP/PackageTcp.hpp
#include "../../Package/IPackage.hpp"


class PackageTcp: public IPackage<std::string, std::string> {
========
#include "client/src/Network/IPackage.hpp"
#include "common/TCP/CommonPackages.hpp"


class PackageTcp: public IPackage<Common::PackageServer *, Common::Response> {
>>>>>>>> 70d82ac... feat(client): adding secodary template:client/src/Network/TCP/PackageTcp.hpp
    public:
    std::string toString(Common::PackageServer *send) override;
    const char *toString2(Common::PackageServer *send);

    Common::Response toPackage(std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP
