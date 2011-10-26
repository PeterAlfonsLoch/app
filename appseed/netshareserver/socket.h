#pragma once

namespace netshareserver
{

   class application;
   class netshareserver_service;
   class session;

   class netnodeMemoryFile : 
      public gen::memory_file
   {
   public:
      netnodeMemoryFile(::ca::application * papp);

      inline netnodeMemoryFile & operator << (const char * lpcsz)
      {
         write(lpcsz, strlen(lpcsz));
         return *this;
      }
      inline netnodeMemoryFile & operator << (const string & str)
      {
         write((const char *) str, str.get_length());
         return *this;
      }
      inline netnodeMemoryFile & operator << (gen::memory_file & memfile)
      {
         write(memfile.get_data(), (::primitive::memory_size) memfile.get_length());
         return *this;
      }
      inline netnodeMemoryFile & operator << (ex1::file & file)
      {
         int nRead;
         char buf[1024];
         while((nRead = file.read(buf, sizeof(buf))) > 0)
         {
            write(buf, nRead);
         }
         return *this;
      }
   };

   class CLASS_DECL_NETSHARESERVER socket : 
      public ::sockets::httpd_socket
   {
   public:
	   
      
      string                  m_strRead;

	   int                     m_nBytesSent;
	   int                     m_nBytesBufferSize;
      session *               m_psession;
      bool                    m_bDrawCursor;

      DWORD                   m_dwLastITime;
      ::visual::dib_sp        m_dibSnapshot;




	   socket(::sockets::socket_handler_base & h);
	   virtual ~socket(void);

      virtual void OnExecute();
	   virtual void OnResponseComplete();

      void send_response();
      virtual int send_snapshot(string str);

	   void get(const char * lpcsz);

      void image_query(const char * pszQuery);

      void netshareSend();

      virtual void OnConnect();
      virtual void OnSSLConnect();

      void defer_initialize_session();

   };

} // namespace netshareserver