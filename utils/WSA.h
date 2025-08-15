#pragma once

#include <winsock2.h>
class WSA {
    WSAData wsaData;
public:
    int wsa_err;
    WSA();
    ~WSA();
};