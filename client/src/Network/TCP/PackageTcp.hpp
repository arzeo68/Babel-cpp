//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include "client/src/Network/INetwork.hpp"
#include "client/src/Network/IPackage.hpp"
#include "common/TCP/CommonPackages.hpp"


class PackageTcp: public IPackage<Common::PackageServer *, Common::Response> {
    public:
    std::string toString(Common::PackageServer *send) override;
    const char *toString2(Common::PackageServer *send);

    Common::Response toPackage(std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP