#include "Sockets.hpp"

#include "ServerApp.hpp"

void ServerSocketCL::DerivedReset() {
    m_packeter.SetValidPacketCallback([this](int command, const void* data, int length) {
        this->m_packeter.SendData(command, data, length);

        static std::atomic<int> count{ 0 };
        if (++count % 10 == 0) {
            ::printf("ClientSocket OnValidPacket %p %d\n", data, length);
        }
    });

    m_packeter.SetInvalidPacketCallback([this]() {
        this->Close();
    });
}

void ServerSocketCL::DerivedOnConnected() {
    ::printf("ServerSocket from Client Connected\n");
}

void ServerSocketCL::DerivedOnDisconnected() {
    ::printf("ServerSocket from Client Disconnected\n");

    Release();

#if defined(MZ_ENABLE_STATISTIC)
    ::printf("STATISTIC Connect Time:       %lld\n", m_connectedTime);
    ::printf("STATISTIC Disconnect Time:    %lld\n", m_disconnectedTime);
    ::printf("STATISTIC First Send Time:    %lld\n", m_firstSendTime);
    ::printf("STATISTIC Last Send Time:     %lld\n", m_lastSendTime);
    ::printf("STATISTIC Send Byts:          %lld\n", m_sendedBytes);
    ::printf("STATISTIC First Recv Time:    %lld\n", m_firstRecvTime);
    ::printf("STATISTIC Last Recv Time:     %lld\n", m_lastRecvTime);
    ::printf("STATISTIC Recv Bytes:         %lld\n", m_recvedBytes);

    ::printf("STATISTIC Send Speed(KB/s):   %lld\n", m_sendedBytes / (m_lastSendTime - m_firstSendTime));
    ::printf("STATISTIC Recv Speed(KB/s):   %lld\n", m_recvedBytes / (m_lastRecvTime - m_firstRecvTime));
#endif
}


void ListenSocketCL::DerivedReset() {
    m_accepter.SetCreateSocketCallback([this]() {
        auto serverSocket = m_socketPool.Obtain();
        serverSocket->Reset();
        serverSocket->Retain();
        serverSocket->SetDestroyCallback([&](Socket* socket) {
            auto dstSocket = static_cast<ServerSocketCL*>(socket);
            m_socketPool.Return(dstSocket);
        });
        return serverSocket;
    });
}

void ListenSocketCL::DerivedOnWatched() {
    ::printf("ListenSocket for Client Watched\n");
}

void ListenSocketCL::DerivedOnUnwatched() {
    ::printf("ListenSocket for Client Unwatched\n");

    Release();
}
