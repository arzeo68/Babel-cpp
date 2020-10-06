/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_COMMON_PROTOCOL_
#define SRC_COMMON_PROTOCOL_

#include <cstdint>
#include <string>
#include <vector>

namespace Common {
    static const constexpr uint16_t g_MagicNumber = 0xFABAu;
    const static constexpr uint16_t g_maxMessageLength = 256u;

    enum class HTTPCodes_e : uint16_t {
        OK = 200,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        INTERNAL_SERVER_ERROR = 500,
    };

    #pragma pack(push, 1)
    struct Response {
        HTTPCodes_e code;
        char msg[g_maxMessageLength];
    };
    #pragma pack(pop)

    static const Response InvalidMethodTemplate = {
        HTTPCodes_e::METHOD_NOT_ALLOWED,
        "Method not allowed",
    };

    static const Response BadRequestTemplate = {
        HTTPCodes_e::BAD_REQUEST,
        "Missing argument",
    };

    typedef uint8_t HTTPMethod_t;
    enum Method : HTTPMethod_t {
        GET,
        DELETE,
        POST,
        PUT
    };

    #pragma pack(push, 1)
    struct PackageServer {
        uint16_t magic;
        uint16_t id;
        Method method;
        uint8_t command;
        char args[g_maxMessageLength];
    };
    #pragma pack(pop)
}

#endif
