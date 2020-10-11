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
#include <optional>
#include "Network.hpp"
#include "common/Log.hpp"

namespace Server {
    /**
     * A worker is a class that waits tasks to do. In this case, it's notification to send.
     */
    class Worker : public std::enable_shared_from_this<Worker> {
        public:
        /**
         * Store network's mutex and the shared instance logger
         * @param mutex parent's mutex, usually the network
         * @param logger The shared instance logger
         */
        explicit Worker(std::mutex &mutex,
                        std::shared_ptr<Common::Log::Log> logger);
        Worker(const Worker &) = delete;
        /**
         * The destructor waits for the thread to end
         */
        ~Worker();

        /**
         * Set a network's instance which wil be used to look for the list of clients. Create a thread.
         * @param network The shared network instance
         */
        void SetNetwork(std::shared_ptr<Network::Network> network);
        /**
         * Run the worker - RESERVED to the thread
         */
        void Run();
        /**
         * Stop the worker and wait for the thread to stop
         */
        void Stop();
        /**
         * Add a notification to the list
         * @param rep The notification/response to be written for the specified user
         * @param dest User's name
         */
        void
        AddNotification(const Common::Response &&rep, const std::string &dest);
        void
        AddNotification(const Common::Response &rep, const std::string &dest);

        private:
        std::mutex &_mutex;
        std::shared_ptr<Common::Log::Log> _logger;
        bool _is_running = false;
        std::shared_ptr<Network::Network> _network;
        std::optional<std::thread> _thread;
        std::list<std::pair<Common::Response, std::string>> _tasks;
    };
}


#endif //BABEL_WORKER_HPP
