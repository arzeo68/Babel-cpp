//
// Created by alexis on 20/09/2020.
//

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP
#include <portaudio.h>

class PortAudio
{
    public:
    PortAudio();

    private:
    PaError _err;
};


#endif //BABEL_PORTAUDIO_HPP
