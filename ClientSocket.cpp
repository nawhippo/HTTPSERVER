#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define DEFAULT_PORT "27015"


namespace Client {
SOCKET initClientSocket(addrinfo*& result, addrinfo*& ptr, addrinfo* hints);
int connectSocket(SOCKET& connectionSocket, addrinfo* ptr);
int sendToServer(SOCKET& connectionSocket, char mail[500]);
int shutDownConnectionSocket(SOCKET& connectionSocket);

int main(){
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    char* argv[1];
    char* defaultaddy = "bonkbonky";
    argv[0] = defaultaddy;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    SOCKET connectsocket = initClientSocket(1, argv, result, ptr, &hints);
    if (connectsocket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    if (connectSocket(connectsocket, ptr) != 0) {
        WSACleanup();
        return 1;
    }

    if (shutDownConnectionSocket(connectsocket) != 0) {
        WSACleanup();
        return 1;
    }
    cout << "Client socket setup successful!" << endl;
    return 0;
}

SOCKET initClientSocket(addrinfo*& result, addrinfo*& ptr, addrinfo* hints){
    ZeroMemory(hints, sizeof(*hints));
    int iResult = getaddrinfo(argv[0], DEFAULT_PORT, hints, &result);
    if (iResult != 0){
        std::cout << "Error in getting addrinfo: " << iResult << std::endl;
        WSACleanup();
        return INVALID_SOCKET;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    ptr = result;
    connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connectSocket == INVALID_SOCKET){
        std::cout << "Invalid socket.. error with connection" << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return INVALID_SOCKET;
    }
    return connectSocket;
}

int connectSocket(SOCKET& connectionSocket, addrinfo* ptr){
    int iResult = connect(connectionSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR){
        closesocket(connectionSocket);
        connectionSocket = INVALID_SOCKET;
    }
    freeaddrinfo(ptr);
    if (connectionSocket == INVALID_SOCKET){
        std::cout << "Error with client socket connection" << std::endl;
        WSACleanup();
        return 1;
    }
    return 0;
}

int sendToServer(SOCKET& connectionSocket, char[500] mail){
    int iResult;
    char receivingBuffer[500];
    iResult = send(connectionSocket, mail, 500, 0);
    if (iResult == SOCKET_ERROR){
        std::cout << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(connectionSocket);
        connectionSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }
    std::cout << "Message sent successfully!" << std::endl;
}

int shutDownConnectionSocket(SOCKET& connectionSocket){
    int iResult = shutdown(connectionSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cout << "Shutdown failed: " << WSAGetLastError() << std::endl;
        closesocket(connectionSocket);
        WSACleanup();
        return 1;
    }
    closesocket(connectionSocket);
    WSACleanup();
    return 0;
}
}