//
// Created by arzeo on 10/5/2020.
//

#include "PackageManager.hpp"

PackageManager::PackageManager() : _packageBuilder(std::make_shared<PackageUdp>()), _encoder(std::make_shared<Opus>()), _player(std::make_shared<PortAudio>())
{
}

void PackageManager::sendPackage(void)
{

}

void PackageManager::start()
{

    _player->startRecording();
    _player->startPlaying();
}

void PackageManager::end()
{
    _player->stopRecording();
    _player->stopPlaying();
}

void PackageManager::handlePackage(char *pack, int size)
{
    std::string str(pack, size);
    Babel::Audio::packageAudio_t *package = _packageBuilder->toPackage(str);
    if (package->magicByte != 0x12b)
    if (lastPackageTimestamp == 0)
        lastPackageTimestamp = package->timestamp;
    if (package->timestamp < lastPackageTimestamp)
    {
        delete package;
        return;
    }
    // todo if sound bug try to replace 960 by size
    int voiceSize = 0;
    for(; package->voice[voiceSize] != 0; voiceSize++);
    std::vector<unsigned char> voice(package->voice, package->voice + voiceSize);
    Babel::Audio::soundEncoded encoded(voice, voiceSize);
    encoded.setEncodedBuffer(voice);
    _player->addSoundToQueue(std::make_shared<Babel::Audio::soundDecoded>(_encoder->decode(encoded)));
}

std::shared_ptr<PortAudio> PackageManager::getPa()
{
    return _player;
}

std::shared_ptr<Opus> PackageManager::getEncoder() const
{
    return _encoder;
}

const std::shared_ptr<IPackage<Babel::Audio::packageAudio_t *, Babel::Audio::packageAudio_t *>> &PackageManager::getPackageBuilder() const
{
    return _packageBuilder;
}

std::shared_ptr<Babel::Audio::soundDecoded> PackageManager::getPaNextSound()
{
    return _player->getNextSound();
}

