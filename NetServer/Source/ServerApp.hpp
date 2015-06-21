#ifndef _LOGINSERVER_SERVERAPP_HPP_
#define _LOGINSERVER_SERVERAPP_HPP_

#include <Metazion/Net/NetworkService.hpp>

class ServerApp {
public:
    ServerApp();

    ~ServerApp();

public:
    void Initialize();

    void Finalize();

    void Tick();

private:
    NS_MZ_NET::NetworkService m_networkService;
    NS_MZ_NET::NetworkService::SocketArray_t m_socketArray;
    NS_MZ_NET::Socket* m_sockets[1024];
};

extern ServerApp* g_serverApp;

#endif // _LOGINSERVER_SERVERAPP_HPP_
