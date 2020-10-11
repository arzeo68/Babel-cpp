//
// Created by alexis on 20/09/2020.
//

#include <common/Error/ThrowError.hpp>

#include "Opus.hpp"

Opus::Opus()
{
    // ENCODER
    _encoder = opus_encoder_create(_sampleRate, _channel, OPUS_APPLICATION_VOIP, &_err);
    if (_err < 0)
    {
        throw ThrowError("OPUS","failed to create the encoder");
    }
    // DECODER
    _decoder = opus_decoder_create(48000, _channel, &_err);
    if (_err < 0)
    {
        throw ThrowError("OPUS","failed to create the decoder");

    }
}

Opus::~Opus()
{
    opus_encoder_destroy(_encoder);
    opus_decoder_destroy(_decoder);
}

Babel::Audio::soundEncoded Opus::encode(Babel::Audio::soundDecoded &data)
{
    Babel::Audio::soundEncoded encoded;
    if (data.getSize() == 0)
    {
        encoded.setSize(0);
        return encoded;
    }
    encoded.resizeBuffer(data.getSize());
    int err = opus_encode_float(_encoder, data.getData(), 480, encoded.getEncodedBuffer().data(), data.getSize());

    if (err < 0)
    {
        throw ThrowError("OPUS","failed to encode");
    }
    encoded.setSize(err);
    return encoded;
}

Babel::Audio::soundDecoded Opus::decode(Babel::Audio::soundEncoded &data)
{
    Babel::Audio::soundDecoded decode;
    if (data.getSize() <= 0)
    {
        decode.setSize(0);
        return decode;
    }

    decode.resizeBuffer(_frameSize * _channel);
    int err = opus_decode_float(_decoder, data.getEncodedBuffer().data(), data.getSize(), decode.getSoundBuffer().data(), 480, 0) * 2;
    decode.setSize(err);
    if (err < 0)
        throw ThrowError("OPUS","failed to decode");
    return decode;
}
