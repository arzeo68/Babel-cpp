//
// Created by alexis on 20/09/2020.
//

#include "PortAudio.hpp"
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
    inputParams.channelCount = NUM_CHANNEL;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = NULL;
    // Output
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cout << "Can't Pa_GetDefaultOutputDevice" << std::endl;
        return;
    }
    outputParams.channelCount = NUM_CHANNEL;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;
    _init = true;
    std::cout << "Port audio initialized." << std::endl;
}


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
        std::cout << "Can't Pa_GetDefaultInputDevice" << std::endl;
        return;
    }
    if (Pa_StartStream(stat) != paNoError) {
        std::cout << "Can't Pa_StartStream" << std::endl;
        return;
    }
    _recording = true;
}

void PortAudio::stopRecording()
{
    if (!_recording || !_init)
        return;
    if (Pa_CloseStream(stat) != paNoError) {
        std::cout << "Can't Pa_CloseStream" << std::endl;
        return;
    }
    _recording = false;
}

void PortAudio::startPlaying()
{
    if (_listening || !_init)
        return;
    if (Pa_OpenStream(&stout, NULL, &outputParams, SAMPLE_RATE, BUFFER_SIZE, paClipOff, PortAudio::playCallBack, this) != paNoError) {
        std::cout << "Can't Pa_OpenStream" << std::endl;
        return;
    }
    if (Pa_StartStream(stout) != paNoError) {
        std::cout << "Can't Pa_StartStream" << std::endl;
        return;
    }
    _listening = true;
}

void PortAudio::stopPlaying()
{
    if (!_listening || !_init)
        return;
    if (Pa_CloseStream(stat) != paNoError) {
        std::cout << "Can't Pa_CloseStream" << std::endl;
        return;
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
    if (data->getSize() != 0)
    {
        _playQueue.push(data->getSoundBuffer());
    }
    _m.unlock();
}
