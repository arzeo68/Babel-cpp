//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_INETWORK_HPP
#define BABEL_INETWORK_HPP

#include <QtCore/QObject>

template <typename SEND, typename RECEIVE>
class INetwork : public QObject {
    public:
    virtual ~INetwork() = default;
    virtual bool startConnection(const std::string &ip, const std::string &port) = 0;
    //virtual bool write(SEND) = 0;
    //virtual RECEIVE read() = 0;
};

#endif