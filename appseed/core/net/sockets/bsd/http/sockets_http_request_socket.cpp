#include "framework.h"


namespace sockets
{


   http_request_socket::http_request_socket(base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h)
   {
   }


   http_request_socket::http_request_socket(base_socket_handler & h, const char * pszRequest, const string & url_in) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {

      m_strRequest = pszRequest;

   }


   http_request_socket::http_request_socket(base_socket_handler & h, const char * pszRequest, const string & host, port_t port, const string & url_in) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {

      m_strRequest = pszRequest;

      UNREFERENCED_PARAMETER(host);
      UNREFERENCED_PARAMETER(port);

   }


   http_request_socket::~http_request_socket()
   {
   }


   void http_request_socket::step()
   {
      m_request.attr("http_method") = m_strRequest;
      //outheader(__id(accept)) = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
      //outheader("Accept-Language") = "en-us,en;q=0.5";
      //outheader("Accept-Encoding") = "gzip,deflate";
      //outheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
      outheader(__id(user_agent)) = MyUseragent();

      if (GetUrlPort() != 80 && GetUrlPort() != 443)
         outheader("Host") = GetUrlHost() + ":" + ::str::from(GetUrlPort());
      else
         outheader("Host") = GetUrlHost();
      SendRequest();
   }

} // namespace sockets

