//
// Created by alexis on 28/09/2020.
//

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

class IAudio
{
    public:
    virtual ~IAudio() = default;
    //! startRecording
    /*!
        this function start the record of the input device
    */
    virtual void startRecording() = 0;
    //! stopRecording
    /*!
        this function stop the record of the input device
    */
    virtual void stopRecording() = 0;
    //! startPlaying
    /*!
        this function start sound playing on the output device
    */
    virtual void startPlaying() = 0;
    //! stopPlaying
    /*!
        this function stop sound playing on the output device
    */
    virtual void stopPlaying() = 0;
};

#endif //BABEL_IAUDIO_HPP
