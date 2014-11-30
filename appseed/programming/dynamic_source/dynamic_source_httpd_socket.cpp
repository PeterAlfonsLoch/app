#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


   httpd_socket::httpd_socket(::sockets::base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      http_socket(h),
      ::sockets::httpd_socket(h)
   {
      
      m_iCa2FetchMode      = 0;

   }

   httpd_socket::httpd_socket(const httpd_socket& s) :
      element(s.get_app()),
      base_socket(s),
      socket(s),
      stream_socket(s),
      tcp_socket(s),
      http_base_socket(s),
      http_socket(s),
      ::sockets::httpd_socket(s)
   {
   }

   httpd_socket::~httpd_socket()
   {
   }


   void httpd_socket::Reset()
   {

      ::sockets::httpd_socket::Reset();

      m_iCa2FetchMode      = 0;

   }


} // namespace dynamic_source