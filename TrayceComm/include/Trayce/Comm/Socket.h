#ifndef TRAYCE_SOCKET_H
#define TRAYCE_SOCKET_H

#include <memory>
#include <string>

namespace Trayce { namespace Comm {

enum class AddressFamily {
    Unknown = 0,
    IPv4,
    IPv6
};

struct IPAddress
{
    AddressFamily family;
    char          address[16];
};

struct IPEndPoint
{
    IPAddress address;
    int port;
};

struct Socket
{
    Socket();
    ~Socket();

    Socket(Socket&& socket) noexcept;
    Socket& operator=(Socket&& socket) noexcept;

    void connect(const IPEndPoint& endpoint);
    void connect(const std::string& address);
    void close();

    bool isConnected();

    IPEndPoint getLocalEndPoint();
    IPEndPoint getRemoteEndPoint();

private:
    struct SocketImpl;
    std::unique_ptr<SocketImpl> internalSocket;
};

}} // Trayce::Comm

#endif //TRAYCE_SOCKET_H
