#pragma once


typedef LPVOID HINTERNET;


namespace fontopus
{


   class user;


} // namespace fontopus


namespace ca4
{


   namespace http
   {

      class CLASS_DECL_ca system :
         virtual public gen::signalizable
      {
      public:


         class CLASS_DECL_ca pac :
            virtual public ::radix::object
         {
         public:


            string      m_strUrl;
            string      m_strAutoConfigScript;
            tinyjs      m_js;
            DWORD       m_dwLastChecked;


            pac(::ca::application * papp);


         };


         class CLASS_DECL_ca proxy :
            virtual public ::radix::object
         {
         public:


            string      m_strUrl;
            bool        m_bDirect;
            string      m_strProxy;
            int32_t         m_iPort;
            DWORD       m_dwLastChecked;


            proxy(::ca::application * papp);


         };

         mutex                                  m_mutexPac;
         ::collection::string_map < pac *  >    m_mapPac;
         mutex                                  m_mutexProxy;
         ::collection::string_map < proxy *  >  m_mapProxy;


         system(::ca::application * papp);
         virtual ~system();


         virtual void set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * pfile);
         virtual void clean_proxy_auth(::fontopus::user * puser);


         ::sockets::http_session * open(
                     ::sockets::socket_handler & handler, 
                     const char * pszHost,
                     const char * pszProtocol,
                     gen::property_set & set,
                     ::fontopus::user * puser,
                     const char * pszVersion);

         ::sockets::http_session * request(::sockets::socket_handler & handler, ::sockets::http_session * psession, const char * pszRequest, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);

         ::sockets::http_session * get(::sockets::socket_handler & handler, ::sockets::http_session * psession, const char * pszRequest, primitive::memory_base & memory, ::fontopus::user * puser = NULL);




         ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);



         DECL_GEN_SIGNAL(get);


         bool get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, primitive::memory_base & memory, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         bool get(const char * pszUrl, string & str, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, string & str, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);

         bool exists(const char * pszUrl, ::fontopus::user * puser = NULL);

         string get(const char * pszUrl, ::fontopus::user * puser = NULL);

         using ::radix::object::request;
         bool request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool request(const char * pszRequest, const char * pszUrl, string & str, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser = NULL);


         string request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser = NULL);


         bool download(const char * pszUrl, const char * pszFile, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL,  ::fontopus::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, const char * pszPost, gen::property_set & headers, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser = NULL);


         bool put(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool put(const char * pszUrl, ex1::file * pfile, ::fontopus::user * puser = NULL);

         bool put(string & strResponse, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool put(string & strResponse, const char * pszUrl, ex1::file * pfile, ::fontopus::user * puser = NULL);


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


} // namespace ca4

