#pragma once

typedef uint32_t ipaddr_t;
typedef uint16_t port_t;
#ifdef WINDOWS
typedef int32_t socklen_t;
#endif


namespace net
{


   CLASS_DECL_AXIS int32_t family_len(int32_t family);



} // namespace net



namespace sockets
{

   class sockets;
   class socket_handler;


} // namespace sockets



#include "axis/net/net_url_department.h"
#include "axis/net/net_url_domain.h"






#include "net_email_address.h"
#include "net_email.h"






#include "net_ip_enum.h"
#include "net_port_forward.h"






#include "axis/net/http/http_ostream.h"




#include "axis/net/http/http_http.h"




