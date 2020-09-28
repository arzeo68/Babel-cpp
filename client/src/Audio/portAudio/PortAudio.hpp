//
// Created by alexis on 20/09/2020.
//

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP
#include <portaudio.h>
#include <vector>
#include <cstdint>
#include <mutex>
#include <queue>

int portAudioTest(void);

#define SAMPLE_RATE  (48000)
#define BUFFER_SIZE  (480)
#define NUM_CHANNEL  (2)

class PortAudio
{
    public:
    PortAudio();
    void startStream();
    void stopStream();
    void startListening();
    void stopListening();
    void *getStat() const;
    void *getStout() const;

    private:
    static int recordCallBack(const void *tmp_buff, void *, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj);
    static int playCallBack(const void *, void *tmp_buff, unsigned long frm, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *obj);
    std::queue<std::vector<float>> _bufferQueue;
    PaStreamParameters inputParams;
    PaStreamParameters outputParams;
    PaStream *stat;
    PaStream *stout;
    bool _inCall = false;
    bool _recording = false;
    bool _listening = false;
    bool _init = false;
    std::mutex _m;
    PaError _err;
};


#endif //BABEL_PORTAUDIO_HPP
