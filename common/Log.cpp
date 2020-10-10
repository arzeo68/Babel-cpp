/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Simple logger.
*/

#include <vector>
#include "Log.hpp"

Common::Log::Log::Log(const std::string &title, const std::string &path,
                      uint8_t log_level) : _title(title),
                                           _file(path, std::ios::app),
                                           _level(
                                               static_cast<LogLevel_e>(log_level)) {
    if (!this->_file.is_open())
        throw InvalidPath(path);
}

Common::Log::InvalidPath::InvalidPath(const std::string &path) : _path(path) {
}

const char *Common::Log::InvalidPath::what() const noexcept {
    static std::string message = "Invalid path entered: " + this->_path;
    return (message.c_str());
}
