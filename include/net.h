/*
    RB3Enhanced - net.h
    Platform-agnostic networking functionality.
*/

typedef enum _RB3E_SocketTypes
{
    RB3E_TYPE_TCP = 0,
    RB3E_TYPE_UDP = 1
} RB3E_SocketTypes;

int RB3E_CreateSocket(int protocol);
void RB3E_DisposeSocket(int socket);
int RB3E_LastError();
int RB3E_BindPort(int socket, unsigned short port);
int RB3E_SetNonBlocking(int socket, int enable);
int RB3E_SetRecvTimeout(int socket, int timeout_ms);
int RB3E_SetSendTimeout(int socket, int timeout_ms);
int RB3E_SetTimeout(int socket, int timeout_ms);
int RB3E_UDP_SendTo(int socket, unsigned int ipv4, unsigned short port, void *data, int size);
int RB3E_UDP_RecvFrom(int socket, unsigned int *ipv4, unsigned short *port, void *data, int size);
int RB3E_TCP_Connect(int socket, unsigned int ipv4, unsigned short port);
int RB3E_TCP_Send(int socket, void *data, int size);
int RB3E_TCP_Recv(int socket, void *data, int size);
int RB3E_TCP_Listen(int socket);
int RB3E_TCP_Accept(int socket, unsigned int *ipv4, unsigned short *port);
unsigned int RB3E_GetInternalIP();
unsigned int RB3E_GetGatewayIP();

#ifdef RB3E_XBOX
#define AWAIT_SOCKET(...) (RB3E_LastError() == 10035)
#elif RB3E_WII
#define AWAIT_SOCKET(r) (r == -6)
#elif RB3E_PS3
#define AWAIT_SOCKET(...) (RB3E_LastError() == 35)
#endif
