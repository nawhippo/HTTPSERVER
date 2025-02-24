//HTTP Server
#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define DEFAULT_PORT "27015"


int initServerSocket(){
struct addrinfo *result = NULL, *ptr = NULL, hints;
ZeroMemory(&hints, sizeof(hints));
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;
hints.ai_protocol = IPPROTO_TCP;
hints.ai_flags = AI_PASSIVE;

//addr for bind stoed in result
int iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
if (iResult != 0){
    printf("addr info failure!: %d\n", iResult);
    WSACleanup();
    return 1;
}

SOCKET listenSocket = INVALID_SOCKET;
listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
if (listenSocket == INVALID_SOCKET){
    std::cout << "Invalid socket defined." << std::endl;
}

int bindSocket(){
iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);

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


int listenSocket(SOCKET &socket){
if (listen(socket, SOMAXCONN) == SOCKET_ERROR){
    std::cout << "Yowzah... socket error!" << std::endl;
    closesocket(socket);
    WSACleanup();
    return 1;
}
return 0;
}

int acceptSocketConnections(SOCKET &socket){
SOCKET clientSocket;
clientSocket = INVALID_SOCKET;
clientSocket = accept(socket, NULL, NULL);
if (clientSocket == SOCKET_ERROR) {
    std::cout << "FRICK! accept socket error!" << std::endl;
    closesocket(socket);
    WSACleanup();
    return 1;
}
return 0;
}

int receiveFromSocket(SOCKET &recvsocket){
int bufferLen = 530;
char buffer[bufferLen];
result = recv(recvsocket, &buffer, bufferLen, 0);
if (result <= 0){
    std::cout << "FRICK, RECVFROM ERROR, WE GOT TROUBLE!" << std::endl;
    closesocket(recvsocket);
} else {
    char[21] response;
    response = "Response received.";
    iResultResponseSocket = send(recvsocket, response, len(response), 0);
    if (iResultResponseSocket <= 0){
        std::cout << "FRICK! Trouble sending response to client!" << std::endl;
    } else {
        std::cout << "Response transmitted successfully." << std::endl;
        WSACleanup();
        return 1;
    }
}
return 0
}









std::cout << "Great success";
return 0;
}




int main(){
    return server();
}
// func initclient(){
// int clientsockeet = socket(AF_INET, SOCK_STREAM, 0);
// int clientaccept = accept(serverSocket, nullptr, nullptr);
// int connectsuccess connect(client, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
// if (connectsuccess == 0){
//     cout << "Client initialized successfully";
// } else {
//     cout << "Something went wrong with client.";
// }
// return 0;
// }

// func sendToServer(int client, int server, string message){
// const char* message = "Hello!";
// cout << "Sending message to server."
// send(client, message, strlen(message), 0);
// if (send == 0){
// cout << "info sent successfully";
// } else {
// cout << "Something went wrong with sending info to server.";
// }
// return 0;
// }


// func getRequest(int &client, int &server){
//     client.send("GET");
//     buffer[256];
//     //we receive information from a port no?
//     server.recv(client, buffer, sizeof(char) * len(buffer));
//     cout << string(buffer);
// }


// func putRequest(int &client, int &server){
//     client.send("PUT")
//     char[300]
//     std.in("Please enter message to append to server")
//     buffer[256];
//     //
//     message = server.recv(client, buffer, sizeof(char) * len(buffer), 0);
//     char * globalmessageptr = &globalmessage;
//     int charcounter = 0;
//     while(globalmessageptr != NULL){
//         charcounter += 1;
//         //iterate through char array. 
//         globalmessageptr += sizeof(char)
//     }

//     //memory won't be predictable the globalmessageptr... it has been malloced onto the heap already.
//     char * finalmessage = malloc((sizeof(char) * charcounter))
//     while(p < charcounter){
        
//     }




//     cout << string(message);

// }

