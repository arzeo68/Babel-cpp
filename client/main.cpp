#include <client/src/Audio/portAudio/PortAudio.hpp>
#include <client/src/Audio/Opus/Opus.hpp>

int main(int argc, char **argv)
{
    PortAudio p;
    Opus o;
    p.startRecording();
    p.startPlaying();
    while (1)
    {
        p.addSoundToQueue(p.getNextSound());
    }
}

