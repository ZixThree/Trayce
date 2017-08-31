#include "SocketImpl.h"

#include <string>

namespace Trayce { namespace Comm {

namespace {
    struct Winsock2Initialization{
        Winsock2Initialization() {
            //WSAStartup();
        }
    };

    static Winsock2Initialization GWinsock2Initialization;

}

Socket::SocketImpl::SocketImpl() {

}

Socket::SocketImpl::~SocketImpl() {

}

void Socket::SocketImpl::connect(const std::string& address) {

}

void Socket::SocketImpl::connect(const IPEndPoint &endpoint) {

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