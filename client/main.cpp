#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common/TCP/CommonPackages.hpp"


void readSocket(boost::asio::ip::tcp::socket *socket) {
    std::array<char, sizeof(Common::Response)> bb = {};
    //std::cout << "sleeping for 15 secs" << std::endl;
    //sleep(2);
    std::cout << "Reading socket" << std::endl;
    socket->read_some(boost::asio::buffer(bb));
    auto r = *(struct Common::Response *) bb.data();
    std::cout << "Read from server: '" << std::string(r.msg) << "'" << std::endl;
    std::cout << "HTTP code: " << std::to_string(static_cast<uint16_t>(r.code)) << std::endl;
    if (r.code != Common::HTTPCodes_e::HTTP_OK) {
        delete socket;
        exit(0);
    }
}

void writeSocket(boost::asio::ip::tcp::socket *socket, Common::PackageServer&& p) {
    std::cout << "Will write w/ route " + std::to_string(p.command) + "..." << std::endl;
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&p, sizeof(p)));

    socket->write_some(buffers);
    //boost::asio::write(sock, buffers);
    std::cout << "Write done" << std::endl;
    readSocket(socket);
}

int main(__attribute__((unused)) int argc, char **argv)
{
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::address::from_string("192.168.1.11"), 4242);
    boost::asio::io_service service;

    if (argv[0] == nullptr)
        return (1);
    auto sock = new boost::asio::ip::tcp::socket(service);
    std::cout << "Connecting to an ip" << std::endl;
    sock->connect(ep);
    writeSocket(sock, Common::PackageServer {
        Common::g_MagicNumber,
        0,
        Common::HTTP_POST,
        1,
        "admin|admin"
    });
    writeSocket(sock, Common::PackageServer {
        Common::g_MagicNumber,
        0,
        Common::HTTP_POST,
        3,
        "new message"
    });


    delete sock;
    return (0);
}
