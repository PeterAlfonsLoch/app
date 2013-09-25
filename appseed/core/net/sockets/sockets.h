#pragma once


typedef uint32_t ipaddr_t;
typedef uint16_t port_t;
#ifdef WINDOWS
typedef int32_t socklen_t;
#endif


#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets_config.h"
#elif defined(METROWIN)
#include "metrowin/sockets_config.h"
#else
#error "Unknown Sockets Type?"
#endif


//#include "http_file.h"
//#include "http_memory_file.h"


#include "webserver/webserver_http_form.h"
#include "webserver/webserver_http_cookie.h"
#include "webserver/webserver_http_transaction.h"
#include "webserver/webserver_http_request.h"
#include "webserver/webserver_http_response.h"


#include "sockets_logger.h"
#include "sockets_trace_logger.h"


#include "core/net/net_address_base.h"
#include "core/net/net_address.h"
#include "base/sockets_base_socket.h"

#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets.h"
#elif defined(METROWIN)
#include "metrowin/sockets.h"
#else
#error "Unknown Sockets Type?"
#endif


#include "sockets_http_buffer.h"
#include "sockets_http_batch_buffer.h"




#include "net/mail/mail.h"



