//
// Created by whosdad on 04/10/2020.
//

#ifndef BABEL_COMMONPACKAGES_HPP
#define BABEL_COMMONPACKAGES_HPP

#pragma pack(push, 1)

#include <cstdint>

struct PackageServer {
    uint16_t magic;
    uint16_t id;
    uint8_t method;
    uint8_t command;
    char args[256];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ResponseServer {
    uint8_t code;
    char res[256];
};
#pragma pack(pop)

#endif //BABEL_COMMONPACKAGES_HPP
