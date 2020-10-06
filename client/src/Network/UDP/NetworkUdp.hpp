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
    bool stopConnection();

    bool write(std::string t) override;
    void sendSound(std::shared_ptr<Babel::Audio::soundDecoded> data);

    std::string read() override;

    void packageReadyToSendCallback();

    private:
    quint16 _port;
    std::string _ip;
    std::shared_ptr<PackageManager> _packageManger;
    QUdpSocket *_socket;

    public slots:
        void markAsReadable(void);

};

#endif //BABEL_NETWORKUDP_HPP
