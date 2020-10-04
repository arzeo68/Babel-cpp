//
// Created by alexis on 20/09/2020.
//

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#include <portaudio.h>
#include <vector>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>

#include "client/src/Audio/portAudio/AAudio/AAudio.hpp"
#include "../data.hpp"


int portAudioTest(void);

#define SAMPLE_RATE  (48000)
#define BUFFER_SIZE  (480)
#define NUM_CHANNEL  (2)

class PortAudio: public AAudio
{
    public:
    PortAudio();

    void startRecording() override;

    void stopRecording() override;

    void startPlaying() override;

    void stopPlaying() override;

    std::shared_ptr<Babel::Audio::soundDecoded> getNextSound();
    void addSoundToQueue(const std::shared_ptr<Babel::Audio::soundDecoded>& data);

    private:
    static int recordCallBack(const void *tmp_buff, void *, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj);
    static int playCallBack(const void *, void *tmp_buff, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj);
    std::queue<std::vector<float>> _recordQueue;
    std::queue<std::vector<float>> _playQueue;
    PaStreamParameters inputParams;
    PaStreamParameters outputParams;
    PaStream *stat;
    PaStream *stout;
    std::mutex _m;
    PaError _err;
};


#endif //BABEL_PORTAUDIO_HPP
