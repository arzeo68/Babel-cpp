//
// Created by arzeo on 10/5/2020.
//

#ifndef BABEL_PACKAGEMANAGER_HPP
#define BABEL_PACKAGEMANAGER_HPP

#include <memory>
#include <client/src/Audio/Opus/Opus.hpp>
#include <client/src/Audio/portAudio/PortAudio.hpp>

#include "../Network/UDP/PackageUdp.hpp"

class PackageManager
{
    public:
    PackageManager();
    void start();
    void end();
    void sendPackage(void);
    void handlePackage(char *pack, int size);
    std::shared_ptr<PortAudio> getPa();
    std::shared_ptr<Opus> getEncoder() const;
    std::shared_ptr<Babel::Audio::soundDecoded> getPaNextSound();
    const std::shared_ptr<IPackage<Babel::Audio::packageAudio_t *, Babel::Audio::packageAudio_t *>> &getPackageBuilder() const;

    private:
    std::time_t lastPackageTimestamp = 0;
    std::shared_ptr<IPackage<Babel::Audio::packageAudio_t *, Babel::Audio::packageAudio_t *>> _packageBuilder;
    std::shared_ptr<Opus> _encoder;
    std::shared_ptr<PortAudio> _player;
};

#endif //BABEL_PACKAGEMANAGER_HPP
