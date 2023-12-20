// SocketInitializer.cpp

#include "SocketInitializer.h"

SocketInitializer::SocketInitializer() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

SocketInitializer::~SocketInitializer() {
#ifdef _WIN32
    WSACleanup();
#endif
}
