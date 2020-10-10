/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <thread>
#include "Worker.hpp"
#include "Client.hpp"

Server::Worker::Worker(std::mutex &mutex,
                       std::shared_ptr <Common::Log::Log> logger)
    : _mutex(mutex), _logger(logger) {
}

Server::Worker::~Worker() {
    if (this->_thread->joinable())
        this->_thread->join();
}


void Server::Worker::Run() {
    this->_is_running = true;
    this->_logger->Info("Starting worker...");
    while (this->_is_running) {
        if (this->_tasks.empty()) {
            //std::cerr << "No task available. Sleeping for 1 second... -> " << std::to_string(this->_network->GetClients().size())
            //          << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        this->_logger->Debug("I've ", this->_tasks.size(), " task(s) to do");
        for (auto &task : this->_tasks) {
            this->_mutex.lock();
            for (auto &client: this->_network->GetClients()) {
                if (client->GetUserData().GetName() == task.second) {
                    std::cerr << "Sending data to user '" << task.second << "'"
                              << std::endl;
                    client->Write(task.first);
                    break;
                }
            }
            this->_mutex.unlock();
        }
        this->_logger->Debug("Removing current tasks...");
        this->_tasks.clear();
    }
}

void Server::Worker::AddNotification(const Common::Response &&rep,
                                     const std::string &dest) {
    this->_tasks.emplace_back(std::make_pair(rep, dest));
}

void Server::Worker::AddNotification(const Common::Response &rep,
                                     const std::string &dest) {
    this->_tasks.emplace_back(std::make_pair(rep, dest));
}

void Server::Worker::SetNetwork(std::shared_ptr <Network::Network> network) {
    this->_network = network;
    this->_thread = std::thread(&Worker::Run, this);
}

void Server::Worker::Stop() {
    this->_logger->Info("Stopping worker...");
    this->_is_running = false;
    if (!this->_thread->joinable())
        this->_logger->Error("Thread is non-joinable");
    else {
        this->_logger->Info("Worker stopped");
        this->_thread->join();
    }
}
