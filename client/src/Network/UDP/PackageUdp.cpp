//
// Created by alexis on 04/10/2020.
//

#include "PackageUdp.hpp"

std::string PackageUdp::toString(Babel::Audio::packageAudio_t *t)
{
    return std::string((char *)t);
}

Babel::Audio::packageAudio_t *PackageUdp::toPackage(const std::string &string)
{
    return (Babel::Audio::packageAudio_t *)string.c_str();
}
