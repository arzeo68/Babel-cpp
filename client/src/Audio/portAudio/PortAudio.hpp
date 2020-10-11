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
class NetworkUDP;

#define SAMPLE_RATE  (48000)
#define BUFFER_SIZE  (480)
#define NUM_CHANNEL  (2)

class PortAudio: public AAudio
{
    public:
    PortAudio();
    /*!
        open the input stream to allow the program to get your mic input
    */
    void startRecording() override;
    //! stopRecording
    /*!
        close the input stream to stop recording mic input
    */
    void stopRecording() override;
    /*!
        open the output stream to allow the program to play sound on your output device
    */
    void startPlaying() override;
    /*!
        close the output stream to stop playing sound
    */
    void stopPlaying() override;
    /*!
        return the next sound that is needed to be played
    */
    /**
     *
     * @return the next sound that is needed to be played
     */
    std::shared_ptr<Babel::Audio::soundDecoded> getNextSound();
    /*!
        add a sound at the back of the sound to be played queue
    */
    /**
     *
     * @param data take a const std::shared_ptr<Babel::Audio::soundDecoded>& that contain the sound that you want to add in the queue
     */
    void addSoundToQueue(const std::shared_ptr<Babel::Audio::soundDecoded>& data);

    private:
    NetworkUDP *_soundCallBack = nullptr;
    public:
    /*!
        return the callback that is played when a sound is ready to be send
    */
    /**
     *
     * @return the callback that is played when a sound is ready to be send
     */
    NetworkUDP *getSoundCallBack() const;
    /*!
        set the callback that is played when a sound is ready to be send
    */
    /**
     *
     * @param soundCallBack callback that is played when a sound is ready to be send
     */
    void setSoundCallBack(NetworkUDP *soundCallBack);

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
