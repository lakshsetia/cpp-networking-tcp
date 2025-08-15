#include "Socket.h"

std::string ErrorMessage(const std::string& msg) {
    int errorCode = WSAGetLastError();
    return msg + " failed. Error Code: " + std::to_string(errorCode);
} 

Socket::Socket(int family, int type, int protocol) {
    fd = socket(family, type, protocol);
    if (fd == INVALID_SOCKET) {
        throw SocketException(ErrorMessage("socket creation"));
    }
}
Socket::~Socket() {
    if (fd != INVALID_SOCKET) {
        closesocket(fd);
    }
}

void Socket::bind(const sockaddr_in* addr) {
    if (::bind(fd, (sockaddr*)addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("socket binding"));
    }
}
void Socket::bind(const sockaddr_in6* addr) {
    if (::bind(fd, (sockaddr*)addr, sizeof(sockaddr_in6)) == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("socket binding"));
    }
}
void Socket::connect(const sockaddr_in* addr) {
    if (::connect(fd, (sockaddr*)addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("socket connection"));
    }
}
void Socket::connect(const sockaddr_in6* addr) {
    if (::connect(fd, (sockaddr*)addr, sizeof(sockaddr_in6)) == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("socket connection"));
    }
}
void Socket::listen(int backlog) {
    if (::listen(fd, backlog) == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("socket listening"));
    }
}
SOCKET Socket::accept(const sockaddr_in* addr) {
    int size = sizeof(sockaddr_in);
    SOCKET clientSocket = ::accept(fd, (sockaddr*)addr, &size);
    if (clientSocket == INVALID_SOCKET) {
        throw SocketException(ErrorMessage("accepting socket"));
    }
    return clientSocket;
}
SOCKET Socket::accept(const sockaddr_in6* addr) {
    int size = sizeof(sockaddr_in6);
    SOCKET clientSocket = ::accept(fd, (sockaddr*)addr, &size);
    if (clientSocket == INVALID_SOCKET) {
        throw SocketException(ErrorMessage("accepting socket"));
    }
    return clientSocket;
}
int send(SOCKET socketfd, const std::string& buf, int flags) {
    int len = buf.size();
    int bytesSent = ::send(socketfd, buf.c_str(), len, flags);
    if (bytesSent == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("sending to socket"));
    }
    return bytesSent;
}
int recv(SOCKET socketfd, std::string& buf, int flags) {
    char temp[1024];
    int bytesRecv = ::recv(socketfd, temp, 1024, flags);
    if (bytesRecv == SOCKET_ERROR) {
        throw SocketException(ErrorMessage("receiving from socket"));
    }
    temp[bytesRecv] = 0;
    buf = temp;
    return bytesRecv;
}

sockaddr_in createIPv4Addr(const std::string& ip_addr, int port) {
    sockaddr_in ip{};
    ip.sin_family = AF_INET;
    ip.sin_port = htons(port);
    if (ip_addr == "") {
        ip.sin_addr.S_un.S_addr = INADDR_ANY;
    }
    else {
        inet_pton(AF_INET, ip_addr.c_str(), &ip.sin_addr);
    }
    return ip;
}

std::string getIPv4Addr(const sockaddr_in& addr) {
    char ip_addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ip_addr, INET_ADDRSTRLEN);
    return ip_addr;
}