//
// Created by alexis on 04/10/2020.
//

#include "PackageUdp.hpp"

std::string &PackageUdp::toString(Babel::Audio::packageAudio_t *t)
{
    std::string str((char *)t);
    return str;
}

Babel::Audio::packageAudio_t *PackageUdp::toPackage(std::string &string)
{
    return (Babel::Audio::packageAudio_t *)string.c_str();
}
