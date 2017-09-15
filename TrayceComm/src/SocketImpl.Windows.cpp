#include "SocketImpl.h"

#include "Trayce/LogService.h"
#include "InternalData.h"

#include <atomic>
#include <inaddr.h>

using namespace Trayce::Log;

namespace Trayce { namespace Comm {

namespace {
    struct Winsock2Initialization{
        Winsock2Initialization() {
            increaseUsage();
        }

        ~Winsock2Initialization() {
            decreaseUsage();
        }

        void ensureInitialized() {
            if(inUseCounter == 0) {
                fprintf(stderr, "Unable to initialize Winsock2.");
            }
        }

        static void increaseUsage()
        {
            if(inUseCounter++ == 0)
            {
                WORD versionRequested = MAKEWORD(2, 2);
                WSADATA data;
                int err = WSAStartup(versionRequested, &data);
                if(err != 0) {
                    fprintf(stderr, "WSAStartup failed with error: 0x%x.\n", err);
                }
            }
        }

        static void decreaseUsage()
        {
            if(--inUseCounter == 0)
            {
                WSACleanup();
            }
        }

        static std::atomic_uint32_t inUseCounter;
    };

    static Winsock2Initialization GWinsock2Initialization;

}

Socket::SocketImpl::SocketImpl() {
    GWinsock2Initialization.ensureInitialized();
    Winsock2Initialization::increaseUsage();
}

Socket::SocketImpl::~SocketImpl() {
    Winsock2Initialization::decreaseUsage();
}

bool Socket::SocketImpl::connect(const std::string& address) {
    return false;
}

bool Socket::SocketImpl::connect(const IPEndPoint &endpoint) {
    internalSocket = ::socket(endpoint.address.family == AddressFamily::IPv4 ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if(internalSocket == INVALID_SOCKET) {
        LogService::get().log(LogLevel::Critical, GTrayceCommCategoryId, "Unable to create a new socket (error code=%i).", WSAGetLastError());
        return false;
    }

    if(endpoint.address.family == AddressFamily::IPv4) {
        struct sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_addr.S_un.S_addr = htonl(*reinterpret_cast<const int*>(endpoint.address.address));
        addr.sin_port = htons(endpoint.port);
        int returnCode = ::connect(internalSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(sockaddr_in));
        if(returnCode != 0)
        {
            LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Unable to connect (error code=%i).", WSAGetLastError());

            closesocket(internalSocket);
            internalSocket = INVALID_SOCKET;
        }
        return (returnCode == 0);
    }

    return false;
}

void Socket::SocketImpl::close() {
    if(internalSocket != INVALID_SOCKET) {
        closesocket(internalSocket);
        internalSocket = INVALID_SOCKET;
    }
}

bool Socket::SocketImpl::isConnected() {
    return internalSocket != INVALID_SOCKET;
}

IPEndPoint Socket::SocketImpl::getLocalEndPoint() {
    if (!isConnected()) {
        LogService::get().log(LogLevel::Warning, GTrayceCommCategoryId, "Unable to get local endpoint: not connected.");
        return IPEndPoint();
    }

    int addr_length;
    struct sockaddr_storage addr;
    if (getsockname(internalSocket, (struct sockaddr*)&addr, &addr_length) != SOCKET_ERROR) {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Unable to get local endpoint: error code %i.", WSAGetLastError());
        return IPEndPoint();
    }

    IPEndPoint endPoint;
    if(addr.ss_family == AF_INET) {
        struct sockaddr_in *ipv4_addr = (struct sockaddr_in*)&addr;
        endPoint.address.family = AddressFamily::IPv4;
        *((int*)&endPoint.address.address) = ipv4_addr->sin_addr.S_un.S_addr;
        endPoint.port = ntohs(ipv4_addr->sin_port);
    } else if(addr.ss_family == AF_INET6) {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Not implemented, IPv6");
//        struct sockaddr_in6 *ipv6_addr = (struct sockaddr_in6 *) &addr;
//        memcpy(endPoint.address.address, ipv6_addr->sin6_addr, sizeof(char) * 8);
//        endPoint.port = ntohs(ipv6_addr->sin_port);
        return IPEndPoint();
    } else {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Unknown family address in local endpoint.");
        return IPEndPoint();
    }
    return endPoint;
}

IPEndPoint Socket::SocketImpl::getRemoteEndPoint() {
    if (!isConnected()) {
        LogService::get().log(LogLevel::Warning, GTrayceCommCategoryId, "Unable to get remote endpoint: not connected.");
        return IPEndPoint();
    }

    int addr_length;
    struct sockaddr_storage addr;
    if (getpeername(internalSocket, (struct sockaddr*)&addr, &addr_length) != SOCKET_ERROR) {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Unable to get remote endpoint: error code %i.", WSAGetLastError());
        return IPEndPoint();
    }

    IPEndPoint endPoint;
    if(addr.ss_family == AF_INET) {
        struct sockaddr_in *ipv4_addr = (struct sockaddr_in*)&addr;
        endPoint.address.family = AddressFamily::IPv4;
        *((int*)&endPoint.address.address) = ipv4_addr->sin_addr.S_un.S_addr;
        endPoint.port = ntohs(ipv4_addr->sin_port);
    } else if(addr.ss_family == AF_INET6) {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Not implemented, IPv6");
//        struct sockaddr_in6 *ipv6_addr = (struct sockaddr_in6 *) &addr;
//        memcpy(endPoint.address.address, ipv6_addr->sin6_addr, sizeof(char) * 8);
//        endPoint.port = ntohs(ipv6_addr->sin_port);
        return IPEndPoint();
    } else {
        LogService::get().log(LogLevel::Error, GTrayceCommCategoryId, "Unknown family address in remote endpoint.");
        return IPEndPoint();
    }
    return endPoint;
}

}} // Trayce::Comm