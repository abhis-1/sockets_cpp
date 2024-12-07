#include <iostream>
// #include <winsock2.h>
// #include <ws2tcpip.h>
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
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "socket() is OK" << endl;
    }
    //======================================================
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(PORT);
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    // memset(&(service.sin_zero), 0, 8);
    // InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);

    if (connect(clientSocket, (SOCKADDR *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        cout << "Client: connect() - failed to connect. " << endl;
        WSACleanup();
        return 0;
    }

    cout << "Client: connect() is OK." << endl;
    cout << "Connected to the server. :)" << endl;
    cout << "Client: Can start sending and receiving data..." << endl;

    const int BUFFER_SIZE = 1024;
    char receiveBuffer[BUFFER_SIZE] = {0};
    int bytesRecieved = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);

    if(bytesRecieved < 0) {
        printf("Client: error %ld.\n", WSAGetLastError());
        return 0;
    }
    else {
        printf("Received data: %s \n", receiveBuffer);
    }

    system("pause");
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}