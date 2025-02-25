#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <winsock2.h>
#include <ws2tcpip.h>

namespace Client {
    SOCKET initClientSocket(int argc, char* argv[], addrinfo*& result, addrinfo*& ptr, addrinfo* hints);
    int connectSocket(SOCKET& connectionSocket, addrinfo* ptr);
    int sendToServer(SOCKET& connectionSocket, char mail[500]);
    int shutDownConnectionSocket(SOCKET& connectionSocket);
}

#endif // CLIENTSOCKET_H