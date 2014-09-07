#include "framework.h" // from "base/net/net_sockets.h"

#ifdef LINUX

#include <sys/time.h>

#endif

namespace sockets
{


   http_session::http_session(sp(::sockets::base_socket_handler) phandler,const string & protocol,const string & host) :
      element(phandler->get_app()),
      base_socket(*phandler),
      socket(*phandler),
      stream_socket(*phandler),
      tcp_socket(*phandler),
      http_socket(*phandler),
      http_tunnel(*phandler),
      http_client_socket(*phandler),
      http_get_socket(*phandler),
      http_post_socket(*phandler),
      http_put_socket(*phandler)
   {

      m_phandler                    = phandler;

      m_strProtocol                 = protocol,
      m_strHost                     = host;
      m_host                        = host;

      inattr(__id(http_protocol))   = protocol;


      m_request.m_propertysetHeader[__id(host)] = host;


      m_strUrl                      = protocol + "://" + host;

      if(protocol == "http")
         m_port = 80;
      else
         m_port = 443;

      m_strConnectHost              = m_host;
      m_iConnectPort                = m_port;

      m_bRequestComplete            = false;

   }

   http_session::~http_session()
   {

   }


   void http_session::request(const string & strMethod, const string & strRequest)
   {

      request(string_http_method(strMethod), strRequest);

   }


   void http_session::request(e_http_method emethod, const string & strRequest)
   {

      m_emethod                     = emethod;
      inattr(__id(request_uri))     = strRequest;
      inattr(__id(http_protocol))   = m_strProtocol;
      m_strUrl                      = m_strProtocol + "://" + GetUrlHost() + inattr("request_uri");
      inattr(__id(http_version))    = "HTTP/1.1";
      m_b_keepalive                 = true;
      m_content_ptr                 = 0;

      if(m_bRequestComplete)
      {
         step();
      }

      m_bRequestComplete      = false;

   }

   void http_session::step()
   {

      inheader(__id(connection)) = "Keep-Alive";

      inattr(__id(http_method)) = http_method_string(m_emethod);

      switch (m_emethod)
      {
      case http_method_get:

         http_get_socket::step();

         break;

      case http_method_post:

         http_post_socket::step();

         break;

      case http_method_put:

         http_put_socket::step();

         break;

      default:

         http_get_socket::step();

         break;

      }

   }


   void http_session::OnDataComplete()
   {

      m_bRequestComplete = true;

   }


   void http_session::OnHeaderComplete()
   {

      http_client_socket::OnHeaderComplete();

   }


} // namespace sockets





