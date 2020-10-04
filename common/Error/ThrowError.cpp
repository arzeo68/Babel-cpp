//
// Created by alexis on 04/10/2020.
//

#include "ThrowError.hpp"

ThrowError::ThrowError(const std::string &context, const std::string &message)
{
    _what = context + ": "  + message;
}

const char *ThrowError::what() const noexcept
{
    return _what.c_str();
}
