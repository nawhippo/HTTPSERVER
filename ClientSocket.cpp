#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define DEFAULT_PORT "27015"

int initClientSocket(int argc, char* argv[]){
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    int iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0){
        std::cout << "Error in getting addrinfo" << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    ptr = result;
    connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connectSocket == INVALID_SOCKET){
        std::cout << "Invalid socket.. error with connection" << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    return 0;
}

int connectSocket(SOCKET& connectionSocket, const sockaddr* addrinfo){
    int iResult = connect(connectionSocket, addrinfo->ai_addr, (int)addrinfo->ai_addrlen);
    if (iResult == SOCKET_ERROR){
        closesocket(connectionSocket);
        connectionSocket = INVALID_SOCKET;
    }
    freeaddrinfo(addrinfo);
    if (connectionSocket == INVALID_SOCKET){
        std::cout << "Error with client socket connection" << std::endl;
        WSACleanup();
        return 1;
    }
    return 0;
}


int sendToServer(SOCKET& connectionSocket, char mail[500]){
    int iResult;
    char receivingBuffer[500];
    int iResult = send(connectionSocket, mail, 500, 0);
    if (iResult == SOCKET_ERROR){
        closesocket(connectionSocket);
        connectionSocket = INVALID_SOCKET;
        WSACleanup();
    }
    if (connectionSocket == INVALID_SOCKET){
        std::cout << "Error with sending message connection" << std::endl;
        return 1;
    } else {
        std::cout << "Message sent successfully!" << std::endl;
        return 0;
}
    iResult = shutdown(connectionSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cout << "shutdown failed....." << std::endl;
        closesocket(connectionSocket);
        WSACleanup();
        return 1;
    }
    do {
        iResult = recv(connectionSocket, receivingBuffer, 500, 0);
        if (iResult > 0){
            printf("We got this result from the server..", iResult);
        } else if (iResult == 0){
            std::cout << "Connection has been closed." << std::endl;
        } else {
            std::cout << "Error in receiving message." << std::endl;
        }   
    } while (iResult > 0);
    return 0;
}


int shutDownConnectionSocket(SOCKET& connectionSocket){
    int iResult = shutdown(connectionSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cout << "Shutdown failed" << std::endl;
        closesocket(connectionSocket);
        WSACleanup();
        return 1;
    }
    closesocket(connectionSocket);
    WSACleanup();
    return 0;
}