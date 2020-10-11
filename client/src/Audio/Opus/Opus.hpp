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
    /*!
        take a encoded sound package as parameter and decode the sound inside of it
    */
    /**
     *
     * @param decoded sound decoded of type Babel::Audio::soundDecoded &
     * @return sound encoded
     */
    Babel::Audio::soundEncoded encode (Babel::Audio::soundDecoded &decoded);
    /*!
        take a decoded sound package as parameter and encode the sound inside of it
    */
    /**
     *
     * @param encoded sound encoded of type Babel::Audio::soundEncoded
     * @return sound decoded
     */
    Babel::Audio::soundDecoded decode (Babel::Audio::soundEncoded &encoded);

    private:
    OpusEncoder *_encoder; /*!< encoder instance */
    OpusDecoder *_decoder; /*!< decoder instance */
    const int _channel  = 2; /*!< number of channel */
    const int _bitRate = 64000; /*!< recording and playing bitrate */
    const int _frameSize = 480; /*!< frame size */
    const int _sampleRate  = 48000; /*!< smaple rate */
    const int _maxFrameSize  = 5760; /*!< frame size */
    int _err; /*!< always contain the last error */
};

#endif //BABEL_OPUS_HPP
