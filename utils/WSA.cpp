#include "WSA.h"

WSA::WSA() {
    wsa_err = WSAStartup(MAKEWORD(2,2), &wsaData);
}

WSA::~WSA() {
    WSACleanup();
}