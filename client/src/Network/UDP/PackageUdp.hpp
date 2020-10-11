//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGEUDP_HPP
#define BABEL_PACKAGEUDP_HPP

#include "client/src/Audio/data.hpp"
#include "client/src/Network/INetwork.hpp"
#include "client/src/package/IPackage.hpp"

class PackageUdp: public IPackage<Babel::Audio::packageAudio_t *, Babel::Audio::packageAudio_t *>
{
    public:
    //! toString
    /*!
      take a sound and convert it into a package that can be send by the networkUDP
    */
    std::string toString(Babel::Audio::packageAudio_t *t) override;

    //! toPackage
    /*!
      take a package and convert it into a sound that can be play
    */
    Babel::Audio::packageAudio_t *toPackage(std::string &string) override;

};

#endif //BABEL_PACKAGEUDP_HPP
