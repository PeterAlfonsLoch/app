#pragma once


namespace sockets
{


   class CLASS_DECL_ca2 sip_tcp_client_socket :
      virtual public tcp_socket,
      virtual public sip_base_client_socket
   {
   public:


      sip_tcp_client_socket(socket_handler_base& );


      void OnRawData(char *, size_t);
      void OnLine(const string & line);


   };


} // namespace sockets


