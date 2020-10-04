#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "common/Protocol.hpp"

int main(int argc, char **argv)
{
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::address::from_string("192.168.1.11"), 4242);
    boost::asio::io_service service;

    if (argv[0] == nullptr)
        return (1);
    auto sock = new boost::asio::ip::tcp::socket(service);
    std::cout << "Connecting to an ip" << std::endl;
    sock->connect(ep);
    Common::PackageServer p {
        Common::g_MagicNumber,
        0,
        Common::GET,
        0,
        "user"
    };
    std::cout << "Will write..." << std::endl;



    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&p, sizeof(p)));

    sock->write_some(buffers);
    //boost::asio::write(sock, buffers);
    std::cout << "Write done" << std::endl;
    std::array<char, sizeof(Common::Response)> bb = {};
    sleep(50);
    std::cout << "let met reead" << std::endl;
    sock->read_some(boost::asio::buffer(bb));
    auto r = *(struct Common::Response *) bb.data();
    std::cout << "Read from server: '" << std::string(r.msg) << "'" << std::endl;
    return (0);
}

