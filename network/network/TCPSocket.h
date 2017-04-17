// TCPSocket.h: interface for the TCPSocket class.
// //
// //////////////////////////////////////////////////////////////////////
#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include "SocketBase.h"

class CTCPSocket
    : public CSocketBase
{
public:
    CTCPSocket(void);
    virtual ~CTCPSocket(void);
public:
    bool Bind(const int &socktype, const struct sockaddr *name, int len);
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
    int m_nReuseAddr;
    int m_nSockbufsize;
};

#endif //__TCPSOCKET_H__

