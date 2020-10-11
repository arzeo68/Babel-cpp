/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_BABEL_CALL_STATUS_COMMON
#define SRC_BABEL_CALL_STATUS_COMMON

#include <cstdint>

namespace Common {
    enum CallState : uint8_t {
        NONE = 0,
        PENDING = 1,
        ACCEPTED = 2,
        DECLINED = 3,
        PENDING_CALLER = 4,
        ENDED = 5
    };
}

#endif
