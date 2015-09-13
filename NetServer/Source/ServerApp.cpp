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

    Host hostCl;
    hostCl.SetFamily(AF_INET);
    hostCl.SetIp("0.0.0.0");
    hostCl.SetPort(20001);

    auto listenSocketCL = new ListenSocketCL();
    listenSocketCL->Reset();
    listenSocketCL->Retain();
    listenSocketCL->SetLocalHost(hostCl);
    listenSocketCL->Listen(100);
    m_networkService.Manage(listenSocketCL);
}

void ServerApp::Finalize() {
    m_networkService.Finalize();
    Network::Cleanup();

    ::printf("Server stop.\n");
}

void ServerApp::Tick() {
    m_networkService.Tick();
}