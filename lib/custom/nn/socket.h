#pragma once

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int nnsocketRecv(int socket, void* out, ulong outLen, int flags);
int nnsocketRecvFrom(int,void *,ulong,int, struct sockaddr *,uint *);
int nnsocketSend(int socket, const void* data, ulong dataLen, int flags);
int nnsocketSendTo(int,void const*,ulong,int, struct sockaddr const*,uint);
int nnsocketAccept(int,struct sockaddr *,uint *);
int nnsocketBind(int,struct sockaddr const*,uint);
u32 nnsocketConnect(); // returns nn::Result
int nnsocketGetPeerName(int,struct sockaddr *,uint *);
int nnsocketGetSockName(int,struct sockaddr *,uint *);
int nnsocketGetSockOpt(int,int,int,void *,uint *);
int nnsocketListen(int,int);
int nnsocketSetSockOpt(int socket, int socketLevel, int option, void const*, u32 len);
int nnsocketSockAtMark(int);
int nnsocketShutdown(int,int);
int nnsocketSocket(bool);
int nnsocketWrite(int domain, int type, int protocol);
int nnsocketRead(int,int,int);
u32 nnsocketClose(); // returns nn::Result
void nnsocketSelect(int,struct fd_set *,fd_set *,fd_set *,struct timeval *);
void nnsocketPoll(struct pollfd *,ulong,int);
void nnsocketFcntl(int,int,...);
void nnsocketInetPton(int,char const*,void *);
const char* nnsocketInetNtop(int af,void const* src,char* dst,uint size);
s32 nnsocketInetAton(const char* addressStr, struct in_addr* addressOut);
char* nnsocketInetNtoa(struct in_addr);
u16 nnsocketInetHtons(u16 val);
u32 nnsocketInetHtonl(uint);
u16 nnsocketInetNtohs(ushort);
u32 nnsocketInetNtohl(uint);
s32 nnsocketGetLastErrno();;
void nnsocketSetLastErrno(int);;
s32 nnsocketRecvMsg(int,struct msghdr *,int);
s32 nnsocketSendMsg(int,struct msghdr const*,int);
s32 nnsocketIoctl(int,uint,void *,ulong);
s32 nnsocketOpen(char const*,int);
u32 nnsocketInitialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);
s32 nnsocketFinalize();
s32 nnsocketGetAddrInfo(char const*,char const*,struct addrinfo const*,struct addrinfo**);
s32 nnsocketGetAddrInfoCancel(char const*,char const*,struct addrinfo const*,struct addrinfo**,int);
s32 nnsocketGetAddrInfoWithoutNsdResolve(char const*,char const*,struct addrinfo const*,struct addrinfo**);;
s32 nnsocketGetAddrInfoWithoutNsdResolveCancel(char const*,char const*,struct addrinfo const*,struct addrinfo**,int);;
s32 nnsocketFreeAddrInfo(struct addrinfo *);
s32 nnsocketGetNameInfo(struct sockaddr const*,uint,char *,uint,char *,uint,int);
s32 nnsocketGetNameInfoCancel(struct sockaddr const*,uint,char *,uint,char *,uint,int,int);
struct hostent* nnsocketGetHostByName(const char* name);
struct hostent* nnsocketGetHostByNameCancel(char const*,int);
struct hostent* nnsocketGetHostByNameWithoutNsdResolve(char const*);;
struct hostent* nnsocketGetHostByNameWithoutNsdResolveCancel(char const*,int);;
struct hostent* nnsocketGetHostByAddr(void const*,uint,int);
struct hostent* nnsocketGetHostByAddrCancel(void const*,uint,int,int);
s32 nnsocketRequestCancelHandle();
s32 nnsocketCancel(int);
s32 nnsocketGetHErrno();
s32 nnsocketHStrError(int);
s32 nnsocketGAIStrError(int);
s32 nnsocketSysctl(int *,ulong,void *,ulong *,void *,ulong);
s32 nnsocketDuplicateSocket(int,ulong);

#ifdef __cplusplus
}
#endif