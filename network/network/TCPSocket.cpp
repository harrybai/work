
// TCPSocket.cpp: implementation of the TCPSocket class.
// //
// //////////////////////////////////////////////////////////////////////

#include "TCPSocket.h"
CTCPSocket::CTCPSocket(void)
    :m_nSockType(AF_INET)
{
    //m_nMTU = NetSetting::GetMTU();
    m_nMTU = 1280;
    m_nReuseAddr = 1;
    m_nSockbufsize = (1 << 19);
}
CTCPSocket::~CTCPSocket(void)
{
}
bool CTCPSocket::Bind(const int &socktype, const struct sockaddr *name, int len)
{
    m_nSockType = socktype;
    m_hSocket = socket(socktype, SOCK_STREAM, IPPROTO_TCP);
    if(m_hSocket == INVALID_SOCKET)
    {
        return false;
    }
    setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR,
            (char *)&m_nReuseAddr, sizeof(m_nReuseAddr));
    int err = 0;
    err = setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF,
            (char *)&m_nSockbufsize, sizeof(m_nSockbufsize) );
    err = setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF,
            (char *)&m_nSockbufsize, sizeof(m_nSockbufsize) );
    if (bind(m_hSocket, name, len) == -1)
    {
        return false;
    }
    if (listen(m_hSocket, 200) == -1)
    {
        return false;
    }
    return true;
}
bool Connect(const char *szIP, unsigned short usPort, 
            const char *szLocalIP, std::string &strPeerIP, 
            bool bNoB=false);
    int Receive(char *pBuffer, int nLen);
    int Send(const char *pData, int nLen);
    SOCKET Accept(std::string &strLocalIP, std::string &strPeerIP);
    int GetConnectedLocalIP(std::string &strLocalIP);
    unsigned short GetLocalIP(void);
    void Close(void);
protected:
    int m_nSockType;
    int m_nMTU;
};

#endif //__TCPSOCKET_H__

