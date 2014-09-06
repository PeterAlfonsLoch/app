#pragma once


namespace fontopus
{
   
   
   class user;

   
} // namespace fontopus

typedef LPVOID HINTERNET;


namespace fontopus
{

   class user;

} // namespace fontopus


namespace sockets
{

   class sockets;

   class CLASS_DECL_BASE http_client_socket:
      virtual public ::object
   {
   public:
   };

   class CLASS_DECL_BASE socket_handler:
      virtual public ::object
   {
   public:
   };

   class CLASS_DECL_BASE http_session:
      virtual public ::object
   {
   public:
   };

   class CLASS_DECL_BASE http_tunnel:
      virtual public ::object
   {
   public:
   };


} // namespace sockets


#include "webserver/webserver_http_cookie.h"

#include "http_status.h"

#include "http_signal.h"

#include "http_listener.h"





