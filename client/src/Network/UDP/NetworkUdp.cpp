//
// Created by alexis on 04/10/2020.
//

#include <utility>
#include "common/Error/ThrowError.hpp"
#include "NetworkUdp.hpp"

NetworkUDP::NetworkUDP(): _packageManger(std::make_shared<PackageManager>())
{
}

bool NetworkUDP::startConnection(const std::string &ip, const std::string &port)
{
    _socket = (new QUdpSocket(this));
    _port = std::stoi(port);
    _ip = ip;
    if ( _socket->bind(QHostAddress::Any, _port) == 0)
    {
        throw ThrowError("QUdpSocket bind failed");
    }
    connect(_socket, SIGNAL(readyRead()),this, SLOT(markAsReadable()));
    _packageManger->getPa()->setSoundCallBack(this);
    _packageManger->start();
}

bool NetworkUDP::startConnection() {
    if (_port == 0 || _ip == "")
        throw ThrowError("NetworkUdp: port or ip is not set");
    _socket = (new QUdpSocket(this));
    if ( _socket->bind(QHostAddress::Any, _port) == 0)
    {
        throw ThrowError("QUdpSocket bind failed");
    }
    connect(_socket, SIGNAL(readyRead()),this, SLOT(markAsReadable()));
    _packageManger->getPa()->setSoundCallBack(this);
    _packageManger->start();
}

bool NetworkUDP::write(std::string t)
{
    int res = _socket->writeDatagram(t.c_str(), _nextPackageSize, QHostAddress(QString(_ip.c_str())), _port);
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
    std::shared_ptr<Babel::Audio::soundDecoded> sound = _packageManger->getPaNextSound();
    sendSound(*sound);

}

void NetworkUDP::markAsReadable(void)
{
    read();
}

void NetworkUDP::sendSound(Babel::Audio::soundDecoded &data)
{
    Babel::Audio::soundEncoded encoded = _packageManger->getEncoder()->encode(data);
    Babel::Audio::packageAudio_t *package = new Babel::Audio::packageAudio_t;
    std::vector<unsigned char> tmp = encoded.getEncodedBuffer();
    package->size = encoded.getSize();
    for(int i = 0; i < package->size; i++)
        package->voice[i] = tmp[i];
    package->timestamp = std::time(nullptr);
    char *buffer  = (char *)package;
    _nextPackageSize = 12 + package->size;
    std::string toString(buffer, _nextPackageSize);
    write(toString);
    delete package;
}

bool NetworkUDP::stopConnection()
{
    delete _socket;
    _packageManger->end();
    return true;
}

quint16 NetworkUDP::getPort() const {
    return _port;
}

void NetworkUDP::setPort(quint16 port) {
    _port = port;
}

const std::string &NetworkUDP::getIp() const {
    return _ip;
}

void NetworkUDP::setIp(const std::string &ip) {
    _ip = ip;
}


