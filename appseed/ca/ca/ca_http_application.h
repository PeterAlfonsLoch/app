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


      class CLASS_DECL_ca application :
         virtual public ca::signalizable
      {
      public:


         application();
         virtual ~application();


         ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, ca::property_set & post, ca::property_set & headers, ca::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);

         
         DECL_GEN_SIGNAL(get);


         bool get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, primitive::memory_base & memory, ca::property_set & post, ca::property_set & headers, ca::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         bool get(const char * pszUrl, string & str, ::fontopus::user * puser = NULL);
         bool get(const char * pszUrl, string & str, ca::property_set & post, ca::property_set & headers, ca::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         
         bool exists(const char * pszUrl, ::fontopus::user * puser = NULL);
         
         bool exists(const char * pszUrl, var * pvarQuery, ::fontopus::user * puser = NULL);

         string get(const char * pszUrl, ::fontopus::user * puser = NULL);


         bool request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = NULL);
         bool request(const char * pszRequest, const char * pszUrl, string & str, ca::property_set & post, ca::property_set & headers, ca::property_set & set, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = NULL, e_status * pestatus = NULL);
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser = NULL);


         using ::ca::signalizable::request;
         string request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser = NULL);

      
         bool download(const char * pszUrl, const char * pszFile, ca::property_set & post, ca::property_set & headers, ca::property_set & set, ::http::cookies * pcookies = NULL,  ::fontopus::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, const char * pszPost, ca::property_set & headers, ::http::cookies * pcookies = NULL, ::fontopus::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser = NULL);


         bool put(const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser = NULL);
         bool put(const char * pszUrl, ca::file * pfile, ::fontopus::user * puser = NULL);

         bool put(string & strResponse, const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser = NULL);
         bool put(string & strResponse, const char * pszUrl, ca::file * pfile, ::fontopus::user * puser = NULL);

      };


   } // namespace htttp


} // namespace ca