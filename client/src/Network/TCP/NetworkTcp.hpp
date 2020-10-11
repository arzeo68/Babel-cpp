//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#include <QtNetwork/QTcpSocket>
#include "PackageTcp.hpp"

class GUIController;

/**
 * The NetworkTcp do the communication with the server:
 * - Create the socket
 * - Receive package
 * - Send package
 */
class NetworkTcp: public INetwork<std::string &, std::string> {
    Q_OBJECT
    public:

    /**
     * constructor
     * @param g the GUIController
     */
    NetworkTcp(GUIController *g, std::string &ip) : _guiController(g), _ip(ip) {};

    /**
     * destructor
     */
    ~NetworkTcp() override { delete _socket; };

    /**
     * start the connection with the server (create the socket link to the server)
     * @param ip ip of the server
     * @param port port of the server
     * @return true if connected, false otherwise
     */
    bool startConnection(const std::string &ip, const std::string &port) override;

    signals:
    public slots:

    /**
     * connected signal
     */
    void connected();

    /**
     * disconnected signal
     */
    void disconnected();

    /**
     * readyRead signal to read the data send by the server
     */
    void readyRead();

    /**
     * send the encoded package to the server
     * @param pkg the encoded package to send
     */
    void write(const char *pkg);

    private:
    GUIController *_guiController;
    QTcpSocket *_socket;
    std::string _ip;
};

#endif //BABEL_NETWORKTCP_HPP
