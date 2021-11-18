#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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
            void bindSocket(uint16_t port);

            /**
             * @brief Establish connection with server
             */
            void connect(char hostName, char hostAliases, int hostAddressType, int addressLength, char hostAddressList);

            /**
             * @brief Send a message
             * 
             * @param message The message
             */
            void sendMessage(string message);

            /**
             * @brief Get the File Descriptor 
             * 
             * @return the integer socket file descriptor
             */
            int getFileDescriptor();
    };
}

#endif