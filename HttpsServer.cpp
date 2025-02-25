//components of an https server 
// socket creation...
// REST functions...
// some element of security... ssl validation? or rather tls. 
#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#define DEFAULT_PORT "27015"
#include <ClientSocket.h>
#include <ServerSocket.h>

using namespace Client;
using namespace ServerSock; 


int main(){
    ServerSock.main();
    Client.main();
    //initialized
    char messageState[500];
    char objectSampleState[500];
    crudReqs()
    return 0;   
}

int crudReqs(SOCKET masterSocket, &objectSampleState){
    char receivingmessage[500];
    char message[500];
    
    client.send(masterSocket, message, 500, 0);
    ServerSOCK.receivefromClient(masterSocket);
    if (message == "GET") {
       ServerSock.sendMessageToClient(&objectSampleState);
    }
    if (message == "PUT") {
        
    }

}





