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
         virtual public ::ca::signalizable
      {
      public:


         application();
         virtual ~application();


         ::sockets::http_client_socket * get(::sockets::socket_handler & handler, const char * pszUrl, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());

         
         DECL_GEN_SIGNAL(get);


         bool get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool get(const char * pszUrl, primitive::memory_base & memory, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());
         bool get(const char * pszUrl, string & str, ::fontopus::user * puser = ::null());
         bool get(const char * pszUrl, string & str, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());
         
         bool exists(const char * pszUrl, ::fontopus::user * puser = ::null());
         
         bool exists(const char * pszUrl, var * pvarQuery, ::fontopus::user * puser = ::null());

         string get(const char * pszUrl, ::fontopus::user * puser = ::null());


         bool request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser = ::null());
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = ::null(), e_status * pestatus = ::null());
         bool request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser = ::null());


         using ::ca::signalizable::request;
         string request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser = ::null());

      
         bool download(const char * pszUrl, const char * pszFile, ::ca::property_set & post, ::ca::property_set & headers, ::ca::property_set & set, ::http::cookies * pcookies = ::null(),  ::fontopus::user * puser = ::null(), const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, const char * pszPost, ::ca::property_set & headers, ::http::cookies * pcookies = ::null(), ::fontopus::user * puser = ::null(), const char * pszVersion = "HTTP/1.1");
         bool download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser = ::null());


         bool put(const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser = ::null());
         bool put(const char * pszUrl, ::ca::file * pfile, ::fontopus::user * puser = ::null());

         bool put(string & strResponse, const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser = ::null());
         bool put(string & strResponse, const char * pszUrl, ::ca::file * pfile, ::fontopus::user * puser = ::null());

      };


   } // namespace htttp


} // namespace ca