#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define DEFAULT_PORT "27015"

namespace ServerSock {
int initServerSocket(SOCKET& listenSocket, addrinfo*& result);
int bindSocket(SOCKET& listenSocket, addrinfo* result);
int listenSocket(SOCKET& socket);
int acceptSocketConnections(SOCKET& socket);
int receiveFromSocket(SOCKET& recvsocket);

int main(){
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    SOCKET listenSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    char[500] globalStateObject;
    std::memset(globalStateObject, '\0', sizeof(globalStateObject));


    if (initServerSocket(listenSocket, result) != 0) {
        WSACleanup();
        return 1;
    }

    if (bindSocket(listenSocket, result) != 0) {
        WSACleanup();
        return 1;
    }

    if (listenSocket(listenSocket) != 0) {
        WSACleanup();
        return 1;
    }

    if (acceptSocketConnections(listenSocket) != 0) {
        WSACleanup();
        return 1;
    }
    cout << "Server socket setup successful!" << endl;
    return 0;
}

int initServerSocket(SOCKET& listenSocket, addrinfo*& result){
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0){
        printf("addr info failure!: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET){
        std::cout << "Invalid socket defined." << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    return l;
}

int bindSocket(SOCKET& listenSocket, addrinfo* result){
    int iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if(iResult == SOCKET_ERROR){
        std::cout << "Socket error from bind" << std::endl;
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);
    return 0;
}

int listenSocket(SOCKET& socket){
    if (listen(socket, SOMAXCONN) == SOCKET_ERROR){
        std::cout << "Yowzah... socket error!" << std::endl;
        closesocket(socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int acceptSocketConnections(SOCKET& socket){
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = accept(socket, NULL, NULL);
    if (clientSocket == SOCKET_ERROR) {
        std::cout << "FRICK! accept socket error!" << std::endl;
        closesocket(socket);
        WSACleanup();
        return 1;
    } if clientSocket != INVALID_SOCKET {
        std::cout << "Client socket accepted."<<  << std::endl;
    }
    return receiveFromSocket(clientSocket);
}

int receiveFromSocket(SOCKET& recvsocket, char[500] globalObjectState){
    int bufferLen = 530;
    char buffer[bufferLen];
    int result = recv(recvsocket, buffer, bufferLen, 0);
    std::span<char> subspan(buffer, 3)
    std::span<char> response = subspan;
    
    if (strcmp(response, "GET") == 0){
        std::span<char> subspan(buffer + 3, 500);
        std::span<char> remainderstring = subspan;
        std::cout << "" << remainderstring << std::endl;
        send(recvsocket, globalObjectState, 0);
    }

    if (strcmp(response, "PUT") == 0){
        //assume space.
        std::span<char> subspan(buffer + 4, 500);
        std::span<char> remainderstring = subspan;
        char[500] response = "PUT request received."
        send(recvsocket, response, 0);
        *globalObjectState = remainderstring;
        std::cout << "" << remainderstring << std::endl;
    }
    if (strcmp(response, "DEL") == 0){
        char[500] response = "DEL request received."
        send(recvsocket, response, 0);
        globalObjectState = NULL;
    }
    if (strcmp(response, "ADD") == 0){
        //assume space for command
        std::span<char> subspan(buffer + 4, 500);
        std::span<char> remainderstring = subspan;
        std::cout << "" << remainderstring << std::endl;
    }
    if (result <= 0){
        std::cout << "FRICK, RECVFROM ERROR, WE GOT TROUBLE!" << std::endl;
        closesocket(recvsocket);
        WSACleanup();
        return 1;

    } else {
        const char* response = "Response received.";
        int iResultResponseSocket = send(recvsocket, response, strlen(response), 0);
        if (iResultResponseSocket <= 0){
            std::cout << "FRICK! Trouble sending response to client!" << std::endl;
        } else {
            std::cout << "Response transmitted successfully." << std::endl;
        }
    }
    closesocket(recvsocket);
    WSACleanup();
    return 0;
}

}