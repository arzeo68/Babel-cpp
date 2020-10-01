//
// Created by whosdad on 27/09/2020.
//

#ifndef BABEL_RESPONSE_HPP
#define BABEL_RESPONSE_HPP

#include "HTTPCodes.hpp"
#include <string>

namespace Server {
    struct Response {
        HTTPCodes::HTTPCodes_e code;
        std::string msg;
    };
    static const Response InvalidMethodTemplate = {
        .code = HTTPCodes::HTTPCodes_e::METHOD_NOT_ALLOWED,
        .msg = "Method not allowed",
    };
}


#endif //BABEL_RESPONSE_HPP
