#include "Trayce/Comm/Socket.h"
#include "SocketImpl.h"

namespace Trayce { namespace Comm {

Socket::Socket() = default;
Socket::~Socket() = default;

Socket::Socket(Socket&& socket) noexcept = default;
Socket& Socket::operator=(Socket&& socket) noexcept = default;

void Socket::connect(const IPEndPoint& endpoint) {
    internalSocket->connect(endpoint);
}

void Socket::connect(const std::string& address) {
    internalSocket->connect(address);
}

void Socket::close() {
    internalSocket->close();
}

bool Socket::isConnected() {
    return internalSocket->isConnected();
}

IPEndPoint Socket::getLocalEndPoint() {
    return internalSocket->getLocalEndPoint();
}

IPEndPoint Socket::getRemoteEndPoint() {
    return internalSocket->getRemoteEndPoint();
}

}} // Trayce::Comm