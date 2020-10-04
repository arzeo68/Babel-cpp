//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#include "PackageTcp.hpp"

class NetworkTcp: public INetwork<PackageTcp, PackageTcp> {
    public:
    bool startConnection(const std::string &ip, const std::string &port) override;

    bool write(PackageTcp) override;

    PackageTcp read() override;
};

#endif //BABEL_NETWORKTCP_HPP
