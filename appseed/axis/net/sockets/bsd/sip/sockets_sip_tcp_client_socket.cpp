#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"


namespace sockets
{

   sip_tcp_client_socket::sip_tcp_client_socket(axis_socket_handler & h) :
      element(h.get_app()),
      axis_socket(h),
      socket(h),
      tcp_socket(h),
      stream_socket(h),
      sip_axis_client_socket(h)
   {
      DisableInputBuffer();
   }


   void sip_tcp_client_socket::OnRawData(char * buf, size_t len)
   {
      sip_axis_client_socket::OnRawData(buf, len);
   }


   void sip_tcp_client_socket::OnLine(const string & line)
   {
      sip_axis_client_socket::OnLine(line);
   }

} // namespace sockets