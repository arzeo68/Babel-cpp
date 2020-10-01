//
// Created by alexis on 28/09/2020.
//

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

class IAudio
{
    public:
    virtual ~IAudio() = default;
    virtual void startRecording() = 0;
    virtual void stopRecording() = 0;

    virtual void startPlaying() = 0;
    virtual void stopPlaying() = 0;
};

#endif //BABEL_IAUDIO_HPP
