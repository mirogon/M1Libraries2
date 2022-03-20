#pragma once
#include "IPAddress.h"

class SocketAddress{
    public:

    SocketAddress():
    address(IPAddress("0.0.0.0"))
    {
        this->port = 0;
    }

    SocketAddress(const IPAddress& addr, uint16_t port):
        address{addr}
    {
        this->port = port;
    }

    friend bool operator==(const SocketAddress& a, const SocketAddress& b);

    IPAddress IpAddress() const{
        return address;
    }

    uint16_t Port() const{
        return port;
    }

    private:

    IPAddress address;
    uint16_t port;
};

inline bool operator==(const SocketAddress& a, const SocketAddress& b){
    if(a.address == b.address && a.port == b.port){
        return true;
    }
    return false;
}