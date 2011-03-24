#include "StdAfx.h"

namespace sockets
{

   tls_socket::tls_socket(::sockets::socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h)
   {
   }


   tls_socket::~tls_socket()
   {
   }

   void tls_socket::InitSSLClient()
   {
      InitializeContext(m_strCat, TLSv1_client_method());
   }

} // namespace sockets