#pragma once




//#include "config.h"

#ifndef _RUN_DP
/* First undefine symbols if already defined. */
#undef ENABLE_IPV6
#undef USE_SCTP
#undef NO_GETADDRINFO
#undef ENABLE_POOL
#undef ENABLE_SOCKS4
#undef ENABLE_RESOLVER
#undef ENABLE_RECONNECT
#undef ENABLE_DETACH
#undef ENABLE_TRIGGERS
#undef ENABLE_EXCEPTIONS
#endif // _RUN_DP




/* Ipv6 support. */
#define ENABLE_IPV6


/* SCTP support. */
//#define USE_SCTP


/* Define NO_GETADDRINFO if your operating system does not support
the "getaddrinfo" and "getnameinfo" function calls. */
//#define NO_GETADDRINFO


/* Connection pool support. */
#define ENABLE_POOL


/* Socks4 client support. */
//#define ENABLE_SOCKS4


/* Asynchronous resolver. */
#define ENABLE_RESOLVER


/* Enable TCP reconnect on lost connection.
socket::OnReconnect
socket::OnDisconnect
*/
#define ENABLE_RECONNECT


/* Enable socket thread detach functionality. */
#define ENABLE_DETACH


/* Enable socket to socket triggers. Not yet in use. */
//#define ENABLE_TRIGGERS


/* Enabled exceptions. */
#define ENABLE_EXCEPTIONS


/* Resolver uses the detach function so either enable both or disable both. */
#ifndef ENABLE_DETACH
#undef ENABLE_RESOLVER
#endif





// common defines affecting library and applications using library

/* Define SOCKETS_DYNAMIC_TEMP to use dynamically allocated buffers
in read operations - helps on ECOS */
#define SOCKETS_DYNAMIC_TEMP

//#include <openssl/ssl.h>
#include "internal/SSLInitializer.h"

/*
// platform specific stuff
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

// int64_t
#ifdef _WIN32
#else
#ifdef SOLARIS
#else
# include <stdint.h>
#endif
#endif

*/

#ifndef _WIN32

// all typedefs in this file will be declared outside the sockets namespace,
// because some System's will already have one or more of the type defined.
typedef int32_t SOCKET;
#define Errno errno
#define StrError strerror

#ifdef sockets
namespace sockets {
#endif


   // WIN32 adapt
#define closesocket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#ifndef INADDR_NONE
#define INADDR_NONE ((unsigned long) -1)
#endif // INADDR_NONE

#ifdef sockets
}
#endif

#endif // !_WIN32


// ----------------------------------------
// Generic
#ifndef SOL_IP
#define SOL_IP IPPROTO_IP
#endif


// ----------------------------------------
// App specific adaptions

#ifdef SOLARIS
// ----------------------------------------
// Solaris
typedef uint16_t port_t;
#ifdef sockets
namespace sockets {
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 _S6_un._S6_u8
#define MESSAGE_NOSIGNAL 0

#elif defined __FreeBSD__
// ----------------------------------------
// FreeBSD
# if __FreeBSD_version >= 400014
#  define s6_addr16 __u6_addr.__u6_addr16
#  if !defined(MESSAGE_NOSIGNAL)
#   define MESSAGE_NOSIGNAL 0
#  endif
typedef   in_addr_t ipaddr_t;
typedef   in_port_t port_t;
#ifdef sockets
namespace sockets {
#endif
   // no defs

#ifdef sockets
}
#endif

#  define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#  define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
# else
#  error FreeBSD versions prior to 400014 does not support ipv6
# endif

#elif defined MACOS
// ----------------------------------------
// Mac App X
#ifdef __DARWIN_UNIX03
typedef uint16_t port_t;
#else
#include <mach/port.h>
#endif // __DARWIN_UNIX03
#ifdef sockets
namespace sockets {
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 __u6_addr.__u6_addr16
#define MESSAGE_NOSIGNAL 0 // oops - thanks Derek
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

#elif defined(METROWIN)

CLASS_DECL_ca2 const char *StrError(int32_t x);
#define Errno GetLastError()

#elif defined(WINDOWSEX)

// ----------------------------------------
// Win32
#ifdef _MSC_VER
#pragma comment(lib, "wsock32.lib")
#endif
#define strcasecmp _stricmp



#define MSG_NOSIGNAL 0
//#define SHUT_RDWR 2
#define SHUT_WR 1

#define Errno WSAGetLastError()
CLASS_DECL_ca2 const char *StrError(int32_t x);

namespace sockets
{

   // class WSAInitializer is a part of the socket class (on win32)
   // as a static instance - so whenever an application uses a socket,
   // winsock is initialized
   class WSAInitializer // Winsock Initializer
   {
   public:
      WSAInitializer() {
         if (WSAStartup(0x101,&m_wsadata))
         {
            exit(-1);
         }
      }
      ~WSAInitializer() {
         WSACleanup();
      }
   private:
      WSADATA m_wsadata;
   };

} // namespace sockets


#else


// ----------------------------------------
// LINUX
typedef uint32_t ipaddr_t;
typedef uint16_t port_t;

namespace sockets
{
   // no defs

} // namespace sockets

#endif


namespace sockets
{
   /** List type containing file descriptors. */
   class CLASS_DECL_ca2 socket_id_list :
      public ::comparable_list<SOCKET>
   {
   };

} // namespace sockets


// getaddrinfo / getnameinfo replacements
#ifdef NO_GETADDRINFO
#ifndef AI_NUMERICHOST
#define AI_NUMERICHOST 1
#endif
#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif
#endif

#include "basic/ipv4_address.h"
#include "basic/ipv6_address.h"
#include "basic/address.h"
#include "basic/sockets_ssl_client_context.h"
#include "basic/sockets_ssl_client_context_map.h"
#include "basic/socket.h"
#include "basic/stream_socket.h"
#include "basic/sctp_socket.h"
#include "basic/tcp_socket.h"
#include "basic/udp_socket.h"

#include "basic/tls_socket.h"


#include "log/StdLog.h"

#include "basic/socket_handler_base.h"
#include "basic/socket_handler.h"
#include "basic/listen_socket.h"






#include "http/http_socket.h"


#include "http/http_tunnel.h"
#include "http/http_client_socket.h"
#include "http/http_request_socket.h"
#include "http/http_get_socket.h"
#include "http/http_post_socket.h"
#include "http/http_put_socket.h"
#include "http/http_debug_socket.h"
#include "http/http_session.h"


#include "webserver/AjpBaseSocket.h"
#include "webserver/Ajp13Socket.h"
#include "webserver/ajp13.h"
#include "webserver/http_base_socket.h"
#include "webserver/httpd_socket.h"

#include "sip/sip_base.h"

#include "sip/sip_transaction.h"
#include "sip/sip_request.h"
#include "sip/sip_response.h"

#include "sip/sip_base_client_socket.h"
#include "sip/sip_tcp_client_socket.h"
#include "sip/sip_udp_client_socket.h"
#include "sip/sip_client.h"
#include "sip/sip_server.h"

#include "smtp/smtp_socket.h"
#include "smtp/smtpd_socket.h"

#include "timer/EventTime.h"
#include "timer/Event.h"

#include "timer/IEventHandler.h"
#include "timer/IEventOwner.h"
#include "timer/EventHandler.h"

#include "asynch_dns/resolv_socket.h"
#include "asynch_dns/resolv_server.h"


#include "log/StdLog.h"
#include "log/trace_log.h"

#include "basic/sync_socket_handler.h"


#include "sockets_link_out_socket.h"
#include "sockets_link_in_socket.h"

#include "basic/net.h"


#include "sockets_sockets.h"




