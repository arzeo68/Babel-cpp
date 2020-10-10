//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#include <QtNetwork/QTcpSocket>
#include "PackageTcp.hpp"

class GUIController;

class PackageManagerTcp;

class NetworkTcp: public INetwork<std::string &, std::string> {
    Q_OBJECT
    public:
    NetworkTcp(GUIController *g) : _guiController(g) {};
    ~NetworkTcp() override { delete _socket; };
    bool startConnection(const std::string &ip, const std::string &port) override;

    signals:
    public slots:

    void connected();
    void disconnected();
    void readyRead();
    void write(const char *pkg);

    private:
    GUIController *_guiController;
    QTcpSocket *_socket;
};

#endif //BABEL_NETWORKTCP_HPP
