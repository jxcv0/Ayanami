#include "Socket.hpp"

using namespace std;

Ayanami::Socket::Socket(int dom, int typ) {
    domain = dom;
    type = typ;
};

void Ayanami::Socket::bindSocket(uint16_t port) {
    if (socket(domain, type, 0) < 0) {
        fprintf(stderr, "ERROR: Unable to create socket\n");
        // return false?
    }

    struct sockaddr_in socketAddress;

    memset(&socketAddress, 0, sizeof(socketAddress));

    socketAddress.sin_family = domain;
    socketAddress.sin_port = htons(port);

    if (bind(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress))) {
        fprintf(stderr, "ERROR: Unable to bind socket\n");
        // return false?
    }
};

int Ayanami::Socket::getFileDescriptor() {
    return socketFileDescriptor;
};