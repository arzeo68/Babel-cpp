/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Interface for the network
*/

#ifndef SRC_BABEL_INETWORK_
#define SRC_BABEL_INETWORK_

#include <memory>
#include <cstdint>

namespace Server::Network {
    class Client;

    typedef std::shared_ptr<Client> SharedPtrClient_t;

    /**
     * Interface with basic functions
     */
    class INetwork {
        public:
        virtual ~INetwork() = default;
        /**
         * Run the network. This function might add client
         */
        virtual void Run() = 0;
        /**
         * Stop the network
         */
        virtual void Stop() = 0;
        /**
         * Remove a client from the network
         */
        virtual void RemoveClient(const std::shared_ptr<Client> &) = 0;
    };

    /**
     * Abstract class for network
     */
    class ANetwork : public INetwork {
        public:
        /**
         * Get the list of all clients
         * @return A list of smart pointer of clients
         */
        virtual std::list<SharedPtrClient_t> GetClients() = 0;

        protected:
        /**
         * Boolean corresponding to the network's state
         */
        bool _is_running = false;
        /**
         *List of shared pointer of clients
         */
        std::list<SharedPtrClient_t> _clients;
        /**
         * The mutex to the thread-safety for the list of clients
         */
        std::mutex _mutex;
    };
}

#endif
