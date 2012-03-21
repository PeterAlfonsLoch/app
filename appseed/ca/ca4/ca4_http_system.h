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

            
            pac(::ca::application * papp);

            

            string      m_strUrl;
            string      m_strAutoConfigScript;
            tinyjs      m_js;
            DWORD       m_dwLastChecked;

         };

         mutex                                  m_mutexPac;
         ::collection::string_map < pac *  >    m_mapPac;


         system();
         virtual ~system();


         virtual void set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * pfile);
         virtual void clean_proxy_auth(::fontopus::user * puser);


         ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);

      
         DECL_GEN_SIGNAL(get);

         bool get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, primitive::memory_base & memory, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         bool get(const char * pszUrl, string & str, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, string & str, gen::property_set & post, gen::property_set & headers, gen::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         


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
         void auto_config_proxy(int i);
         int auto_config_proxy_count();
         void config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);
         bool try_pac_script(const char * pszScriptUrl, const char * pszUrl, ::sockets::http_tunnel * psocket);

         string gmdate(time_t t);

         pac * get_pac(const char * pszUrl);

      };


   } // namespace http


} // namespace ca4

