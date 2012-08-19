#include "framework.h"


namespace dynamic_source
{


   httpd_socket::httpd_socket(::sockets::socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      ::sockets::httpd_socket(h)
   {
      
      m_iCa2FetchMode      = 0;

      m_pinstanceCurrent   = NULL;

   }

   httpd_socket::httpd_socket(const httpd_socket& s) :
      ::ca::ca(s.get_app()),
      socket(s.m_handler),
      stream_socket(s),
      tcp_socket(s),
      ::sockets::httpd_socket(s)
   {
   }

   httpd_socket::~httpd_socket()
   {
   }


} // namespace dynamic_source