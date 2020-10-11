//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGETCP_HPP
#define BABEL_PACKAGETCP_HPP

#include <common/TCP/CommonPackages.hpp>
#include "client/src/Network/INetwork.hpp"
#include "../../package/IPackage.hpp"


/**
 * PackageTcp encode and decode package for the TCP Communication
 */
class PackageTcp: public IPackage<Common::PackageServer *, Common::Response> {
    public:

    /**
     * encode package to send
     * @param send package to encode
     * @return
     */
    std::string toString(Common::PackageServer *send) override;
    const char *toString2(Common::PackageServer *send);

    /**
     * decode package received
     * @param string package to decode
     * @return
     */
    Common::Response toPackage(std::string &string) override;
};

#endif //BABEL_PACKAGETCP_HPP
