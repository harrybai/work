#include "SocketBase.h"

CSoketBase::CSoketBase()
    :m_hSocket(INVALID_SOCKET)
{
}

CSoketBase::~CSoketBase()
{
}

void CSoketBase::Attach(SOCKET hSocket)
{
   m_hSocket = hSocket;
}

void CSoketBase::Detach()
{
    m_hSocket = INVALID_SOCKET;
}

void CSoketBase::Close()
{
    if(m_hSocket != INVALID_SOCKET)
    {
        closesocket(m_hSocket);
        m_hSocket = INVALID_SOCKET;
    }
}

bool CSoketBase::SetNoBlock(bool bNoB)
{
    unsigned int flag = bNoB?O_NONBLOCK:0;
    if(fcntl(m_hSocket, F_SETFL, flag) == -1)
    {
        return false;
    }
    return true;
}

bool CSoketBase::SetTos(SOCKET hSocket, unsigned char nTos)
{
    if(hSocket ==  INVALID_SOCKET)
        return false;
    int nTmp = nTos;
    int err = setsockopt(hSocket, SOL_IP, 
            IP_TOS, (char *)&nTmp, sizeof(nTmp));
    return (err == 0);
}

char CSoketBase::m_szLocalHostName[256] = "";
const char *CSoketBase::GetLocalHostName()
{
    gethostname(m_szLocalHostName, sizeof(m_szLocalHostName));
    return m_szLocalHostName;
}

char CSoketBase::m_szLocalIP[256] = "";
void CSoketBase::SetLocalIP(const char *szLocalIP)
{
    strcpy(m_szLocalIP, szLocalIP);
}
const char *CSoketBase::GetLocalIP()
{
    return m_szLocalIP;
}

