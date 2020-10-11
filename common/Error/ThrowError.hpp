//
// Created by alexis on 04/10/2020.
//

#ifndef BABEL_THROWERROR_HPP
#define BABEL_THROWERROR_HPP

#include <exception>
#include <string>

class ThrowError : public std::exception
{
    public:
    explicit ThrowError(
        const std::string &context = "Undefined",
        const std::string &message = "Unknown Error");
    const char *what() const noexcept override;

    private:
    std::string _what;
};

#endif //BABEL_THROWERROR_HPP
