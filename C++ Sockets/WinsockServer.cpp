// Socket Server
/*
    1. Initialize WSA - WSAStartup()
    2. Create a socket - socket()
    3. Bind the socket - bind()
    4. Listen on the socket - listen()
    5. Accept a connection - accept(), connect()
    6. Send and receive data - recv(), send(), recvfrom(), sendto()
    7. Disconnect - closesocket()
*/

#include <iostream>
#include <winsock.h>
using namespace std;

#define PORT 55555

int main()
{
    //=======================================================
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
    //=========================================================
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
    //============================================================
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(PORT);
    service.sin_addr.s_addr = INADDR_ANY;
    // InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    memset(&(service.sin_zero), 0, 8);
    if (bind(serverSocket, (sockaddr *)&service, sizeof(sockaddr)) == SOCKET_ERROR)
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
    //==============================================================
    if (listen(serverSocket, 10) == SOCKET_ERROR)
    {
        cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "listen() is OK, I'm waiting for connections..." << endl;
    }
    //==================================================================
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    cout << "Connection established with the client." << endl;

    const int BUFFER_SIZE = 1024;
    char sendBuffer[BUFFER_SIZE];
    printf("Welcome to abhis server!\nEnter your message: ");
    cin.getline(sendBuffer, BUFFER_SIZE);
    cout << "You typed:\n"
         << sendBuffer << endl;
    int bytesSent = send(acceptSocket, sendBuffer, sizeof(sendBuffer), 0);
    if (bytesSent == SOCKET_ERROR)
    {
        printf("Server send error %ld.\n", WSAGetLastError());
        return -1;
    }
    else
    {
        printf("Server: sent %ld bytes \n", bytesSent);
    }

    //Transmitting Objects
    // Sending an object. Assuming the class Data has been defined elsewhere. Cast the object's address to a char*

    // Data data;
    // data.health = 100;
    // byteCount = send(socket, (char*) &data, sizeof(Data), 0);

    // Receiving an object
    // Data data;
    // byteCount = recv(clientSocket, (char*) &data, sizeof(Data), 0);
    // printf("Health: \"%d\"\n", data.health);

    //Assigning values to char array
    // char sendBuffer[200] = "Message received by server";
    //We can't however use the assignment operator after it has been defined
    // instead we must use the strcpy function or if depreciated strcpy_s
    // char buffer[200];
    // strcpy_s(buffer,"heelo world");
    // use the strlen function to return the number of characters in the array
    // strlen(sendBuffer);

    //  the strcpm() function compares two strings
    // int strcpm( const char* string1, const char* string2);
    // takes two string as arguments (pointers to character arrays)
    // returns 0 if they are equal 
    // returns <0 if string1 less than string2
    // returns >0 if string2 greater than string2
    // if(strcmp(buffer,"Password") == 0) {
    //     //string are equal
    // }

    WSACleanup();
    closesocket(serverSocket);
}