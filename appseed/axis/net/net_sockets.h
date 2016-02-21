#pragma once





#include "net.h"


#ifdef ANDROID

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/endian.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef in6_addr in_addr6;

#endif

#ifdef LINUX


#include <time.h>


#endif

#ifdef APPLEOS

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#endif


#include "net_net.h"


#include "net_address.h"


#include "net_port_forward.h"


#include "axis/net/sockets/sockets.h"


#include "net/http/http_get_socket.h"


#include "filesystem/fs/fs_ifs_file.h"


#include "filesystem/fs/fs_remote_native_file.h"


CLASS_DECL_AXIS string ip_reverse(string str);















