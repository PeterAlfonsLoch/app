#pragma once

namespace sockets
{


   class CLASS_DECL_ca http_session : 
      virtual public http_get_socket,
      virtual public http_post_socket,
      virtual public http_put_socket,
      virtual public http_request_socket
   {
   public:


      string      m_strProtocol;
      string      m_strHost;
      bool        m_bRequestComplete;


      http_session(socket_handler_base &, const string & protocol, const string & host);
      ~http_session();


      using http_client_socket::request;
      virtual void request(const char * pszMethod, const char * pszRequest);

      virtual void step();

      virtual void OnHeaderComplete();
      virtual void OnDataComplete();

   };




} // namespace sockets
