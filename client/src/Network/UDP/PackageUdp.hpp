//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGEUDP_HPP
#define BABEL_PACKAGEUDP_HPP

#include "client/src/Audio/data.hpp"
#include "client/src/Network/INetwork.hpp"

class PackageUdp: public IPackage<Babel::Audio::packageAudio_t *>
{
    public:
    std::string toString(Babel::Audio::packageAudio_t *t) override;

    Babel::Audio::packageAudio_t *toPackage(const std::string &string) override;
};

#endif //BABEL_PACKAGEUDP_HPP
