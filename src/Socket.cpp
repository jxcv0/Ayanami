#include "Socket.hpp"

using namespace std;

Ayanami::Socket::Socket(int dom, int typ) {
    domain = dom;
    type = typ;
};

bool Ayanami::Socket::bindSocket(uint16_t port) {
    socketFileDescriptor = socket(domain, type, 0);
    if (socketFileDescriptor < 0) {
        fprintf(stderr, "ERROR: Unable to create socket\n");
        return false;
    }

    struct sockaddr_in socketAddress;

    memset(&socketAddress, 0, sizeof(socketAddress));

    socketAddress.sin_family = domain;
    socketAddress.sin_port = htons(port);

    if (bind(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress))) {
        fprintf(stderr, "ERROR: Unable to bind socket\n");
        return false;
    }

    return true;
};

bool Ayanami::Socket::connectToServer(string svr, uint16_t port) {
    auto server = gethostbyname(svr.c_str());
    if (server == NULL) {
        fprintf(stderr, "ERROR: No such host\n");
        return false;
    }

    struct sockaddr_in socketAddress;

    bzero((char *) &socketAddress, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr, (char *)&socketAddress.sin_addr.s_addr, server->h_length);
    socketAddress.sin_port = htons(port);

    if (connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(server)) < 0) {
        fprintf(stderr, "ERROR: Unable to connect\n");
        return false;
    }

    return true;
};

int Ayanami::Socket::getFileDescriptor() {
    return socketFileDescriptor;
};