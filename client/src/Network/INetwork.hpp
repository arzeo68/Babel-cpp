//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_INETWORK_HPP
#define BABEL_INETWORK_HPP

#include <QtCore/QObject>

/**
 * INetwork for communication
 * @tparam SEND package to send
 * @tparam RECEIVE package received
 */
template <typename SEND, typename RECEIVE>
class INetwork : public QObject {
    public:

    /**
     * default destructor
     */
    virtual ~INetwork() = default;

    /**
     * start connection with server/client
     * @param ip ip of the server/client
     * @param port port of the server/client
     * @return true if success, false otherwise
     */
    virtual bool startConnection(const std::string &ip, const std::string &port) = 0;
    //virtual bool write(SEND) = 0;
    //virtual RECEIVE read() = 0;
};

#endif