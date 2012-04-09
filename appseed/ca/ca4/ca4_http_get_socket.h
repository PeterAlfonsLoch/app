#pragma once

namespace ca4
{

   class CLASS_DECL_ca http_get_socket : 
      public ::sockets::http_get_socket
   {
   public:

      http_get_socket(::sockets::socket_handler_base& handler,const string & url);
      http_get_socket(::sockets::socket_handler_base& handler,const string & host,port_t port,const string & url);

      string m_strHeaderLocation;

      ::http::cookies * m_pcookies;
   
      virtual void OnDataArrived(const char *, size_t len);
      void OnHeader(const string & key,const string & value, const string & lowvalue);

      virtual string MyUseragent();
   };


} // namespace ca4