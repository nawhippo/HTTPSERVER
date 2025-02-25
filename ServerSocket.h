#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <winsock2.h>
#include <ws2tcpip.h>

namespace ServerSock {
    int initServerSocket(SOCKET& listenSocket, addrinfo*& result);
    int bindSocket(SOCKET& listenSocket, addrinfo* result);
    int listenSocket(SOCKET& socket);
    int acceptSocketConnections(SOCKET& socket);
    int receiveFromSocket(SOCKET& recvsocket);
    int sendMessageToClient(SOCKET& Socket, char message[500]);
}

#endif // SERVERSOCKET_H