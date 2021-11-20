#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

namespace Ayanami {

    /**
     * @brief Client side socket implimentation
     */
    class Socket {

        // https://man7.org/linux/man-pages/man2/socket.2.html
        
        // The socket file descriptor
        int socketFileDescriptor;

        // The communication domain of the socket
        int domain;

        // The socket type
        int type;

        public:

            /**
             * @brief Construct a new Socket object
             * 
             * @param dom The communication domain, i.e, AF_NET for IPv4 Internet protocols
             * @param typ The socket type, i.e, SOCK_STREAM
             */
            Socket(int dom, int typ);

            /**
             * @brief Bind socket to an address
             * 
             * @param port The port number, 0 for OS delegation
             */
            bool bindSocket(uint16_t port);

            /**
             * @brief Establish connection with server
             * 
             * @param svr The host name of the server
             * @param port The port number
             */
            bool connectToServer(string svr, uint16_t port);

            /**
             * @brief Send a message to the server
             * 
             * @param message The message
             */
            void sendMessage(string message);

            /**
             * @brief Get the File Descriptor 
             * 
             * @return The integer socket file descriptor
             */
            int getFileDescriptor();
    };
}

#endif