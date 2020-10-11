//
// Created by alexis on 20/09/2020.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <common/Error/ThrowError.hpp>

#include "PortAudio.hpp"

PortAudio::PortAudio()
{
    _recording = false;
    _listening = false;
    // Init
    if (Pa_Initialize() != paNoError) {
        throw ThrowError("PortAudio failed to initialize PortAudio");
    }
    // Input
    inputParams.device = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        throw ThrowError("PortAudio failed to get input default device");
    }
    inputParams.channelCount = NUM_CHANNEL;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = NULL;
    // Output
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        throw ThrowError("PortAudio failed to get output default device");
    }
    outputParams.channelCount = NUM_CHANNEL;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;
    _init = true;
}
#include "../../Network/UDP/NetworkUdp.hpp"
int PortAudio::recordCallBack(const void *tmp_buff, void *, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj)
{
    PortAudio *p = reinterpret_cast<PortAudio *>(obj);
    std::vector<float> wptr;
    p->_m.lock();
    wptr.assign(
        reinterpret_cast<const float *>(tmp_buff), reinterpret_cast<const float *>(tmp_buff) + frm * NUM_CHANNEL
        );
    p->_recordQueue.push(std::move(wptr));
    p->_m.unlock();
    if (p->_soundCallBack != nullptr)
        p->_soundCallBack->packageReadyToSendCallback();
    return 0;
}

int PortAudio::playCallBack(const void *, void *tmp_buff, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj)
{
    PortAudio *p = reinterpret_cast<PortAudio *>(obj);
    p->_m.lock();
    if (!p->_playQueue.empty())
    {
        std::vector<float> tmp = p->_playQueue.front();
        float *wptr = static_cast<float *>(tmp_buff);
        for (int i = 0; i < frm * NUM_CHANNEL; i++)
            *wptr++ = tmp[i];
        p->_playQueue.pop();
    }
    p->_m.unlock();
    return 0;
}

void PortAudio::startRecording()
{
    if (_recording || !_init)
        return;
    if (Pa_OpenStream(&stat, &inputParams, NULL, SAMPLE_RATE, BUFFER_SIZE,
        paClipOff, PortAudio::recordCallBack, this) != paNoError) {
        throw ThrowError("PortAudio failed to open record stream");
    }
    if (Pa_StartStream(stat) != paNoError) {
        throw ThrowError("PortAudio failed to start record stream");
    }
    _recording = true;
}

void PortAudio::stopRecording()
{
    if (!_recording || !_init)
        return;
    if ((_err = Pa_CloseStream(stat)) != paNoError) {
        throw ThrowError("PortAudio failed to close record stream");
    }
    _recording = false;
}

void PortAudio::startPlaying()
{
    if (_listening || !_init)
        return;
    if (Pa_OpenStream(&stout, NULL, &outputParams, SAMPLE_RATE, BUFFER_SIZE, paClipOff, PortAudio::playCallBack, this) != paNoError) {
        throw ThrowError("PortAudio failed to open play stream");
    }
    if (Pa_StartStream(stout) != paNoError) {
        throw ThrowError("PortAudio failed to start play stream");
    }
    _listening = true;
}

void PortAudio::stopPlaying()
{
    if (!_listening || !_init)
        return;
    if ((_err = Pa_CloseStream(stout)) != paNoError) {
        throw ThrowError("PortAudio failed to close play stream");
    }
    _listening = false;
}

std::shared_ptr<Babel::Audio::soundDecoded> PortAudio::getNextSound()
{
    _m.lock();
    if (_recordQueue.empty())
    {
        std::shared_ptr<Babel::Audio::soundDecoded> s = std::make_shared<Babel::Audio::soundDecoded>();
        _m.unlock();
        return s;
    }
    std::shared_ptr<Babel::Audio::soundDecoded> s =std::make_shared<Babel::Audio::soundDecoded>(BUFFER_SIZE * NUM_CHANNEL, _recordQueue.front());
    _recordQueue.pop();
    _m.unlock();
    return s;
}

void PortAudio::addSoundToQueue(const std::shared_ptr<Babel::Audio::soundDecoded>& data)
{
    _m.lock();
    if (data->getSize() > 0)
    {
        _playQueue.push(data->getSoundBuffer());
    }
    _m.unlock();
}

NetworkUDP *PortAudio::getSoundCallBack() const
{
    return _soundCallBack;
}

void PortAudio::setSoundCallBack(NetworkUDP *soundCallBack)
{
    _soundCallBack = soundCallBack;
}

