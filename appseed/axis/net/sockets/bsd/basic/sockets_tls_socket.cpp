#include "framework.h"
#include <openssl/ssl.h>


namespace sockets
{


   tls_socket::tls_socket(::sockets::base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
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


