#pragma once

namespace sockets
{

   class CLASS_DECL_ca tls_socket : 
      virtual public tcp_socket
   {
   public:


      tls_socket(socket_handler_base& );
      ~tls_socket();


      virtual void InitSSLClient();

   };



} // namespace sockets