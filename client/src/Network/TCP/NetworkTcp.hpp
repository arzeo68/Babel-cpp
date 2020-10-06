//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#include <QtNetwork/QTcpSocket>
#include "PackageTcp.hpp"
#include "PackageManagerTcp.hpp"

class NetworkTcp: public INetwork<std::string &, std::string> {
    Q_OBJECT
    public:
    NetworkTcp(PackageManagerTcp &packageManager) : _packageManager(packageManager) {};
    ~NetworkTcp() override { delete _socket; };
    bool startConnection(const std::string &ip, const std::string &port) override;

    signals:

    public slots:

    void connected();
    void disconnected();
    void readyRead();
    void write(Common::PackageServer *, std::string &, Common::Method);

    private:
    QTcpSocket *_socket;
    PackageManagerTcp _packageManager;
};

#endif //BABEL_NETWORKTCP_HPP
