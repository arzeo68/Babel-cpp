//
// Created by alexis on 20/09/2020.
//

#include "Opus.hpp"

Opus::Opus()
{
    // ENCODER
    _encoder = opus_encoder_create(_sampleRate, _channel, OPUS_APPLICATION_AUDIO, &_err);
    if (_err < 0)
    {
        std::cout << " opus failed to create the encoder error: " << opus_strerror(_err) << std::endl;
    }
    _err = opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(_bitRate));
    if (_err < 0)
    {
        std::cout << " opus failed to set the bitrate error: " << opus_strerror(_err) << std::endl;
    }
    // DECODER
    _decoder = opus_decoder_create(_sampleRate, _channel, &_err);
    if (_err < 0)
    {
        std::cout << " opus failed to create the decoder error: " << opus_strerror(_err) << std::endl;
    }
    std::cout << "opus initialization works" << std::endl;
}

Opus::~Opus()
{
    opus_encoder_destroy(_encoder);
    opus_decoder_destroy(_decoder);
}