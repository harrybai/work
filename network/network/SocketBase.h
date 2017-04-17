#ifndef __SOCKETBASE_H__
#define __SOCKETBASE_H__

#ifndef SOCKET
#define SOCKET int
#endif

#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SOCKET_ERROR   (-1)
#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif
#define closesocket(s) close(s)

class CSoketBase
{
public:
    CSoketBase(void);
    virtual ~CSoketBase(void);
public:
    virtual void Attach(SOCKET hSocket);
    virtual void Detach(void);
    virtual void Close(void);
    virtual bool SetNoBlock(bool bNoB);
    virtual bool SetTos(SOCKET hSocket, unsigned char nTos);

    static const char *GetLocalHostName(void);
    static const char *GetLocalIP(void);
    static       void  SetLocalIP(const char *szLocalIP);
private:
    SOCKET m_hSocket;

    static char m_szLocalHostName[256];
    static char m_szLocalIP[256];
};

#endif //__SOCKETBASE_H__
