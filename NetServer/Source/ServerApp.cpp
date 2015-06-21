#include "ServerApp.hpp"

#include <Metazion/Net/Network.hpp>

#include "Sockets.hpp"

USING_NAMESPACE_MZ_NET

ServerApp* g_serverApp = nullptr;

ServerApp::ServerApp() {}

ServerApp::~ServerApp() {}

void ServerApp::Initialize() {
    ::printf("Server start.\n");

    Network::Startup();

    m_networkService.Initialize(1024, 2);

    ::memset(m_sockets, 0, sizeof(m_sockets));
    m_socketArray.Attach(m_sockets, 1024, 0);
    
    Host hostCl;
    hostCl.SetFamily(AF_INET);
    hostCl.SetIp("0.0.0.0");
    hostCl.SetPort(20001);

    auto listenSocketCL = new ListenSocketCL();
    listenSocketCL->Reset();
    listenSocketCL->Retain();
    listenSocketCL->SetLocalHost(hostCl);
    listenSocketCL->Listen(100);
    m_networkService.Attach(listenSocketCL);
}

void ServerApp::Finalize() {
    m_socketArray.Detach();
    m_networkService.Finalize();
    Network::Cleanup();

    ::printf("Server stop.\n");
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