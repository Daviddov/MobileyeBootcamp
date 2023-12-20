// IPAddressFinder.cpp

#include "IPAddressFinder.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
// Include any Windows-specific headers or functions here if needed
#else
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

IPAddressFinder::IPAddressFinder() {
    // No need for explicit socket library initialization here on Linux/macOS
}

IPAddressFinder::~IPAddressFinder() {
    // No need for explicit socket library cleanup here on Linux/macOS
}

std::string IPAddressFinder::getLocalIPv4Address() {
    char hostName[256];
    if (gethostname(hostName, sizeof(hostName)) != 0) {
        std::cerr << "Error getting hostname" << std::endl;
        return "";
    }

    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(hostName, nullptr, &hints, &result) != 0) {
        std::cerr << "Error getting address info" << std::endl;
        return "";
    }

    for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        if (ptr->ai_family == AF_INET) {
            struct sockaddr_in* sockaddr_ipv4 = reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
            char ipBuffer[INET_ADDRSTRLEN];
            if (inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipBuffer, INET_ADDRSTRLEN) != nullptr) {
                std::cout << "Local IPv4 Address: " << ipBuffer << std::endl;
                freeaddrinfo(result);
                return ipBuffer;
            }
            else {
                std::cerr << "Error converting address to string" << std::endl;
                freeaddrinfo(result);
                return "";
            }
        }
    }

    std::cerr << "No suitable address found" << std::endl;
    freeaddrinfo(result);
    return "";
}
