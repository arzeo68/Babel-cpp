/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Simple logger.
*/

#ifndef BABEL_LOG_HPP
#define BABEL_LOG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace Common::Log {
    enum LogLevel_e : uint16_t {
        LOG_DEBUG_E = 0b0001u,
        LOG_INFO_E = 0b0010u,
        LOG_WARN_E = 0b01000u,
        LOG_ERROR_E = 0b10000u,
    };

    class Log : public std::enable_shared_from_this <Log> {
        public:
        explicit Log(const std::string &title, const std::string &path,
                     uint8_t logLevel = LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E |
                                        LOG_ERROR_E,
                     std::ios_base::openmode openMode = std::ios::app);

        Log(const Log &log);

        ~Log() = default;

        static const constexpr uint8_t g_AllLogLevel =
            LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E | LOG_ERROR_E;

        template <typename ...variadic>
        void Debug(variadic &&... args) {
            return (this->Write(LOG_DEBUG_E, args...));
        }

        template <typename ...variadic>
        void Debug(variadic &&... args) const {
            return (this->Write(LOG_DEBUG_E, args...));
        }

        template<typename ...variadic>
        void Warning(variadic &&... args) {
            return (this->Write(LOG_WARN_E, args...));
        }
        template<typename ...variadic>
        void Warning(variadic &&... args) const {
            return (this->Write(LOG_WARN_E, args...));
        }

        template<typename ...variadic>
        void Error(variadic &&... args) {
            return (this->Write(LOG_ERROR_E, args...));
        }
        template<typename ...variadic>
        void Error(variadic &&... args) const {
            return (this->Write(LOG_ERROR_E, args...));
        }

        template<typename ...variadic>
        void Info(variadic &&... args) {
            return (this->Write(LOG_INFO_E, args...));
        }
        template<typename ...variadic>
        void Info(variadic &&... args) const {
            return (this->Write(LOG_INFO_E, args...));
        }


        private:
        static std::string GetCurrentTime() {
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            // Use localtime_s on windows
            timeinfo = localtime(&rawtime);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
            return (buffer);
        }

        template<typename ...variadic>
        void Write(LogLevel_e level, variadic &&... args) {
            if ((level & this->_level) == 0)
                return;
            std::string prefix("[" + Common::Log::Log::GetCurrentTime() + "/" +
                               this->_title + "/" +
                               _map.find(level)->second + "] ");
            std::cout << prefix;
            (std::cout << ... << args) << std::endl;
            if (!this->_mutex.try_lock())
                return;
            this->_file << prefix;
            (this->_file << ... << args) << std::endl;
            this->_mutex.unlock();
        }

        std::string _title;
        std::string _path;
        std::ios_base::openmode _mode;
        std::ofstream _file;
        LogLevel_e _level;
        std::mutex _mutex;
        const std::map<uint8_t, std::string> _map = {
            {LOG_DEBUG_E, "debug"},
            {LOG_INFO_E,  "info"},
            {LOG_WARN_E,  "warning"},
            {LOG_ERROR_E, "error"},
        };
    };

    class InvalidPath : std::exception {
        public:
        explicit InvalidPath(const std::string &path);

        const char *what() const noexcept override;

        private:
        std::string _path;
    };
}


#endif //BABEL_LOG_HPP
