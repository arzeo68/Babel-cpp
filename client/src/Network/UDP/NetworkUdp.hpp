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
    /*!
      create the socket and bind it to the ip and port passed as parameter
    */
    /**
     *
     * @param ip that you connect to
     * @param port that you connect to
     * @return boolean that represent the connection status true if the connection works otherwise false
     */
    bool startConnection(const std::string &ip, const std::string &port) override;
    /*!
      create the socket and bind it to the ip and port stored in the instance
    */
    /**
     *
     * @return boolean that represent the connection status true if the connection works otherwise false
     */
    bool startConnection();
    /*!
      stop the connection and delete the socket
    */
    /**
     *
     * @return true if all have been succesfully closed otherwise false
     */
    bool stopConnection();
    /*!
      write a package into the socket
    */
    /**
     *
     * @param t string that you want to send
     * @return true if all have been succesfully wrote otherwise false
     */
    bool write(std::string t);
    /*!
      compress and create a package based on a soundDecoded and send it
    */
    /**
     *
     * @param data sound package that you want to send
     */
    void sendSound(Babel::Audio::soundDecoded &data);
    /*!
      read all byteAvalaible on the socket
    */
    /**
     *
     * @return the string readed on the socket
     */

    std::string read();
    /*!
      this function will be called by all things thats needs to send something
    */
    void packageReadyToSendCallback();
    /**
     *
     * @return port used on this instance (default = 0)
     */
    quint16 getPort() const;
    /**
    *
    * @param port that going to be used at the next startConnection
    */
    void setPort(quint16 port);
    /**
    *
    * @return ip used by the instance (default = 0.0.0.0)
    */
    const std::string &getIp() const;
    /**
     *
     * @param ip that going to be used at the next startConnection
     */
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
