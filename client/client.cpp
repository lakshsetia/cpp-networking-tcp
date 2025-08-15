#include <winsock2.h>
#include <iostream>
#include <thread>
#include "Socket.h"
#include "WSA.h"

void recvMsgFromServer(Socket& client);
int main() {
    WSA wsa;
    if (wsa.wsa_err) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError();
        return 1;
    }
    try {
        std::cout << "creating socket...\n";
        Socket client(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in clientIP = createIPv4Addr("", 5400);

        std::cout << "Enter server information\n";
        std::string serverAddr;
        int port;
        std::cout << "Enter IP addr: ";
        std::cin >> serverAddr;
        std::cout << "Enter port: ";
        std::cin >> port;

        sockaddr_in serverIP = createIPv4Addr(serverAddr, port);
        std::cout << "connecting to socket...\n";
        client.connect(&serverIP);

        while(true) {
            std::string buf;
            std::thread worker(recvMsgFromServer, std::ref(client));
            worker.detach();
            getline(std::cin, buf);
            if(buf == "exit" || buf == "quit")
                break;
            send(client.fd, buf, 0);
        }
    }
    catch (SocketException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
void recvMsgFromServer(Socket& client) {
    while(true) {
        std::string buf;
        int bytesRecv = recv(client.fd, buf, 0);
        if (bytesRecv == 0)     
            break;
        std::cout << buf << std::endl;
    }
}