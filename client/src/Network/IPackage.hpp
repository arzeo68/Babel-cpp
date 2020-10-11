//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_IPACKAGE_HPP
#define BABEL_IPACKAGE_HPP

#include <string>

/**
 * IPackage encode and decode package
 */
template <typename SEND, typename RECEIVE>
class IPackage {
    public:

    /**
     * default destructor
     */
    virtual ~IPackage() = default;

    /**
     * encode package
     * @return encoded package
     */
    virtual std::string toString(SEND) = 0;

    /**
     * decode package
     * @return decoded package
     */
    virtual RECEIVE toPackage(std::string &) = 0;
};

#endif //BABEL_IPACKAGE_HPP
