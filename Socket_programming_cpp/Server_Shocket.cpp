#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")


int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    int c;
    const char* message;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed. Error Code : " << WSAGetLastError();
        return 1;
    }

    // Create a socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "Could not create socket : " << WSAGetLastError();
        WSACleanup();
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    if (bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "Bind failed with error code : " << WSAGetLastError();
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen to incoming connections
    listen(serverSocket, 3);

    // Accept and incoming connection
    std::cout << "Waiting for incoming connections..." << std::endl;
    c = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error code : " << WSAGetLastError();
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Reply to client
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    //const char* message = "Hello Client , I have received your connection. But I have to go now, bye\n";

    send(clientSocket, message, strlen(message), 0);

    // Cleanup
    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
