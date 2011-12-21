#pragma once


namespace dynamic_source
{


   class script_instance;
   class script_manager;


} // namespace dynamic_source


namespace netnode
{


   class application;
   class service;


   class socket : 
      public ::sockets::httpd_socket
   {
   public:


      string                                 m_strLocale;
      dynamic_source::script_instance *      m_pinstanceCurrent;


      socket(::sockets::socket_handler_base & h);
      ~socket(void);

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void OnSSLAccept();

      void send_response();


      dynamic_source::script_manager & script_manager();


      virtual void simple_file_server(const char * pszPath);
      virtual bool read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea = NULL, const char * pszContentType = NULL);

      virtual bool http_filter_response_header(string & strKey, string & strValue);


   };


} // namespace netnode