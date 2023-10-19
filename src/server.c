
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib");

int main() {
    // init winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. \n");
        return 1;
    }

    // init server
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("failed to create socket server. \n");
        WSACleanup();
        return 1;
    }

    // addr config
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; // ipv4
    serverAddress.sin_port = htons(8080); // set port for server
    serverAddress.sin_addr.s_addr = INADDR_ANY; // server response to any ip addr

    // bind socket to address config 
    if (bind(serverSocket, (struct sockaddr* )&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Failed to bind. \n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;

    }

    //turn on listener
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Failed to listen. \n");
        closesocket(serverSocket);
       WSACleanup();
       return 1;

    }

    printf("Server is listening on port: 8080 \n " );

   while (1) {
        // init client
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("failed to accept client connection. \n");
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        char response[4096] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>";
        char buffer[4096] = "";
        int bytesRead;
        while (
            (bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0))  > 0
        ) {
            printf("message received: \n %s \n" , buffer);
            send(clientSocket, response, strlen(response), 0);
        }

        closesocket(clientSocket);
   
   }

   closesocket(serverSocket);
   WSACleanup();
   return 0;

}