#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS sip_tcp_client_socket :
      virtual public tcp_socket,
      virtual public sip_axis_client_socket
   {
   public:


      sip_tcp_client_socket(axis_socket_handler& );


      void OnRawData(char *, size_t);
      void OnLine(const string & line);


   };


} // namespace sockets


