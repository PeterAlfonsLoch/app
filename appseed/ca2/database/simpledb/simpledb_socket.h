#pragma once


namespace simpledb
{


   class manager;
   class session;
   class socket_thread;

   class socket : 
      public ::sockets::httpd_socket
   {
   public:


      string            m_strLocale;
      session *         m_psession;
      socket_thread *   m_pthreadParent;

      socket(::sockets::socket_handler_base & h);
      virtual ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void OnSSLAccept();

      void send_response();

      class manager & manager();

      virtual void simple_file_server(const char * psz, const char * pszRelative = ::null());
      virtual bool read_file(const char * lpcsz, smart_pointer_array < int_array > * prangea = ::null(), const char * pszContentType = ::null());

      //virtual bool http_filter_response_header(id key, string & strValue);
   };



} // namespace simpledb