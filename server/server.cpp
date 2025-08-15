#include <iostream>
#include <thread>
#include <vector>
#include "WSA.h"
#include "Socket.h"

#define MAX_CLIENTS 3
void recvMsgFromClient(SOCKET client, Socket& server, std::vector<SOCKET>& clients);
int main() {
    WSA wsa;
    if (wsa.wsa_err) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError();
        return 1;
    }
    try {
        std::cout << "creating socket...\n";
        Socket server(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        int port;
        std::cout << "Enter port: ";
        std::cin >> port;
        sockaddr_in serverIP = createIPv4Addr("", port);    

        std::cout << "binding socket...\n";
        server.bind(&serverIP);

        std::cout << "listening socket...\n";
        server.listen(MAX_CLIENTS);

        std::vector<SOCKET> clients;
        while(true) {
            sockaddr_in clientIP;
            SOCKET client = server.accept(&clientIP);
            clients.emplace_back(client);
            std::thread worker(recvMsgFromClient, client, std::ref(server), std::ref(clients));
            worker.detach();
        }
        std::cout << "THANKS FOR USING MY CHAT APPLICATION\n"; 
    }
    catch (SocketException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

void recvMsgFromClient(SOCKET client, Socket& server, std::vector<SOCKET>& clients) {
    while (true) {
        std::string buf;
        int bytesRecv = recv(client, buf, 0);
        if(bytesRecv == 0)
            break;
        std::cout << buf << std::endl;
        for(auto cl: clients) {
            if (cl != client) {
                send(cl, buf, 0);
            }
        }
    }
}