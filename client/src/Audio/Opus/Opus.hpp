//
// Created by alexis on 20/09/2020.
//

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <memory>
#include <opus.h>
#include <cstdio>
#include <iostream>

#include "../data.hpp"

class Opus
{
    public:
    Opus();
    ~Opus();
    std::shared_ptr<Babel::Audio::soundEncoded>encode (std::shared_ptr<Babel::Audio::soundDecoded>);
    std::shared_ptr<Babel::Audio::soundDecoded>decode (std::shared_ptr<Babel::Audio::soundEncoded>);

    private:
    OpusEncoder *_encoder;
    OpusDecoder *_decoder;
    const int _channel  = 2;
    const int _bitRate = 64000;
    const int _frameSize = 480;
    const int _sampleRate  = 48000;
    const int _maxFrameSize  = 5760;
    const int _maxPacketSize = 3828;
    int _err;
};

#endif //BABEL_OPUS_HPP
