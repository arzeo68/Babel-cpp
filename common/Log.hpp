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
#include <map>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace Common::Log {
    enum LogLevel_e : uint16_t {
        DEBUG = 0b0001u,
        INFO = 0b0010u,
        WARN = 0b01000u,
        ERROR = 0b10000u,
    };

    class Log {
        public:
        explicit Log(const std::string &title, const std::string &path,
                     uint8_t logLevel = DEBUG | INFO | WARN | ERROR, std::ios_base::openmode openMode = std::ios::app);

        Log(const Log &log);

        ~Log() = default;
        static const constexpr uint8_t g_AllLogLevel = DEBUG | INFO | WARN | ERROR;

        template<typename ...variadic>
        void Debug(variadic &&... args) {
            return (this->Write(DEBUG, args...));
        }

        template<typename ...variadic>
        void Debug(variadic &&... args) const {
            return (this->Write(DEBUG, args...));
        }

        template<typename ...variadic>
        void Warning(variadic &&... args) {
            return (this->Write(WARN, args...));
        }
        template<typename ...variadic>
        void Warning(variadic &&... args) const {
            return (this->Write(WARN, args...));
        }

        template<typename ...variadic>
        void Error(variadic &&... args) {
            return (this->Write(ERROR, args...));
        }
        template<typename ...variadic>
        void Error(variadic &&... args) const {
            return (this->Write(ERROR, args...));
        }

        template<typename ...variadic>
        void Info(variadic &&... args) {
            return (this->Write(INFO, args...));
        }
        template<typename ...variadic>
        void Info(variadic &&... args) const {
            return (this->Write(INFO, args...));
        }


        private:
        static std::string GetCurrentTime() {
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
            return (buffer);
        }

        template<typename ...variadic>
        void Write(LogLevel_e level, variadic &&... args) {
            if ((level & this->_level) == 0)
                return;
            this->_mutex.lock();
            std::string prefix("[" + Common::Log::Log::GetCurrentTime() + "/" +
                               _map.find(level)->second + "]" + " ");
            std::cout << prefix;
            (std::cout << ... << args) << std::endl;
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
            {DEBUG, "debug"},
            {INFO,  "info"},
            {WARN,  "warning"},
            {ERROR, "error"},
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
