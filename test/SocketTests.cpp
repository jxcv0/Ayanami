#include <gtest/gtest.h>
#include "Socket.hpp"

TEST(SocketTests, fileDescriptorCreation) {
    Ayanami::Socket socket(AF_INET, SOCK_STREAM);
    ASSERT_TRUE(0 < socket.getFileDescriptor());
}