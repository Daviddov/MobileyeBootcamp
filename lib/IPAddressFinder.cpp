#include "IPAddressFinder.h"

    IPAddressFinder::IPAddressFinder() {
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    IPAddressFinder::~IPAddressFinder() {
        WSACleanup();
    }

    std::string IPAddressFinder::getLocalIPv4Address() {
        char hostName[256];
        if (gethostname(hostName, sizeof(hostName)) != 0) {
            std::cerr << "gethostname failed." << std::endl;
            return "";
        }

        struct addrinfo* result = nullptr;
        struct addrinfo hints;

        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if (getaddrinfo(hostName, nullptr, &hints, &result) != 0) {
            std::cerr << "getaddrinfo failed." << std::endl;
            return "";
        }

        for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
            if (ptr->ai_family == AF_INET) {
                struct sockaddr_in* sockaddr_ipv4 = reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
                char ipBuffer[INET_ADDRSTRLEN];
                if (inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipBuffer, INET_ADDRSTRLEN) != nullptr) {
                    freeaddrinfo(result);
                    return ipBuffer;
                }
                else {
                    std::cerr << "inet_ntop failed." << std::endl;
                    freeaddrinfo(result);
                    return "";
                }
            }
        }

        freeaddrinfo(result);
        return "";
    }



