#pragma once



CLASS_DECL_BASE int_bool from_string(in6_addr * addr, const char * string);
CLASS_DECL_BASE string to_vsstring(const in6_addr *addr);
CLASS_DECL_BASE int_bool from_string(in_addr * addr, const char * string);
CLASS_DECL_BASE string to_vsstring(const in_addr *addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_BASE string to_vsstring(const sockaddr *addr);
#endif

CLASS_DECL_BASE uint32_t c_inet_addr(const char *src);
CLASS_DECL_BASE int32_t c_inet_pton(int32_t af, const char *src, void *dst);
CLASS_DECL_BASE const char * c_inet_ntop(int32_t af, const void *src, char *dst, int32_t cnt);
CLASS_DECL_BASE string c_inet_ntop(int32_t af, const void *src);



#include "basic/sockets_ssl_client_context.h"
#include "basic/sockets_ssl_client_context_map.h"
#include "basic/sockets_socket.h"
#include "basic/sockets_stream_socket.h"
#include "basic/sockets_sctp_socket.h"
#include "basic/sockets_tcp_socket.h"
#include "basic/sockets_udp_socket.h"

#include "basic/sockets_tls_socket.h"


#include "base/net/sockets/base/sockets_base_socket_handler.h"
#include "basic/sockets_socket_handler.h"
#include "basic/sockets_listen_socket.h"






#include "base/net/sockets/http/sockets_http.h"






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


#include "basic/sockets_sync_socket_handler.h"


#include "base/net/sockets/sockets_link_out_socket.h"
#include "base/net/sockets/sockets_link_in_socket.h"

#include "basic/sockets_net.h"


#include "sockets_sockets.h"




