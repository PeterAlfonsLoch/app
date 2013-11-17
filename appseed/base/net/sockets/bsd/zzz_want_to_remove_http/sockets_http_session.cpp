#include "framework.h"


namespace sockets
{


   http_session::http_session(base_socket_handler & h, const string & protocol, const string & host) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h),
      http_get_socket(h),
      http_post_socket(h),
      http_put_socket(h),
      http_request_socket(h)
   {

      m_strProtocol                 = protocol,
      m_strHost                     = host;
      m_host                        = host;

      inattr("http_protocol")       = protocol;


      m_strUrl                      = protocol + "://" + host;

      if(protocol == "http")
         m_port = 80;
      else 
         m_port = 443;

      m_bRequestComplete            = false;

   }

   http_session::~http_session()
   {
   }

   void http_session::request(const char * pszMethod, const char * pszRequest)
   {
      
      m_strMethod                   = pszMethod;
      inattr("request_uri")         = pszRequest;
      inattr("http_protocol")       = m_strProtocol;
      m_strUrl                      = m_strProtocol + "://" + m_strHost + inattr("request_uri");
      inattr("http_version")        = "HTTP/1.1";
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
      if(m_strMethod.CompareNoCase("GET") == 0)
      {
         http_get_socket::step();
      }
      else if(m_strMethod.CompareNoCase("POST") == 0)
      {
         http_post_socket::step();
      }
      else if(m_strMethod.CompareNoCase("PUT") == 0)
      {
         http_put_socket::step();
      }
      else
      {
         http_request_socket::step();
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




