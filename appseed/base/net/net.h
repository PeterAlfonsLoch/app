#pragma once


typedef uint32_t ipaddr_t;
typedef uint16_t port_t;
#ifdef WINDOWS
typedef int32_t socklen_t;
#endif


namespace net
{


   inline int32_t family_len(int32_t family)
   {

      if(family == AF_INET)
         return sizeof(sockaddr_in);
      else if(family == AF_INET6)
         return sizeof(sockaddr_in6);
      else
         return 0;

   }



} // namespace net



namespace sockets
{

   class sockets;
   class socket_handler;


} // namespace sockets



#include "net_net.h"



#include "net_address.h"



#include "net_email_address.h"
#include "net_email.h"






#include "net_ip_enum.h"






