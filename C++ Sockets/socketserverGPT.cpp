#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <winsock2.h>
#include <pthread.h>

int main()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int wsaerr;
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        cout << endl << "The Winsock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "The Winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // You can choose any available port
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("Error binding socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening for connections");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // Accept a connection from a client
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection established with the client." << std::endl;

    // Send a welcome message to the client
    const char *welcomeMessage = "Welcome to the server!";
    send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
