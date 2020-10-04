//
// Created by alexis on 28/09/2020.
//

#ifndef BABEL_AAUDIO_HPP
#define BABEL_AAUDIO_HPP

#include "../IAudio/IAudio.hpp"


class AAudio: public IAudio
{
    protected:
    bool _inCall = false;
    bool _recording = false;
    bool _listening = false;
    bool _init = false;
};

#endif //BABEL_AAUDIO_HPP
