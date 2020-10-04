//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_INETWORK_HPP
#define BABEL_INETWORK_HPP

#include <QtCore/QObject>

template <typename T>
class IPackage {
    public:
    virtual ~IPackage() = default;
    virtual std::string toString(T) = 0;
    virtual T toPackage(const std::string &) = 0;
};

template <typename T>
class INetwork : public QObject {
    public:
    virtual ~INetwork() = default;
    virtual bool startConnection(const std::string &ip, const std::string &port) = 0;
    virtual bool write(T) = 0;
    virtual T read() = 0;
};

#endif