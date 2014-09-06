#include "base/net/net_sockets.h"


namespace sockets
{


   http_get_socket::http_get_socket(base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h)
   {

      m_bExpectRequest = true;

   }


   http_get_socket::http_get_socket(base_socket_handler& h,const string & url_in) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {
      
      m_bExpectRequest = true;

      m_emethod = http_method_get;

   }


   http_get_socket::http_get_socket(base_socket_handler& h,const string & host,port_t port,const string & url_in) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {
      
      m_bExpectRequest = true;

      m_emethod = http_method_get;

      UNREFERENCED_PARAMETER(host);

      UNREFERENCED_PARAMETER(port);

   }


   http_get_socket::~http_get_socket()
   {
   }


   void http_get_socket::step()
   {



      if (!(bool)inattr("minimal_headers"))
      {
         //inheader("Accept") = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
         //inheader("Accept-Language") = "en-us,en;q=0.5";
         if (m_pfile == NULL) // by the time, inline gzip decompression not yet implemented
         {
            inheader(__id(accept_encoding)) = "gzip,deflate";
         }
         //inheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
         inheader(__id(user_agent)) = MyUseragent();
      }
      inheader("Content-Length") = 0;

/*      if (GetUrlPort() != 80 && GetUrlPort() != 443)
         inheader(__id(host)) = GetUrlHost() + ":" + ::str::from(GetUrlPort());
      else
         inheader(__id(host)) = GetUrlHost();*/

      m_bExpectResponse = true;
      m_bExpectRequest = false;
      SendRequest();
   }

} // namespace sockets

