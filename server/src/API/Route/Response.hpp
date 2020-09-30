//
// Created by whosdad on 27/09/2020.
//

#ifndef BABEL_RESPONSE_HPP
#define BABEL_RESPONSE_HPP

#include "HTTPCodes.hpp"
#include <string>

<<<<<<< HEAD:server/src/API/Route/Response.hpp
namespace Server {
        struct Response {
            HTTPCodes::HTTPCodes_t code;
            std::string msg;
        };
    }
=======
namespace Server::API {
    struct Error {
        HTTPCodes::HTTPCodes_t code;
        std::string msg;
    };
}
>>>>>>> c3a1b742525581a1d73001aacdf11a924600b210:server/src/API/Route/Error.hpp


#endif //BABEL_RESPONSE_HPP
