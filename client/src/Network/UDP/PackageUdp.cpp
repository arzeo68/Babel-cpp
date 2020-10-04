//
// Created by alexis on 04/10/2020.
//

#include "PackageUdp.hpp"

std::string PackageUdp::toString(std::shared_ptr<Babel::Audio::packageAudio_t> send)
{
    return (char *)send.get();
}

Babel::Audio::packageAudio_t *PackageUdp::toPackage(std::string &string)
{
    return (Babel::Audio::packageAudio_t *)(const_cast<char *>(string.c_str()));
}
