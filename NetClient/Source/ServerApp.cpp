#include "ServerApp.hpp"

#include <Metazion/Net/Network.hpp>

#include "Sockets.hpp"

USING_NAMESPACE_MZ_NET

ServerApp* g_serverApp = nullptr;

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::Initialize() {
    ::printf("Client start.\n");

    Network::Startup();

    m_networkService.Initialize(1024, 8);

    ::memset(m_sockets, 0, sizeof(m_sockets));
    m_socketArray.Attach(m_sockets, 1024, 0);

    Host host;
    host.SetFamily(AF_INET);
    host.SetIp("127.0.0.1");
    host.SetPort(20001);

    auto socketCL = new ClientSocketCL();
    socketCL->Reset();
    socketCL->Retain();
    socketCL->m_connecter.SetRemoteHost(host);
    socketCL->m_connecter.SetReconnectInterval(10000);
    socketCL->m_connecter.Connect();
    m_networkService.Attach(socketCL);
}

void ServerApp::Finalize() {
    m_socketArray.Detach();
    m_networkService.Finalize();
    Network::Cleanup();

    ::printf("Client stop.\n");
}

void ServerApp::Tick() {
    const auto size = m_networkService.AcquireSockets([](Socket* socket) {
            return socket->GetType() != SOCKET_TCP_LISTEN;
        }, m_socketArray);

    for (auto i = 0; i < size; ++i) {
        auto socket = m_socketArray[i];
        MZ_ASSERT_TRUE(!NS_MZ::IsNull(socket));
        socket->Dispatch();
    }

    m_networkService.ReleaseSockets(m_socketArray);
}