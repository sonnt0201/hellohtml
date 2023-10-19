 
/*
    10/2023 by SƠN
    Main Server code goes here
    To compile and run server, open terminal in this 'src' folder then run:
    gcc ../libs/httphelper.c server.c -o server -lws2_32; ./server.exe
*/

#include <stdio.h>
#include <winsock2.h>
#include "../libs/httphelper.h"
#pragma comment(lib, "Ws2_32.lib");
// cd src

int main()
{
    // init winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed. \n");
        return 1;
    }

    // init server
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("failed to create socket server. \n");
        WSACleanup();
        return 1;
    }

    // addr config
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         // ipv4
    serverAddress.sin_port = htons(8080);       // set port for server
    serverAddress.sin_addr.s_addr = INADDR_ANY; // server response to any ip addr

    // bind socket to address config
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("Failed to bind. \n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // turn on listener
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Failed to listen. \n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port: 8080 \n ");

    while (1)
    {

        // init client
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("failed to accept client connection. \n");
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // variable def
        char request[8000] = "";
        int bytesRead;
        char* user = NULL;

        // RECEIVE REQUEST
        while (
            (bytesRead = recv(clientSocket, request, sizeof(request), 0)) > 0)
        {
            printf("message received: \n %s \n", request);
            int type = request_type(request);

            // init link to html page
            char *link = "../web_pages/index.html";

            // MAPPER
            switch (type)
            {
            case HTTP_GET:
                link = "../web_pages/index.html";
                break;
            case HTTP_POST:

            default:
                break;
            }

            FILE *html_file = fopen(link, "r");
            if (html_file == NULL)
            {
                perror("Error opening HTML file. \n");
                return 1;
            }

            // create response
            char *response = create_response(html_file);
            
            //SEND
            send(clientSocket, response, strlen(response), 0);

            // close client socket func goes in inner while, so server can get multi-request
            closesocket(clientSocket);
        }        
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}