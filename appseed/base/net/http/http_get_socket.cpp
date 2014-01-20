#include "framework.h"


namespace http
{


   get_socket::get_socket(::sockets::socket_handler & handler, const string & url) :
      element(handler.get_app()),
      ::sockets::base_socket(handler),
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

      
   get_socket::get_socket(::sockets::socket_handler & handler, const string & host, port_t port, const string & url) :
      element(handler.get_app()),
      ::sockets::base_socket(handler),
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

   void get_socket::OnDataArrived(const char *, size_t len)
   {
      UNREFERENCED_PARAMETER(len);
   }

   void get_socket::OnHeader(id key, const string & value)
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

   string get_socket::MyUseragent()
   {
	   return "core-sockets/10.0.2";
   }


} // namespace core



