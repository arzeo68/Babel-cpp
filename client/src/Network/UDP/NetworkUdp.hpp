//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKUDP_HPP

#include <QtNetwork/qudpsocket.h>

#include "client/src/package/PackageManager.hpp"
#include "PackageUdp.hpp"

class NetworkUDP: public INetwork<std::string, std::string>
{
    public:
    NetworkUDP();

    bool startConnection(const std::string &ip, const std::string &port) override;

    bool write(std::string t) override;

    std::string read() override;

    void packageReadyToSendCallback();

    private:
    int _port;
    std::string _ip;
    std::shared_ptr<PackageManager> _packageManger;
    std::shared_ptr<QUdpSocket> _socket;
};

#endif //BABEL_NETWORKUDP_HPP
