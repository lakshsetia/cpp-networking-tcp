#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

class Socket {
public:
    SOCKET fd;
    Socket(int family, int type, int protocol);
    ~Socket();

    void bind(const sockaddr_in* addr);
    void bind(const sockaddr_in6* addr);

    void connect(const sockaddr_in* addr);
    void connect(const sockaddr_in6* addr);

    void listen(int backlog);

    SOCKET accept(const sockaddr_in* addr);
    SOCKET accept(const sockaddr_in6* addr);
};

class SocketException: public std::runtime_error {
public:
    SocketException(const std::string& msg) : std::runtime_error(msg) {}
};

std::string ErrorMessage(const std::string& msg);

int send(SOCKET socketfd, const std::string& buf, int flags);
int recv(SOCKET socketfd, std::string& buf, int flags);

sockaddr_in createIPv4Addr(const std::string& ip_addr, int port);
std::string getIPv4Addr(const sockaddr_in& sockaddr);
