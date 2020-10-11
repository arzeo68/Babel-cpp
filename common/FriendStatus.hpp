/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_BABEL_FRIEND_STATUS
#define SRC_BABEL_FRIEND_STATUS

#include <cstdint>

namespace Common {
    enum class FriendStatus : uint8_t {
        NONE = 0,
        PENDING = 1,
        ACCEPTED = 2,
        REJECTED = 3
    };
}

#endif
