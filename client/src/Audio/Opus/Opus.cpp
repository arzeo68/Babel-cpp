//
// Created by alexis on 20/09/2020.
//

#include "Opus.hpp"

Opus::Opus()
{
    // ENCODER
    _encoder = opus_encoder_create(_sampleRate, _channel, OPUS_APPLICATION_VOIP, &_err);
    if (_err < 0)
    {
        std::cout << " opus failed to create the encoder error: " << opus_strerror(_err) << std::endl;
    }
    // DECODER
    _decoder = opus_decoder_create(48000, _channel, &_err);
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

std::shared_ptr<Babel::Audio::soundEncoded>Opus::encode(std::shared_ptr<Babel::Audio::soundDecoded> data)
{
    std::shared_ptr<Babel::Audio::soundEncoded> encoded = std::make_shared<Babel::Audio::soundEncoded>();
    if (data->getSize() == 0)
    {
        encoded->setSize(0);
        return encoded;
    }
    std::cout << data->getSize() << std::endl;
    encoded->resizeBuffer(data->getSize());
    int err = opus_encode_float(_encoder, data->getData(), 480, encoded->getEncodedBuffer().data(), data->getSize());

    if (err < 0)
    {
        std::cerr << "error faut throw: " << err << std::endl;
    }
    encoded->setSize(err);
    return encoded;
}

std::shared_ptr<Babel::Audio::soundDecoded>Opus::decode(std::shared_ptr<Babel::Audio::soundEncoded> data)
{
    std::shared_ptr<Babel::Audio::soundDecoded> decode = std::make_shared<Babel::Audio::soundDecoded>();
    if (data->getSize() == 0)
    {
        decode->setSize(0);
        return decode;
    }
    decode->resizeBuffer(480 * 2);
    int err = opus_decode_float(_decoder, data->getEncodedBuffer().data(), data->getSize(), decode->getSoundBuffer().data(), 480, 0) * 2;
    decode->setSize(err);
    if (err < 0)
        std::cerr << "error faut throw: " << err << std::endl;
    std::cout << "real exist" << std::endl;
    return decode;
}
