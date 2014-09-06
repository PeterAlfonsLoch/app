#pragma once




#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets_config.h"
#elif defined(METROWIN)
#include "winrt/sockets_config.h"
#else
#error "Unknown Sockets Type?"
#endif



//#include "http_file.h"
//#include "http_memory_file.h"


#include "base/net/http/webserver/webserver_http_form.h"
#include "base/net/http/webserver/webserver_http_transaction.h"
#include "base/net/http/webserver/webserver_http_request.h"
#include "base/net/http/webserver/webserver_http_response.h"


#include "sockets_logger.h"
#include "sockets_trace_logger.h"


#include "base/sockets_base_socket.h"


#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets.h"
#elif defined(METROWIN)
#include "winrt/sockets.h"
#else
#error "Unknown Sockets Type?"
#endif



//#include "base/filesystem/file/file_timeout_buffer.h"
//#include "base/filesystem/file/file_transfer_buffer.h"
#include "sockets_http_buffer.h"
#include "sockets_http_batch_buffer.h"




#include "net/mail/mail.h"



#include "base/net/net_ip_enum.h"
#include "base/net/net_port_forward.h"


