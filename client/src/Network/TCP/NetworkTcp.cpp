//
// Created by alexis on 04/10/2020.
//

#include <iostream>
#include <QtNetwork/QHostAddress>
#include "NetworkTcp.hpp"

// ip should be a QHostAddress & port should be an int (and should maybe return the UUID of client)
bool NetworkTcp::startConnection(const std::string &ip, const std::string &port) {
    _socket = new QTcpSocket();

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    _socket->connectToHost(QHostAddress::LocalHost, 4243);

    if (!_socket->waitForConnected(5000)) {
        std::cout << "socket " << &_socket << std::endl;
        return false;
    }
    std::cout << "socket " << &_socket << " connected to localhost on 4243" << std::endl;
    return true;
}

void NetworkTcp::connected() {
    std::cout << "socket " << &_socket << " connected" << std::endl;
}

void NetworkTcp::disconnected() {
    std::cout << "close socket " << &_socket << std::endl;
    _socket->close();
}

void NetworkTcp::readyRead() {
    std::cout << "socket " << &_socket << " is ready to read" << std::endl;
    std::string str = _socket->read(sizeof(Common::Response)).toStdString();
    _packageManager.decodePackage(str);
}

void NetworkTcp::write(Common::PackageServer *pkg, std::string &str, Common::Method m) {
    _socket->write(_packageManager.addRoute(pkg, str, m), sizeof(Common::PackageServer));
}
