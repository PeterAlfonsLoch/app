#pragma once


typedef uint32_t ipaddr_t;
typedef uint16_t port_t;
#ifdef WINDOWS
typedef int32_t socklen_t;
#endif


#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets_config.h"
#elif defined(METROWIN)
#include "winrt/sockets_config.h"
#else
#error "Unknown Sockets Type?"
#endif


namespace net
{


   inline int32_t family_len(int32_t family)
   {

      if (family == AF_INET)
         return sizeof(sockaddr_in);
      else if (family == AF_INET6)
         return sizeof(sockaddr_in6);
      else
         return 0;

   }



} // namespace net


//#include "http_file.h"
//#include "http_memory_file.h"


#include "webserver/webserver_http_form.h"
#include "webserver/webserver_http_cookie.h"
#include "webserver/webserver_http_transaction.h"
#include "webserver/webserver_http_request.h"
#include "webserver/webserver_http_response.h"


#include "sockets_logger.h"
#include "sockets_trace_logger.h"


#include "base/net/net_address.h"
#include "base/sockets_base_socket.h"


#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets.h"
#elif defined(METROWIN)
#include "winrt/sockets.h"
#else
#error "Unknown Sockets Type?"
#endif



#include "base/filesystem/file/file_timeout_buffer.h"
#include "base/filesystem/file/file_transfer_buffer.h"
#include "sockets_http_buffer.h"
#include "sockets_http_batch_buffer.h"




#include "net/mail/mail.h"



#include "base/net/net_ip_enum.h"
#include "base/net/net_port_forward.h"


