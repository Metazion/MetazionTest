#include "Sockets.hpp"

void ClientSocketCL::DerivedReset() {
    m_connecter.SetConnectFailedCallback([this]() {
        ::printf("ClientSocket to server Connect Failed\n");
    });

    m_packeter.SetValidPacketCallback([this](int command, const void* data, int length) {
        this->m_packeter.SendData(command, data, length);

        static std::atomic<int> count = 0;
        if (++count % 10 == 0) {
            ::printf("ClientSocket OnValidPacket %p %d\n", data, length);
        }
    });

    m_packeter.SetInvalidPacketCallback([this]() {
        this->Close();
    });
}

void ClientSocketCL::DerivedOnConnected() {
    ::printf("ClientSocket to server Connected\n");
    char buffer[1024] = "abcdefgh12345678";
    m_packeter.SendData(1, buffer, sizeof(buffer));
}

void ClientSocketCL::DerivedOnDisconnected() {
    ::printf("ClientSocket to server Disconnected\n");

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
