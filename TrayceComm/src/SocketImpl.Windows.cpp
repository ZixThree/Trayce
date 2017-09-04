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
        return returnCode == 0;
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
    return false;
}

IPEndPoint Socket::SocketImpl::getLocalEndPoint() {
    return IPEndPoint();
}

IPEndPoint Socket::SocketImpl::getRemoteEndPoint() {
    return IPEndPoint();
}

}} // Trayce::Comm