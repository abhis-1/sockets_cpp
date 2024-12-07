#include <iostream>
#include <winsock.h>
using namespace std;

#define S_PORT 5050

struct sockaddr_in srv;         // Socket address (internet style)
fd_set fr, fw, fe;              // socket descriptors fr- ready to read, fw - ready to write, fe - exceptions having errors

int main() {

    // 0. Initialize the WSA variables -> to enable socket programming on windows machine
    // 1. Initialize the socket
    // 2. Initialize the environment for sockaddr structure
    // 3. Bind the socket to the local port
    // 4. Listen the request from client (queue the requests)
    // 5. Keep waiting for new requests and proceed as per the request

//===================================0===================================
    int nRet = 0;
    WSADATA ws;
    if( WSAStartup(MAKEWORD(2, 2), &ws) < 0){
        cout << endl << "WSA Failed to initialize";
        exit(EXIT_FAILURE);
    }
    else{
        cout << endl << "The socket opened successfully";
    }
//===================================1==================================
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0){
        cout << endl << "The socket not opened";
        exit(EXIT_FAILURE);

    }
    else {
        cout << endl << "The socket opened succesfully" << endl << nSocket;
    }
//====================================2======================================
    srv.sin_family = AF_INET;
    srv.sin_port = htons(S_PORT);
    srv.sin_addr.s_addr = INADDR_ANY;
    memset(&(srv.sin_zero), 0, 8);
//=====================================3=======================================
    nRet = bind(nSocket, (sockaddr*) &srv, sizeof(sockaddr));
    if (nRet < 0) {
        cout << endl << "failed to bind to local port";
        exit(EXIT_FAILURE);
    }
    else {
        cout << endl << "Successfully bind to local port";
    }
//===============================4===============================================
    nRet = listen(nSocket, 5);
    if (nRet < 0) {
        cout << endl << "failed to Start listening to local port";
        exit(EXIT_FAILURE);
    }
    else {
        cout << endl << "Started listening to local port";
    }
//================================5=============================================

    

}