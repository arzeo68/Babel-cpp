//
// Created by alexis on 20/09/2020.
//

#include "PortAudio.hpp"
#include <iostream>

PortAudio::PortAudio()
{
    _err = Pa_Initialize();
    std::cout << "ntm" << std::endl;
}