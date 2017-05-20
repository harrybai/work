
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
{
    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char szPort[64] = {0};
    snprintf(szPort, "%u", usPort, 4); 

    int nResult = getaddrinfo(szIP, szPort, hints, res);
    if(nResult != 0)
        return false;

    m_hSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(m_hSocket == INVALID_SOCKET)
        return false;

    if (cszLocalIP!=NULL && strlen(cszLocalIP)>0)
    {
        int32_t option = 1;
        setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR,
                (char *)&option, sizeof(option));

        struct addrinfo local_hints;
        struct addrinfo*local_res=NULL;

        memset(&local_hints,0,sizeof(local_hints));
        local_hints.ai_family=PF_UNSPEC;
        local_hints.ai_socktype=SOCK_STREAM;
        local_hints.ai_protocol=IPPROTO_TCP;
        local_hints.ai_flags=AI_NUMERICHOST;

        nResult=getaddrinfo(cszLocalIP,"0",&local_hints,&local_res);
        if (nResult==0)
        {
            bind(m_hSocket, local_res->ai_addr,local_res->ai_addrlen); 
            freeaddrinfo(local_res);
            local_res=NULL;
        }
    }

    SocketBase::SetNoneBlocking(bNoB);

    int keepAlive    = 1; 
    int keepIdle     = 60;
    int keepInterval = 5;
    int keepCount    = 3; 
    int nEnable      = 1;
    setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, 
            sizeof(keepAlive)); 
    setsockopt(sock, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, 
            sizeof(keepIdle));
    setsockopt(sock, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, 
            sizeof(keepInterval));
    setsockopt(sock, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, 
            sizeof(keepCount));
    setsockopt(m_hSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nEnable, 
            sizeof(nEnable));
}

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

