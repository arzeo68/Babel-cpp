//
// Created by alexis on 04/10/2020.
//

#include "common/Error/ThrowError.hpp"
#include "NetworkUdp.hpp"

#include <utility>

NetworkUDP::NetworkUDP(): _packageManger(std::make_shared<PackageManager>())
{
}

bool NetworkUDP::startConnection(const std::string &ip, const std::string &port)
{
    _socket = (new QUdpSocket(this));
    _port = 7755;
    _ip = ip;
    if ( _socket->bind(QHostAddress::LocalHost, _port) == 0)
    {
        throw ThrowError("QUdpSocket bind failed");
    }
    connect(_socket, SIGNAL(readyRead()),this, SLOT(markAsReadable()));
    _packageManger->getPa()->setSoundCallBack(this);
    _packageManger->start();
}

bool NetworkUDP::write(std::string t)
{
    int res = _socket->writeDatagram(t.c_str(), 972, QHostAddress::LocalHost, _port);
    if (res == 972)
        return true;
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
    _packageManger->handlePackage(buffer.get(), size);
    return std::string(buffer.get(), size);
}

void NetworkUDP::packageReadyToSendCallback()
{
    sendSound(_packageManger->getPaNextSound());

}

void NetworkUDP::markAsReadable(void)
{
    read();
}

void NetworkUDP::sendSound(std::shared_ptr<Babel::Audio::soundDecoded> data)
{
    std::shared_ptr<Babel::Audio::soundEncoded> encoded = _packageManger->getEncoder()->encode(std::move(data));
    Babel::Audio::packageAudio_t *package = new Babel::Audio::packageAudio_t;
    std::vector<unsigned char> tmp = encoded->getEncodedBuffer();
    for(int i = 0; i < 960; i++)
        package->voice[i] = tmp[i];
    package->timestamp = std::time(nullptr);
    char *buffer  = (char *)package;
    std::string toString(buffer, 972);
    write(toString);
}

bool NetworkUDP::stopConnection()
{
    delete _socket;
    _packageManger->end();
    return true;
}




