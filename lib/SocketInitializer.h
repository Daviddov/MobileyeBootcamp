// SocketInitializer.h

#pragma once

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

struct SocketInitializer {
    SocketInitializer();
    ~SocketInitializer();
};
