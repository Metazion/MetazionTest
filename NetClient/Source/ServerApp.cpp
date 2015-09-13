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
    m_networkService.Manage(socketCL);
}

void ServerApp::Finalize() {
    m_networkService.Finalize();
    Network::Cleanup();

    ::printf("Client stop.\n");
}

void ServerApp::Tick() {
    m_networkService.Tick();
}