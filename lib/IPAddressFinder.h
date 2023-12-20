// IPAddressFinder.h

#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

class IPAddressFinder {
public:
    IPAddressFinder();
    ~IPAddressFinder();
    std::string getLocalIPv4Address();

private:
#ifdef _WIN32
    WSADATA wsaData; // This is only used on Windows
#endif
};
