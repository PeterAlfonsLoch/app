#pragma once

typedef LPVOID HINTERNET;

namespace ca27
{

   class CLASS_DECL_ca2api00200002 http :
      public base_object
   {
   public:

      http();
      virtual ~http();


      virtual void set_proxy_auth(ca2::user * puser, HttpClientSocket * pfile);
      virtual void clean_proxy_auth(ca2::user * puser);


      HttpClientSocket * get(SocketHandler & handler, const char * pszUrl, gen::property_set & post, gen::property_set & headers, ::http::cookies * pcookies = NULL, ca2::user * puser = NULL, const char * pszVersion = "HTTP/1.1");

      bool get(const char * pszUrl, memory & memory, gen::property_set & post, gen::property_set & headers, ::http::cookies * pcookies = NULL,ca2::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
      bool get(const char * pszUrl, string & str, gen::property_set & post, gen::property_set & headers,::http::cookies * pcookies = NULL, ca2::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
      bool download(const char * pszUrl, const char * pszFile, gen::property_set & post, gen::property_set & headers,::http::cookies * pcookies = NULL,  ca2::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
      bool download(const char * pszUrl, const char * pszFile, const char * pszPost, gen::property_set & headers, ::http::cookies * pcookies = NULL, ca2::user * puser = NULL, const char * pszVersion = "HTTP/1.1");
      string get(const char * pszUrl);

      void config_proxy(http_tunnel * psocket);

      string gmdate(time_t t);

   };


} // namespace ca27