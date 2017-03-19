#pragma once



namespace netserver
{


   class CLASS_DECL_AURA socket :
      virtual public ::sockets::httpd_socket
   {
   public:


      bool                             m_bSetCookie;

      socket(::sockets::base_socket_handler & h);
      ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void send_response();

      virtual void on_send_response();

      virtual void simple_file_server(const char * pszPath);

      virtual bool http_filter_response_header(id key, stringa & straValue);


   };


} // namespace netserver

