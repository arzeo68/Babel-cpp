/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Interface & abstract class for Socket
*/

#ifndef BABEL_SOCKET_HPP
#define BABEL_SOCKET_HPP

#include <memory>

namespace Server::Network {
    /**
     * ISocket is an interface which basic function for any socket
     * @tparam T Template correspond to the socket type
     */
    template<class T>
    class ISocket {
        public:
        virtual ~ISocket() = default;
        virtual void Shutdown() = 0;
        virtual std::shared_ptr<T> GetSocket() = 0;
    };

    /**
     * ASocket is an abstract interface implementing ISocket
     * @tparam T Template correspond to the socket type
     */
    template<class T>
    class ASocket : public ISocket<T> {
        public:
        ~ASocket() override = default;
        virtual void Shutdown() = 0;
        T *operator->() const noexcept {
            return (*this->_socket);
        }
        virtual std::shared_ptr<T> GetSocket() = 0;

        protected:
        std::shared_ptr<T> _socket;
    };
}


#endif //BABEL_SOCKET_HPP
