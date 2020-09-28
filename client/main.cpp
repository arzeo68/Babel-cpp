#include <iostream>
#include <boost/asio.hpp>


int main(int argc, char **argv)
{
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::address::from_string("163.5.141.231"), 4242);
    boost::asio::io_service service;

    if (argv[0] == nullptr)
        return (1);
    auto sock = new boost::asio::ip::tcp::socket(service);
    std::cout << "Connecting to an ip" << std::endl;
    sock->connect(ep);
    return (0);
}

