//
// Created by alexis on 20/09/2020.
//

#include <iostream>
#include <cstring>
#include "PortAudio.hpp"

PortAudio::PortAudio()
{
    _inCall = false;
    _recording = false;
    _listening = false;
    // Init
    if (Pa_Initialize() != paNoError) {
        std::cout << "Can't Pa_Initialize" << std::endl;
        return;
    }
    // Input
    inputParams.device = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        std::cout << "Can't Pa_GetDefaultInputDevice" << std::endl;
        return;
    }
    inputParams.channelCount = 2;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = NULL;
    // Output
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cout << "Can't Pa_GetDefaultOutputDevice" << std::endl;
        return;
    }
    outputParams.channelCount = 2;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;
    _init = true;
    std::cout << "Port audio initialized." << std::endl;
}

void PortAudio::startStream()
{
    if (_recording || !_init)
        return;
    if (Pa_OpenStream(&stat, &inputParams, NULL, 48000, 480,
        paClipOff, PortAudio::recordCallBack, this) != paNoError) {
        std::cout << "Can't Pa_GetDefaultInputDevice" << std::endl;
        return;
    }
    if (Pa_StartStream(stat) != paNoError) {
        std::cout << "Can't Pa_StartStream" << std::endl;
        return;
    }
    _recording = true;
}

void PortAudio::stopStream()
{
    if (!_recording || !_init)
        return;
    if (Pa_CloseStream(stat) != paNoError) {
        std::cout << "Can't Pa_CloseStream" << std::endl;
        return;
    }
    _recording = false;
}

void PortAudio::startListening()
{
    if (_listening || !_init)
        return;
    if (Pa_OpenStream(&stout, NULL, &outputParams, 48000, 480, paClipOff, PortAudio::playCallBack, this) != paNoError) {
        std::cout << "Can't Pa_OpenStream" << std::endl;
        return;
    }
    if (Pa_StartStream(stout) != paNoError) {
        std::cout << "Can't Pa_StartStream" << std::endl;
        return;
    }
    _listening = true;
}

void PortAudio::stopListening()
{
    if (!_listening || !_init)
        return;
    if (Pa_CloseStream(stat) != paNoError) {
        std::cout << "Can't Pa_CloseStream" << std::endl;
        return;
    }
    _listening = false;
}

void *PortAudio::getStat() const
{
    return stat;
}

void *PortAudio::getStout() const
{
    return stout;
}

int PortAudio::recordCallBack(const void *tmp_buff, void *, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj)
{
    PortAudio *p = reinterpret_cast<PortAudio *>(obj);
    float const *rptr = (float const *)tmp_buff;
    std::vector<float> wptr;
    wptr.reserve(frm * 2);
    for (int i = 0; i < 480; i++)
    {
        wptr.emplace_back(*rptr++);
        if constexpr (NUM_CHANNEL == 2)
            wptr.emplace_back(*rptr++);
    }
    p->_m.lock();
    p->_bufferQueue.push(std::move(wptr));
    p->_m.unlock();
    return 0;
}

int PortAudio::playCallBack(const void *, void *tmp_buff, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj)
{
    PortAudio *p = reinterpret_cast<PortAudio *>(obj);
    p->_m.lock();
    if (!p->_bufferQueue.empty())
    {
        memcpy(tmp_buff, p->_bufferQueue.front().data(), frm * 2);
        p->_bufferQueue.pop();
    }
    p->_m.unlock();
    return 0;
}