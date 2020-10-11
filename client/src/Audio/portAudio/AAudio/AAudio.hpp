//
// Created by alexis on 28/09/2020.
//

#ifndef BABEL_AAUDIO_HPP
#define BABEL_AAUDIO_HPP

#include "../IAudio/IAudio.hpp"


class AAudio: public IAudio
{
    protected:
    bool _recording = false; /*!< boolean that represent the recording status */
    bool _listening = false; /*!< boolean that represent the playing status */
    bool _init = false; /*!< boolean that represent the lib initialization status */
};

#endif //BABEL_AAUDIO_HPP
