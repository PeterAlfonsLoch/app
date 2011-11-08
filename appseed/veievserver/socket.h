#pragma once

namespace veievserver
{

   class application;
   class veievserver_service;
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
      inline netnodeMemoryFile & operator << (memory_file & memfile)
      {
         write(memfile.get_data(), (primitive::memory_size::TYPE) memfile.get_length());
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

   class CLASS_DECL_VEIEVSERVER socket : 
      public ::sockets::smtpd_socket
   {
   public:
	   
      
      string               m_strRead;

	   int                  m_nBytesSent;
	   int                  m_nBytesBufferSize;
      session *            m_psession;
      bool                 m_bDrawCursor;

      DWORD                m_dwLastITime;

      string               m_strHello;
      base_array < ::email::address > m_froma;
      base_array < ::email::address > m_toa;
      string               m_strHeaders;
      string               m_strData;
      string               m_strSubject;


	   socket(::sockets::socket_handler_base & h);
	   virtual ~socket(void);

      virtual void OnExecute();
	   virtual void OnResponseComplete();


      virtual var get_new_elemental_id(mysql::database & db);
      virtual var get_elemental_file_path(var varKey);

      void send_response();
      virtual int send_snapshot(string str);

	   void get(const char * lpcsz);


      virtual bool OnHello(const string & str);
      virtual bool OnMailFrom(const ::email::address & addr);
      virtual bool OnRcptTo(const ::email::address & addr);
      virtual void OnHeader(const string & strKey, const string & strValue);
      virtual void OnHeaderComplete();
      virtual void OnData(const string & strData);
      virtual bool OnDataComplete();
      virtual void OnRset();
      virtual void OnAbort(sockets::smtpd_socket::reason_t ereason);
      virtual void OnNotSupported(const string & str1, const string & str2);

      void image_query(const char * pszQuery);

      void netshareSend();

      virtual void OnConnect();
      virtual void OnSSLConnect();

      void defer_initialize_session();

   };

} // namespace veievserver