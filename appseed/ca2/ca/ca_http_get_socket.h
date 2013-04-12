#pragma once


namespace ca
{


   class CLASS_DECL_ca2 http_get_socket : 
      public ::sockets::http_get_socket
   {
   public:


      string               m_strHeaderLocation;
      ::http::cookies *    m_pcookies;


      http_get_socket(::sockets::socket_handler & handler, const string & url);
      http_get_socket(::sockets::socket_handler & handler, const string & host,port_t port,const string & url);


      virtual void OnDataArrived(const char *, size_t len);
      void OnHeader(const string & key,const string & value, const string & lowvalue);

      virtual string MyUseragent();


   };


} // namespace ca


