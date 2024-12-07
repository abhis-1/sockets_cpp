#include <iostream>
#include <winsock.h>
using namespace std;

#define PORT 9999

int main()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int wsaerr;
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        cout << endl
             << "The Winsock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "The Winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }
    //-----------------------------------------------------------------------
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "socket() is OK" << endl;
    }
    // -------------------------------------------------------------------
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr *)&address, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "bind() is OK" << endl;
    }
    //--------------------------------------------------------------------
    if (listen(serverSocket, 10) == SOCKET_ERROR)
    {
        cout << "listen(): Error listening on socket, " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "listen() is OK, I'm waiting for connections..." << endl;
    }

    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    else {
        cout << "Accepted Connection" << endl;
    }
    //------------------------------------------------------------------
    const int BUFFER_SIZE = 1024;
    char sendBuffer[BUFFER_SIZE];
    // printf("Welcome to abhis server!\nEnter your message: ");
    // cin.getline(sendBuffer, BUFFER_SIZE);
    // cout << "You typed:\n"
    //      << sendBuffer << endl;
    // //------------------------------------------------------------------
    // int bytesSent = sendto(acceptSocket, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *)&address, sizeof(address));
    // if (bytesSent == SOCKET_ERROR)
    // {
    //     printf("Error transmitting data %ld.\n", WSAGetLastError());
    //     return -1;
    // }
    // else
    // {
    //     printf("\n\nData sent.\nServer: sent %ld bytes \n", bytesSent);
    // }
    const int BUFFER_SIZE = 1024;
    char Buffer[BUFFER_SIZE] = {0};
    cout << "Please enter a message to send the Server" << endl;
    cin.getline(Buffer, BUFFER_SIZE);
    int serverAddress = (int)sizeof(address);
    int bytesRecieved = recvfrom(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0, (struct sockaddr *)&clientService, &clientAddress);
    // int bytesRecieved = send(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);

    if (bytesRecieved < 0)
    {
        printf("Could not receive datagram.\nClient: error %ld.\n", WSAGetLastError());
        WSACleanup();
        return 0;
    }
    else
    {
        printf("Received data: %s \n", receiveBuffer);
    }



    WSACleanup();
    closesocket(serverSocket);
}



//Vector 3D
// a class representing a 3d vector with x, y, z member variables
// x, y, z are public and can therefore be manipulated directly
// primitive data types should be converted to char array before being transmitted
// the sprintf() performs this task
// sprintf( char* buffer, const char * format, list of arguments)
// the & character in the format is placeholder, 6.1 indicated the size and decimal places 
// and the f that a float will be passed to it
