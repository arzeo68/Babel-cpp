#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include "common/TCP/CommonPackages.hpp"


void readSocket(boost::asio::ip::tcp::socket *socket) {
    std::array <char, sizeof(Common::Response)> bb = {};
    //std::cout << "sleeping for 15 secs" << std::endl;
    //sleep(2);
    std::cout << "Reading socket" << std::endl;
    socket->read_some(boost::asio::buffer(bb));
    auto r = *(struct Common::Response *) bb.data();
    std::cout << "Read from server: '" << std::string(r.msg) << "'"
              << std::endl;
    std::cout << "HTTP code: " << std::to_string(static_cast<uint16_t>(r.code))
              << std::endl;
    if (r.code == Common::HTTPCodes_e::FAKE_HTTP_END_PAGINATION ||
        r.code == Common::HTTPCodes_e::FAKE_HTTP_PAGINATION)
        readSocket(socket);
    else if (r.code != Common::HTTPCodes_e::HTTP_OK) {
        delete socket;
        exit(0);
    }
}

void writeSocket(boost::asio::ip::tcp::socket *socket, Common::PackageServer&& p) {
    std::cout << "Will write w/ route " + std::to_string(p.command) + "..."
              << std::endl;
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&p, sizeof(p)));

    socket->write_some(buffers);
    //boost::asio::write(sock, buffers);
    std::cout << "Write done" << std::endl;
    readSocket(socket);
}

#ifdef _WIN32
    #define UNUSED(v)
#else
    #define UNUSED(v) __attribute__((unused)) v
#endif

int main(int UNUSED(argc), char **argv) {
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::address::from_string("127.0.0.1"), 4242);
    boost::asio::io_service service;

    /*
     * 0: USER EXISTS
     * 1: LOGIN
     * 2: REGISTER
     * 3: UPDATE STATUS
     * 4: FRIENDS
     *  - PUT: add
     *  - POST: accept/decline
     *  - DELETE: remove
     *  - GET: all friends
     */

    if (argv[0] == nullptr)
        return (1);
    auto socket = new boost::asio::ip::tcp::socket(service);
    std::cout << "Connecting to an ip" << std::endl;
    socket->connect(ep);
    //writeSocket(socket, Common::PackageServer {
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_POST,
    //    2,
    //    "admin|admin"
    //});
    //writeSocket(socket, Common::PackageServer {
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_POST,
    //    2,
    //    "dayrion|password"
    //});
    //
    //writeSocket(socket, Common::PackageServer{
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_POST,
    //    1,
    //    "dayrion|password"
    //});
    //readSocket(socket);


    //std::cout << "Sleeping for 16 secs" << std::endl;
    //sleep(16);
    writeSocket(socket, Common::PackageServer {
        Common::g_MagicNumber,
        0,
        Common::HTTP_POST,
        1,
        "admin|admin"
    });
    writeSocket(socket, Common::PackageServer {
        Common::g_MagicNumber,
        0,
        Common::HTTP_GET,
        5,
        "world"
    });
    //writeSocket(socket, Common::PackageServer{
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_PUT,
    //    4,
    //    "dayrion"
    //});
    //writeSocket(socket, Common::PackageServer{
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_POST,
    //    4,
    //    "dayrion|2"
    //});
    //writeSocket(socket, Common::PackageServer{
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_DELETE,
    //    4,
    //    "dayrion"
    //});
    //writeSocket(socket, Common::PackageServer{
    //    Common::g_MagicNumber,
    //    0,
    //    Common::HTTP_GET,
    //    4,
    //    ""
    //});

    //std::cout << "Sleeping for 6 secs" << std::endl;
    //sleep(6);


    delete socket;
    return (0);
}
