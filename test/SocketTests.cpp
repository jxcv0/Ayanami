#include <gtest/gtest.h>
#include "Socket.hpp"

TEST(SocketTests, createSocket) {
    Ayanami::Socket socket(AF_INET, SOCK_STREAM);
    ASSERT_TRUE(0 < socket.getFileDescriptor());
}

TEST(SocketTests, bindSocket) {
    Ayanami::Socket socket(AF_INET, SOCK_STREAM);
    ASSERT_TRUE(socket.bindSocket(0));
}

TEST(SocketTests, connect) {
    Ayanami::Socket socket(AF_INET, SOCK_STREAM);
    ASSERT_TRUE(socket.connectToServer("cs.rpi.edu", 0));
}