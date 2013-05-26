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
//#include "internal/SSLInitializer.h"


#ifndef _WIN32
// ----------------------------------------
// common unix includes / defines
#include <unistd.h>
//#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netdb.h>

// all typedefs in this file will be declared outside the sockets namespace,
// because some System's will already have one or more of the type defined.
typedef int SOCKET;
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
typedef unsigned short port_t;
#ifdef sockets
namespace sockets {
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 _S6_un._S6_u8
#define MSG_NOSIGNAL 0

#elif defined __FreeBSD__
// ----------------------------------------
// FreeBSD
# if __FreeBSD_version >= 400014
#  define s6_addr16 __u6_addr.__u6_addr16
#  if !defined(MSG_NOSIGNAL)
#   define MSG_NOSIGNAL 0
#  endif
#  include <netinet/in.h>
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

#elif defined MACOSX
// ----------------------------------------
// Mac App X
//#include <string.h>
#ifdef __DARWIN_UNIX03
typedef unsigned short port_t;
#else
#include <mach/port.h>
#endif // __DARWIN_UNIX03
typedef unsigned long ipaddr_t;
#ifdef sockets
namespace sockets {
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 __u6_addr.__u6_addr16
#define MSG_NOSIGNAL 0 // oops - thanks Derek
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

#elif defined(METROWIN)

CLASS_DECL_ca2 const char *StrError(int x);
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
CLASS_DECL_ca2 const char *StrError(int x);

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
typedef unsigned long ipaddr_t;
typedef unsigned short port_t;

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

#include "base/ca/ca_log.h"

#include "basic/sockets_address.h"
//#include "basic/sockets_ssl_client_context.h"
//#include "basic/sockets_ssl_client_context_map.h"
#include "basic/sockets_socket.h"
#include "basic/sockets_stream_socket.h"
#include "basic/sockets_sctp_socket.h"
#include "basic/sockets_tcp_socket.h"
#include "basic/sockets_udp_socket.h"

#include "basic/sockets_tls_socket.h"


#include "log/sockets_std_log.h"

#include "basic/sockets_socket_handler_base.h"
#include "basic/sockets_socket_handler.h"
#include "basic/sockets_listen_socket.h"






#include "http/http_socket.h"


#include "http/http_tunnel.h"
#include "http/http_client_socket.h"
#include "http/http_request_socket.h"
#include "http/http_get_socket.h"
#include "http/http_post_socket.h"
#include "http/http_put_socket.h"
#include "http/http_debug_socket.h"
#include "http/http_session.h"


#include "webserver/webserver_ajp_base_socket.h"
#include "webserver/webserver_ajp13_socket.h"
#include "webserver/webserver_ajp13.h"
#include "webserver/webserver_http_base_socket.h"
#include "webserver/webserver_httpd_socket.h"

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

#include "timer/sockets_event_time.h"
#include "timer/sockets_event.h"

#include "timer/sockets_ievent_handler.h"
#include "timer/sockets_ievent_owner.h"
#include "timer/sockets_event_handler.h"

#include "asynch_dns/sockets_resolv_socket.h"
#include "asynch_dns/sockets_resolv_server.h"


#include "log/sockets_std_log.h"
#include "log/sockets_trace_log.h"

#include "basic/sockets_sync_socket_handler.h"


#include "sockets_link_out_socket.h"
#include "sockets_link_in_socket.h"

#include "basic/sockets_net.h"

#include "sockets_sockets.h"

