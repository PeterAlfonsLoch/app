#pragma once


#include "http_file.h"
#include "http_memory_file.h"


#if defined(BSD_STYLE_SOCKETS)
#include "bsd/sockets.h"
#elif defined(METROWIN)
#include "metrowin/sockets.h"
#else
#error "Unknown Sockets Type?"
#endif


#include "sockets_http_file.h"
#include "sockets_http_batch_file.h"


#include "sockets_stream_socket.h"


#include "sockets_application.h"