#ifndef _CLIENT_SOCKETS_HPP_
#define _CLIENT_SOCKETS_HPP_

#include <Metazion/Net/AppClientSocket.hpp>

class ClientSocketCL
    : public NS_MZ_NET::AppClientSocket {
public:
    ClientSocketCL() {}

    ~ClientSocketCL() {}

protected:
    void DerivedReset() override;

    void DerivedOnConnected() override final;

    void DerivedOnDisconnected() override final;
};

#endif // _CLIENT_SOCKETS_HPP_
