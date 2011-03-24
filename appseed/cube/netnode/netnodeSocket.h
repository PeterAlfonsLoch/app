#pragma once

class netnodeApp;
class netnodeService;
class netnodeListenSocket;
class netnodeScriptManager;

class netnodeSocket : 
   public ::sockets::httpd_socket
{
public:

   string         m_strLocale;

   netnodeSocket(::sockets::socket_handler_base & h);
   ~netnodeSocket(void);

   virtual void OnExecute();
   virtual void OnResponseComplete();

   virtual void OnSSLAccept();

   void send_response();

   netnodeScriptManager & script_manager();


   netnodeScriptInstance * m_pinstanceCurrent;

   virtual void simple_file_server(const char * psz, const char * pszRelative = NULL);
   virtual bool read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea = NULL);

   virtual bool http_filter_response_header(string & strKey, string & strValue);
};

