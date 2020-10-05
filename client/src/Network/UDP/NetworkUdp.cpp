//
// Created by alexis on 04/10/2020.
//

#include "common/Error/ThrowError.hpp"
#include "NetworkUdp.hpp"

NetworkUDP::NetworkUDP(): _socket(std::make_shared<QUdpSocket>(this)
)
{
}

bool NetworkUDP::startConnection(const std::string &ip, const std::string &port)
{
    _port = std::stoi(port);
    _ip = ip;
    if (! _socket->bind(QHostAddress::Any, _port))
        return false;
    QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(read()));
}

bool NetworkUDP::write(std::string t)
{
    _socket->writeDatagram(t.c_str(), 972, QHostAddress(QString(_ip.c_str())), _port);
    return false;
}

std::string NetworkUDP::read()
{
    QHostAddress host;
    quint16 port;
    unsigned int byteToRead = _socket->bytesAvailable();

    if (byteToRead == 0) {
        return "";
    }
    std::unique_ptr<char[]> buffer(new char[byteToRead]);
    int size = _socket->readDatagram(buffer.get(), byteToRead, &host, &port);
    if (size == -1)
        throw ThrowError("fail QUdpSocket::read");
//    message.msg.insert(message.msg.end(), buffer.get(), buffer.get() + message.msgSize);
//    message.host = host.toString().toStdString();
//    message.port = port;
//    mIsReadable = false;
std::cout << "package received" << std::endl;
    _packageManger->handlePackage(buffer.get(), size);
    return std::string(buffer.get(), size);
}

void NetworkUDP::packageReadyToSendCallback()
{

}




