#include "StdAfx.h"

namespace ca4
{

   http_get_socket::http_get_socket(::sockets::socket_handler_base& handler,const string & url,const string & to_file) :
      ::ca::ca(handler.get_app()),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_get_socket(handler, url, to_file)
   {
      m_pcookies = NULL;
   }

      
   http_get_socket::http_get_socket(::sockets::socket_handler_base& handler,const string & host,port_t port,const string & url,const string & to_file) :
      ::ca::ca(handler.get_app()),
      ::sockets::socket(handler),
      ::sockets::stream_socket(handler),
      ::sockets::tcp_socket(handler),
      ::sockets::http_get_socket(handler, host, port, url, to_file)
   {
      m_pcookies = NULL;
   }

   void http_get_socket::OnDataArrived(const char *, size_t len)
   {
      UNREFERENCED_PARAMETER(len);
   }

   void http_get_socket::OnHeader(const string & key,const string & value)
   {
      ::sockets::http_get_socket::OnHeader(key, value);
      if(!_stricmp(key, "location"))
      {
         m_strHeaderLocation = value;
      }
      else if(!_stricmp(key, "set-cookie"))
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


} // namespace ca4