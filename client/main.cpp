#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>
#include <iostream>
<<<<<<< HEAD
#include <boost/asio.hpp>
=======
>>>>>>> cca3000383c09850c1a28a24088500b9de7286af

#include "common/Protocol.hpp"

int main(int argc, char **argv)
{
    boost::asio::ip::tcp::endpoint ep(
<<<<<<< HEAD
        boost::asio::ip::address::from_string("163.5.141.231"), 4242);
=======
        boost::asio::ip::address::from_string("192.168.1.11"), 4242);
>>>>>>> cca3000383c09850c1a28a24088500b9de7286af
    boost::asio::io_service service;

    if (argv[0] == nullptr)
        return (1);
    auto sock = new boost::asio::ip::tcp::socket(service);
    std::cout << "Connecting to an ip" << std::endl;
    sock->connect(ep);
<<<<<<< HEAD
    return (0);
}
=======
    Common::PackageServer p {
        Common::g_MagicNumber,
        0,
        Common::POST,
        1,
        "user|password"
    };
    //char p[262] = "hello world";
    std::cout << "Will write..." << std::endl;
>>>>>>> cca3000383c09850c1a28a24088500b9de7286af

    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&p, sizeof(p)));

    sock->write_some(buffers);
    //boost::asio::write(sock, buffers);
    std::cout << "Write done" << std::endl;
    std::array<char, sizeof(Common::Response)> bb = {};
    std::cout << "sleeping for 15 secs" << std::endl;
    sleep(15);
    std::cout << "let met reead now" << std::endl;
    sock->read_some(boost::asio::buffer(bb));
    auto r = *(struct Common::Response *) bb.data();
    std::cout << "Read from server: '" << std::string(r.msg) << "'" << std::endl;
    std::cout << "HTTP code: " << std::to_string(static_cast<uint16_t>(r.code)) << std::endl;
    return (0);
}
