#pragma once

#include "../types.h"
#include <sys/select.h>
#include <time/time_timespan.hpp>
#include "nn/result.h"

#define SOMAXCONN 1024

struct pollfd
{
    s32   fd;
    s16   events;
    s16   revents;
};

struct in_addr
{
    u32 s_addr;           // 0
};

struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

struct sockaddr
{
    u8 _0;              // 0
    u8 family;          // 1
    u16 port;           // 2
    struct in_addr address;    // 4
    u8 _8[8];           // 8
};

struct hostent
{
    char*   h_name;
    char**  h_aliases;
    int     h_addrtype;
    int     h_length;
    char**  h_addr_list;
};

struct iovec {
    void* iov_base; /* Starting address */
    size_t iov_len; /* Length in bytes */
};

/* Structure describing messages sent by
   `sendmsg' and received by `recvmsg'.  */
struct msghdr
{
    void *msg_name;		/* Address to send to/receive from.  */
    socklen_t msg_namelen;	/* Length of address data.  */

    struct iovec *msg_iov;	/* Vector of data to send/receive into.  */
    size_t msg_iovlen;		/* Number of elements in the vector.  */

    void *msg_control;		/* Ancillary data (eg BSD filedesc passing). */
    size_t msg_controllen;	/* Ancillary data buffer length.
                              !! The type should be socklen_t but the
                              definition of the kernel is incompatible
                              with this.  */

    int msg_flags;		/* Flags on received message.  */
};

struct mmsghdr {
    struct msghdr msg_hdr;  /* Message header */
    unsigned int  msg_len;  /* Number of received bytes for header */
};

/* Structure used for storage of ancillary data object information.  */
struct cmsghdr
{
    size_t cmsg_len;		/* Length of data in cmsg_data plus length
                        of cmsghdr structure.
                        !! The type should be socklen_t but the
                        definition of the kernel is incompatible
                        with this.  */
    int cmsg_level;		/* Originating protocol.  */
    int cmsg_type;		/* Protocol specific type.  */
};

namespace nn { namespace socket {


        // taken from https://switchbrew.org/wiki/Sockets_services#BsdBufferConfig
        struct PACKED BsdBufferConfig {
            ulong tcp_tx_buf_size = 0x8000; ///< Size of the TCP transfer (send) buffer (initial or fixed).
            ulong tcp_rx_buf_size = 0x10000; ///< Size of the TCP recieve buffer (initial or fixed).
            ulong tcp_tx_buf_max_size = 0x30000; ///< Maximum size of the TCP transfer (send) buffer. If it is 0, the size of the buffer is fixed to its initial value.
            ulong tcp_rx_buf_max_size = 0x30000; ///< Maximum size of the TCP receive buffer. If it is 0, the size of the buffer is fixed to its initial value.
            ulong udp_tx_buf_size = 0x2400; ///< Size of the UDP transfer (send) buffer (typically 0x2400 bytes).
            ulong udp_rx_buf_size = 0xA500; ///< Size of the UDP receive buffer (typically 0xA500 bytes).
            int sb_efficiency = 4; ///< Number of buffers for each socket (standard values range from 1 to 8).
        };

        struct Config {
            int unkInt1 = 2; // 0x0 (value is 2 in SMO sdk, 8 in sv. could be BsdBufferConfig's version)
            bool unkBool1 = false; // 0x4
            bool isUseBsdS = false; // 0x5
            void* pool; // 0x8
            ulong poolSize; // 0x10
            ulong allocPoolSize; // 0x18
            BsdBufferConfig bufferConfig; // 0x20-0x50
            int concurLimit; // 0x54
            int padding;
        };

        static_assert(sizeof(Config) == 0x60, "Config Size");

        s32 Recv(s32 socket, void* out, ulong outLen, s32 flags);
        s32 RecvFrom(int,void *,ulong,int,sockaddr *,uint *);
        s32 Send(s32 socket, const void* data, ulong dataLen, s32 flags);
        s32 SendTo(int,void const*,ulong,int,sockaddr const*,uint);
        s32 Accept(int,sockaddr *,uint *);
        s32 Bind(int,sockaddr const*,uint);
        nn::Result Connect(s32 socket,	const sockaddr* address, u32 addressLen);
        s32 GetPeerName(int,sockaddr *,uint *);
        s32 GetSockName(int,sockaddr *,uint *);
        s32 GetSockOpt(int,int,int,void *,uint *);
        s32 Listen(int,int);
        s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, void const*, u32 len);
        s32 SockAtMark(int);
        s32 Shutdown(int,int);
        s32 ShutdownAllSockets(bool);
        s32 Socket(s32 domain, s32 type, s32 protocol);
        s32 SocketExempt(int,int,int);
        s32 Write(int,void const*,ulong);
        s32 Read(int,void *,ulong);
        Result Close(s32 socket);
        s32 Select(int,fd_set *,fd_set *,fd_set *,struct timeval *);
        s32 Poll(struct pollfd *,ulong,int);
        s32 Fcntl(int,int,...);
        s32 InetPton(int,char const*,void *);
        const char* InetNtop(int af,void const* src,char* dst,uint size);
        s32 InetAton(const char* addressStr, in_addr* addressOut);
        char* InetNtoa(in_addr);
        u16 InetHtons(u16 val);
        u32 InetHtonl(uint);
        u16 InetNtohs(ushort);
        u32 InetNtohl(uint);
        s32 GetLastErrno();
        void SetLastErrno(int);
        s32 RecvMsg(int,struct msghdr *,int);
        s32 RecvMMsg(int,struct mmsghdr *,ulong,int,nn::TimeSpan *);
        s32 SendMsg(int,msghdr const*,int);
        s32 SendMMsg(int,struct mmsghdr const*,ulong,int);
        s32 Ioctl(int,uint,void *,ulong);
        s32 Open(char const*,int);
        Result Initialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);
        Result Initialize(nn::socket::Config const&);
        s32 Finalize();
        s32 GetAddrInfo(char const*,char const*,struct addrinfo const*,addrinfo**);
        s32 GetAddrInfo(char const*,char const*,addrinfo const*,addrinfo**,int);
        s32 GetAddrInfoWithoutNsdResolve(char const*,char const*,addrinfo const*,addrinfo**);
        s32 GetAddrInfoWithoutNsdResolve(char const*,char const*,addrinfo const*,addrinfo**,int);
        s32 FreeAddrInfo(addrinfo *);
        s32 GetNameInfo(sockaddr const*,uint,char *,uint,char *,uint,int);
        s32 GetNameInfo(sockaddr const*,uint,char *,uint,char *,uint,int,int);
        struct hostent* GetHostByName(const char* name);
        hostent* GetHostByName(char const*,int);
        hostent* GetHostByNameWithoutNsdResolve(char const*);
        hostent* GetHostByNameWithoutNsdResolve(char const*,int);
        hostent* GetHostByAddr(void const*,uint,int);
        hostent* GetHostByAddr(void const*,uint,int,int);
        s32 RequestCancelHandle();
        s32 Cancel(int);
        s32 GetHErrno();
        s32 HStrError(int);
        s32 GAIStrError(int);
        s32 Sysctl(int *,ulong,void *,ulong *,void *,ulong);
        s32 DuplicateSocket(int,ulong);
//        s32 GetResourceStatistics(nn::socket::ResourceStatistics *,ulong);

    } }