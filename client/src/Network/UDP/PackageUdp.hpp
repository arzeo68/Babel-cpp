//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_PACKAGEUDP_HPP
#define BABEL_PACKAGEUDP_HPP

#include <memory>

#include "client/src/Network/INetwork.hpp"
#include "common/Package/IPackage.hpp"
#include "../../Audio/data.hpp"

    class PackageUdp: public IPackage<std::shared_ptr<Babel::Audio::packageAudio_t>, Babel::Audio::packageAudio_t *>
{
    public:
        std::string toString(std::shared_ptr<Babel::Audio::packageAudio_t> send) override;
        Babel::Audio::packageAudio_t *toPackage(std::string &string) override;
    };

#endif //BABEL_PACKAGEUDP_HPP
