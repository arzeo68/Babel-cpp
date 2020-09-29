//
// Created by whosdad on 27/09/2020.
//

#ifndef BABEL_RESPONSE_HPP
#define BABEL_RESPONSE_HPP

#include "HTTPCodes.hpp"
#include <string>

namespace Server {
        struct Response {
            HTTPCodes::HTTPCodes_t code;
            std::string msg;
        };
    }


#endif //BABEL_RESPONSE_HPP
