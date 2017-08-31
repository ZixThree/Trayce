#ifndef TRAYCE_SOCKETIMPL_H
#define TRAYCE_SOCKETIMPL_H

#include "Trayce/Comm/Socket.h"

#include <WinSock2.h>

namespace Trayce { namespace Comm {

struct Socket::SocketImpl final
{
    SocketImpl();
    ~SocketImpl();

    void connect(const IPEndPoint& endpoint);
    void connect(const std::string& address);
    void close();

    bool isConnected();

    IPEndPoint getLocalEndPoint();
    IPEndPoint getRemoteEndPoint();

private:
    ::SOCKET internalSocket;
};

}} // Trayce::Comm

#endif //TRAYCE_SOCKETIMPL_H
