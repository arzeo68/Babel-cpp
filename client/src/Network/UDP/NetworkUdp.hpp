//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKUDP_HPP

#include "PackageUdp.hpp"

    class NetworkUDP: public INetwork<const std::string &, std::string &>
{
    public:
    bool startConnection(const std::string &ip, const std::string &port) override;

    };

#endif //BABEL_NETWORKUDP_HPP
