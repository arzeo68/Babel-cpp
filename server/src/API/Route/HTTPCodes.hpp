/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Basic HTTP protocol codes
*/

#ifndef SRC_HTTPCODES_BABEL_
#define SRC_HTTPCODES_BABEL_

#include <cstdint>

namespace Server::HTTPCodes {
    typedef uint16_t HTTPCodes_t;
    enum class HTTPCodes_e : HTTPCodes_t {
        // Some codes might be useless and should removed if so
        OK = 200,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        DATA_NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        INTERNAL_SERVER_ERROR = 500,
    };
}

#endif
