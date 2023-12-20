#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class IPAddressFinder {
public:
    IPAddressFinder();

    ~IPAddressFinder();

    std::string getLocalIPv4Address();

private:
    WSADATA wsaData;
};

