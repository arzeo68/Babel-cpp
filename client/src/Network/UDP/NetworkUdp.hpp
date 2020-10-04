//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKUDP_HPP

#include "PackageUdp.hpp"

class NetworkUDP: public INetwork<PackageUdp, PackageUdp>
{
    public:
    bool startConnection(const std::string &ip, const std::string &port) override;

    bool write(PackageUdp Package) override;

    PackageUdp read() override;
};

#endif //BABEL_NETWORKUDP_HPP
