//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_IPACKAGE_HPP
#define BABEL_IPACKAGE_HPP

#include <string>

template <typename SEND, typename RECEIVE>
class IPackage {
    public:
    virtual ~IPackage() = default;
    virtual std::string toString(SEND) = 0;
    virtual RECEIVE toPackage(const std::string &) = 0;
};

#endif //BABEL_IPACKAGE_HPP
