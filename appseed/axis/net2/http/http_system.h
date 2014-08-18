#pragma once


typedef LPVOID HINTERNET;


namespace fontopus
{


   class user;


} // namespace fontopus


namespace http
{

   class CLASS_DECL_AXIS system :
      virtual public signalizable
   {
   public:


      class CLASS_DECL_AXIS pac :
         virtual public ::object
      {
      public:


         string      m_strUrl;
         string      m_strAutoConfigScript;
         tinyjs      m_js;
         uint32_t       m_dwLastChecked;


         pac(sp(::axis::application) papp);


      };


      class CLASS_DECL_AXIS proxy :
         virtual public ::object
      {
      public:


         string         m_strUrl;
         bool           m_bDirect;
         string         m_strProxy;
         int32_t        m_iPort;
         uint32_t       m_dwLastChecked;


         proxy(sp(::axis::application) papp);


      };

      mutex                                  m_mutexPac;
      string_map < pac *  >                  m_mapPac;
      mutex                                  m_mutexProxy;
      string_map < proxy *  >                m_mapProxy;

      mutex                                  m_mutexDownload;
      stringa                                m_straDownloading;
      stringa                                m_straExists;


      system(sp(::axis::application) papp);
      virtual ~system();


      virtual void set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * pfile);
      virtual void clean_proxy_auth(::fontopus::user * puser);

      ::sockets::http_session * open(
         const char * pszHost,
         const char * pszProtocol,
         property_set & set,
         ::fontopus::user * puser,
         const char * pszVersion);

      ::sockets::http_session * request(::sockets::http_session * psession, const char * pszUrl, property_set & set);





      ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, property_set & set);



      DECL_GEN_SIGNAL(get);


      bool exists(const char * pszUrl, property_set & set);

      var length(const char * pszUrl, property_set & set);

      bool get(const char * pszUrl, property_set & set);

      bool request(const char * pszMethod, const char * pszUrl, property_set & set);


      bool download(const char * pszUrl, const char * pszFile, property_set & set);


      bool put(const char * pszUrl, primitive::memory_base & memory, property_set & set);
      bool put(const char * pszUrl, ::file::buffer_sp  pfile, property_set & set);

      void defer_auto_initialize_proxy_configuration();
      void auto_config_proxy(int32_t i);
      int32_t auto_config_proxy_count();
      void config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);
      void config_proxy(const char * pszUrl, proxy * pproxy);
      bool try_pac_script(const char * pszScriptUrl, const char * pszUrl, proxy * pproxy);

      string gmdate(time_t t);

      pac * get_pac(const char * pszUrl);
      proxy * get_proxy(const char * pszUrl);


   };


} // namespace http
