#pragma once


#include "net_url.h"



#pragma once

typedef uint32_t ipaddr_t;
typedef uint16_t port_t;
#ifdef WINDOWS
typedef int32_t socklen_t;
#endif


//template < > CLASS_DECL_AURA  void to_string(string & str, const port_t & i);


namespace net
{


   CLASS_DECL_AURA int32_t family_len(int32_t family);



} // namespace net



namespace sockets
{

   class sockets;
   class socket_handler;


} // namespace sockets



#include "aura/net/net_url_department.h"
#include "aura/net/net_url_domain.h"






#include "net_email_address.h"
#include "net_email.h"



#include "net_address.h"


#include "net_ip_enum.h"
#include "net_port_forward.h"






#include "aura/net/http/http_ostream.h"




#include "aura/net/http/http_http.h"


#include "sockets/sockets.h"


#include "ftp/ftp.h"




CLASS_DECL_AURA void thread_touch_sockets();
CLASS_DECL_AURA int thread_has_sockets();


#include "netserver/netserver_socket.h"
#include "netserver/netserver_socket_handler.h"
#include "netserver/netserver_socket_thread.h"









