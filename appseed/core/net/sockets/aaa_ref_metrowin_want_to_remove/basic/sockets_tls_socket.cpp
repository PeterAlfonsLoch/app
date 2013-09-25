#include "framework.h"
#ifndef METROWIN
#include <openssl/ssl.h>
#endif

namespace sockets
{


   tls_socket::tls_socket(::sockets::base_socket_handler& h) :
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
#ifdef BSD_STYLE_SOCKETS
      InitializeContext(m_strCat, TLSv1_client_method());
#endif
   }


} // namespace sockets


