//
// Created by alexis on 20/09/2020.
//

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus.h>
#include <stdio.h>
#include <iostream>
class Opus
{
    public:
    Opus();
    ~Opus();

    private:
    OpusEncoder *_encoder;
    OpusDecoder *_decoder;
    const int _channel  = 2;
    const int _bitRate = 64000;
    const int _frameSize = 960;
    const int _sampleRate  = 48000;
    const int _maxFrameSize  = 5760;
    const int _maxPacketSize = 3828;
    int _err;
};

#endif //BABEL_OPUS_HPP
