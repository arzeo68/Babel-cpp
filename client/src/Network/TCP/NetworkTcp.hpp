//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#include "PackageTcp.hpp"

class NetworkTcp: public INetwork<std::string &, std::string> {
    public:
    bool startConnection(const std::string &ip, const std::string &port) override;

    bool write(std::string &) override;

    std::string read() override;
};

#endif //BABEL_NETWORKTCP_HPP
