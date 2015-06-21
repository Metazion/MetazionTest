#ifndef _LOGINSERVER_SOCKETS_HPP_
#define _LOGINSERVER_SOCKETS_HPP_

#include <Metazion/Net/AppListenSocket.hpp>
#include <Metazion/Net/AppServerSocket.hpp>
#include <Metazion/Share/Memory/ObjectPool.hpp>

class ServerSocketCL
    : public NS_MZ_NET::AppServerSocket {
public:
    ServerSocketCL() {}

    ~ServerSocketCL() {}

protected:
    void DerivedReset() override final;

    void DerivedOnConnected() override final;

    void DerivedOnDisconnected() override final;
};


class ListenSocketCL
    : public NS_MZ_NET::AppListenSocket {

    typedef NS_MZ_SHARE::ObjectPool<ServerSocketCL
        , NS_MZ_SHARE::StepAllocator<512>> ServerSocketPool_t;

public:
    ListenSocketCL() {}

    ~ListenSocketCL() {}

protected:
    void DerivedReset() override final;

    void DerivedOnWatched() override final;

    void DerivedOnUnwatched() override final;

private:
    ServerSocketPool_t m_socketPool;
};

#endif // _LOGINSERVER_SOCKETS_HPP_
