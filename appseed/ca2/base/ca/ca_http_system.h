#pragma once


typedef LPVOID HINTERNET;


namespace fontopus
{


   class user;


} // namespace fontopus


namespace ca
{


   namespace http
   {

      class CLASS_DECL_ca2 system :
         virtual public ::ca::signalizable
      {
      public:


         class CLASS_DECL_ca2 pac :
            virtual public ::ca::object
         {
         public:


            string      m_strUrl;
            string      m_strAutoConfigScript;
            tinyjs      m_js;
            uint32_t       m_dwLastChecked;


            pac(sp(::ca::application) papp);


         };


         class CLASS_DECL_ca2 proxy :
            virtual public ::ca::object
         {
         public:


            string      m_strUrl;
            bool        m_bDirect;
            string      m_strProxy;
            int32_t         m_iPort;
            uint32_t       m_dwLastChecked;


            proxy(sp(::ca::application) papp);


         };

         mutex                                  m_mutexPac;
         string_map < pac *  >    m_mapPac;
         mutex                                  m_mutexProxy;
         string_map < proxy *  >  m_mapProxy;


         system(sp(::ca::application) papp);
         virtual ~system();


         virtual void set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * pfile);
         virtual void clean_proxy_auth(::fontopus::user * puser);


         ::sockets::http_session * open(
                     ::sockets::socket_handler & handler, 
                     const char * pszHost,
                     const char * pszProtocol,
                     ::ca::property_set & set,
                     ::fontopus::user * puser,
                     const char * pszVersion);

         ::sockets::http_session * request(::sockets::socket_handler & handler, ::sockets::http_session * psession, const char * pszRequest, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());

         ::sockets::http_session * get(::sockets::socket_handler & handler, ::sockets::http_session * psession, const char * pszRequest, primitive::memory_base & memory, ::fontopus::user * puser = ::null());




         ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());



         DECL_GEN_SIGNAL(get);


         bool get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool get(const char * pszUrl, primitive::memory_base & memory, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());
         bool get(const char * pszUrl, string & str, ::fontopus::user * puser = ::null());
         bool get(const char * pszUrl, string & str, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());

         bool exists(const char * pszUrl, ::fontopus::user * puser = ::null());

         string get(const char * pszUrl, ::fontopus::user * puser = ::null());

         bool request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser = ::null());


         string request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser = ::null());


         bool download(const char * pszUrl, const char * pszFile, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(),  ::fontopus::user * puser = ::null(), const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, const char * pszPost, ::ca::property_set & headers, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser = ::null());


         bool put(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool put(const char * pszUrl, sp(::ca::file) pfile, ::fontopus::user * puser = ::null());

         bool put(string & strResponse, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool put(string & strResponse, const char * pszUrl, sp(::ca::file) pfile, ::fontopus::user * puser = ::null());


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


} // namespace ca

