/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef BABEL_WORKER_HPP
#define BABEL_WORKER_HPP

#include <list>
#include <memory>
#include <thread>
#include "Network.hpp"
#include "common/Log.hpp"

namespace Server {
    class Worker : public std::enable_shared_from_this <Worker> {
        public:
        explicit Worker(std::mutex &mutex,
                        std::shared_ptr <Common::Log::Log> logger);

        Worker(const Worker &) = delete;

        ~Worker();

        void SetNetwork(std::shared_ptr <Network::Network> network);

        void Run();

        void Stop();

        void
        AddNotification(const Common::Response &&rep, const std::string &dest);

        void
        AddNotification(const Common::Response &rep, const std::string &dest);

        private:
        std::mutex &_mutex;
        std::shared_ptr <Common::Log::Log> _logger;
        bool _is_running = false;
        std::shared_ptr <Network::Network> _network;
        std::optional <std::thread> _thread;
        std::list <std::pair <Common::Response, std::string>> _tasks;
    };
}


#endif //BABEL_WORKER_HPP
