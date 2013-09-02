#include "framework.h"


namespace ca2
{


   http_get_socket::http_get_socket(::sockets::socket_handler & handler, const string & url) :
      element(handler.get_app()),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_socket(handler),
      ::sockets::http_tunnel(handler),
      ::sockets::http_client_socket(handler, url),
      ::sockets::http_get_socket(handler, url)
      
   {
      m_pcookies = NULL;
   }

      
   http_get_socket::http_get_socket(::sockets::socket_handler & handler, const string & host, port_t port, const string & url) :
      element(handler.get_app()),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_socket(handler),
      ::sockets::http_tunnel(handler),
      ::sockets::http_client_socket(handler, url),
      ::sockets::http_get_socket(handler, host, port, url)
   {
      m_pcookies = NULL;
   }

   void http_get_socket::OnDataArrived(const char *, size_t len)
   {
      UNREFERENCED_PARAMETER(len);
   }

   void http_get_socket::OnHeader(id key, const string & value)
   {

      ::sockets::http_get_socket::OnHeader(key, value);

      if(key == __id(location))
      {

         m_strHeaderLocation = value;

      }
      else if(key == __id(set_cookie))
      {

         if(m_pcookies != NULL)
         {

            m_pcookies->add(value);

         }

      }

   }

   string http_get_socket::MyUseragent()
   {
	   return "ca2-sockets/10.0.2";
   }


} // namespace ca2



