#include <iostream>

#include "src/Audio/portAudio/PortAudio.hpp"
#include "src/Audio/Opus/Opus.hpp"


int main(int argc, char **argv)
{
    PortAudio p;
    p.startRecording();
    p.startPlaying();
    while (1)
    {
        p.addSoundToQueue(p.getNextSound());
    }
}

