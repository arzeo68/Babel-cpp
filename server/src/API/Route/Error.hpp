//
// Created by whosdad on 27/09/2020.
//

#ifndef BABEL_ERROR_HPP
#define BABEL_ERROR_HPP

#include "HTTPCodes.hpp"
#include <string>

namespace Server {
        struct Error {
            HTTPCodes::HTTPCodes_t code;
            std::string msg;
        };
    }


#endif //BABEL_ERROR_HPP
