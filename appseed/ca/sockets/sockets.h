#pragma once


#include "config.h"


// common defines affecting library and applications using library

/* Define SOCKETS_DYNAMIC_TEMP to use dynamically allocated buffers
   in read operations - helps on ECOS */
#define SOCKETS_DYNAMIC_TEMP

//#include <openssl/ssl.h>
#include "SSLInitializer.h"

/*
// platform specific stuff
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

// int64
#ifdef _WIN32
#else
#include <stdlib.h>
#ifdef SOLARIS
# include <sys/types.h>
#else
# include <stdint.h>
#endif
#endif

*/

#ifndef _WIN32
// ----------------------------------------
// common unix includes / defines
#include <unistd.h>
#include <sys/time.h>
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

#elif defined _WIN32
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
CLASS_DECL_ca const char *StrError(int x);

namespace sockets {


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
namespace sockets {
// no defs

}


#endif

namespace sockets
{
   /** List type containing file descriptors. */
   class CLASS_DECL_ca socket_id_list :
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

#include "ca/ca_log.h"
#include "exception.h"
#include "ipv4_address.h"
#include "ipv6_address.h"
#include "sockets_ssl_client_context.h"
#include "sockets_ssl_client_context_map.h"
#include "socket.h"
#include "stream_socket.h"
#include "sctp_socket.h"
#include "tcp_socket.h"
#include "udp_socket.h"

#include "tls_socket.h"

#include "http_file.h"
#include "http_memory_file.h"
#include "http_form.h"
#include "http_cookie.h"
#include "http_transaction.h"
#include "http_request.h"
#include "http_response.h"
#include "AjpBaseSocket.h"
#include "Ajp13Socket.h"
#include "ajp13.h"
#include "http_socket.h"
#include "StdLog.h"
#include "socket_handler_base.h"
#include "http_base_socket.h"
#include "httpd_socket.h"
#include "listen_socket.h"
#include "http_tunnel.h"
#include "http_client_socket.h"
#include "http_request_socket.h"
#include "http_get_socket.h"
#include "http_post_socket.h"
#include "http_put_socket.h"
#include "http_debug_socket.h"
#include "socket_handler.h"

#include "sip_base.h"

#include "sip_transaction.h"
#include "sip_request.h"
#include "sip_response.h"

#include "sip_base_client_socket.h"
#include "sip_tcp_client_socket.h"
#include "sip_udp_client_socket.h"
#include "sip_client.h"
#include "sip_server.h"

#include "smtp_socket.h"
#include "smtpd_socket.h"

#include "EventTime.h"
#include "Event.h"

#include "IEventHandler.h"
#include "IEventOwner.h"
#include "EventHandler.h"

#include "resolv_socket.h"
#include "resolv_server.h"

#include "sockets_http_file.h"
#include "sockets_http_batch_file.h"

#include "StdLog.h"
#include "trace_log.h"

#include "sync_socket_handler.h"




#include "application_interface.h"

