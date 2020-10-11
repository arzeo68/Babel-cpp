//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKUDP_HPP

#include <QtNetwork/qudpsocket.h>
#include <QNetworkProxy>

#include "client/src/package/PackageManager.hpp"
#include "PackageUdp.hpp"

class NetworkUDP: public INetwork<std::string, std::string>
{
    Q_OBJECT
    public:
    NetworkUDP();

    bool startConnection(const std::string &ip, const std::string &port) override;
    bool startConnection();
    bool stopConnection();

    bool write(std::string t);
    void sendSound(Babel::Audio::soundDecoded &data);

    std::string read();

    void packageReadyToSendCallback();

    quint16 getPort() const;

    void setPort(quint16 port);

    const std::string &getIp() const;

    void setIp(const std::string &ip);

    private:
    quint16 _port = 0;
    std::string _ip = "";
    std::shared_ptr<PackageManager> _packageManger;
    QUdpSocket *_socket = nullptr;
    uint32_t _nextPackageSize = 0;

    public slots:
        void markAsReadable(void);

};



#endif //BABEL_NETWORKUDP_HPP
