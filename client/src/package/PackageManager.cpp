//
// Created by arzeo on 10/5/2020.
//

#include "PackageManager.hpp"


PackageManager::PackageManager() : _packageBuilder(std::make_unique<PackageUdp>()), _encoder(std::make_unique<Opus>()), _player(std::make_shared<PortAudio>())
{

}

void PackageManager::sendPackage(void)
{
}

void PackageManager::start()
{

    _player->startRecording();
    _player->stopRecording();
}

void PackageManager::end()
{
    _player->stopRecording();
    _player->stopPlaying();
}

void PackageManager::handlePackage(char *pack, int size)
{
    Babel::Audio::packageAudio_t *package = _packageBuilder->toPackage(pack);
    // check magic byte + time stamp
    std::shared_ptr<Babel::Audio::soundEncoded> encoded;
    // todo if sound bug try to replace 960 by size
    std::vector<unsigned char> voice(package->voice, package->voice + 960);
    encoded->setEncodedBuffer(voice);
    _player->addSoundToQueue(_encoder->decode(encoded));
}

std::shared_ptr<PortAudio> PackageManager::getPa()
{
    return _player;
}
