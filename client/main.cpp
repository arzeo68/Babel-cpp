#include "src/Network/UDP/NetworkUdp.hpp"

int main(int argc, char **argv)
{
    NetworkUDP p;
    p.startConnection("127.0.0.1", "80");
    while (1);
}

