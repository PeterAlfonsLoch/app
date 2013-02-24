#pragma once


namespace ca2
{


   bool CLASS_DECL_ca is_url(const char * pszCandidate, const char ** ppszRequest = NULL);


   class CLASS_DECL_ca url :
      public ::gen::object
   {
   public:
      // Example: http://veriwell.com.br:443/page?id=1
      string get_protocol(const char *); // http
      string get_root(const char *); // veriwell.com.br:443
      string get_server(const char *); // veriwell.com.br
      int32_t get_port(const char *, int32_t iDefault = -1); // 443
      string get_object(const char *); // page?id=1
      string get_script(const char *); // page
      string get_query(const char *); // id=1
      string set_key(const char * pszUrl, const char * pszKey, var var);
      void set_key(string & strUrl, const char * pszUrl, const char * pszKey, var var);
      void set_param(string & strUrl, const char * pszUrl, const char * pszKey, const string & strParam);
      string set(string & strUrl, const char * pszKey, var var);
      var & set(var & varUrl, const char * pszKey, var var);
      gen::property & set(gen::property & propUrl, const char * pszKey, var var);
      string set_script(const char * pszUrl, const char * pszScript);
      string override_if_empty(const char * pszDest, const char * pszSrc, bool bOverrideQuery = false);
      string override_if_set_at_source(const char * pszDest, const char * pszSrc);
      string remove_key(const char * pszUrl, const char * pszKey);
      string remove(string & strUrl, const char * pszKey);
      var & remove(var & varUrl, const char * pszKey);
      gen::property & remove(gen::property & propUrl, const char * pszKey);
      // Example: page?id=1
      string object_get_script(const char *); // page
      string object_get_query(const char *); // id=1

      bool is_url(const char * pszCandidate);

      string object(const char * pszScript, const char * pszQuery);
      string object_set(const char * pszObject, const char * pszKey, var var);

      string path(const char * psz1, const char * psz2);
      string path(const char * psz1, const char * psz2, const char * psz3);
      string name(const char * psz);
      string url_encode(const char * psz);
      string url_decode(const char * psz);
      string url_decode(const char * psz, strsize iLen);

      string query_append(const char * pszUrl, const char * pszQuery);
      string query_remove(const char * pszQuery, stringa & straKey);
      string query_remove(const char * pszQuery, const char * pszKey);
      string query_set(const char * pszQuery, const char * pszKey, var var);
      string query_set_param(const char * pszQuery, const char * pszKey, const string & strParam);

      var get_var(const char * pszQuery, const char * pszKey);
      var query_get_var(const char * pszQuery, const char * pszKey);
      string get_param(const char * pszQuery, const char * pszKey);
      string query_get_param(const char * pszQuery, const char * pszKey);
      string __query_remove(const char * pszQuery, const char * pszAndKeyEqual);
      
      virtual bool locale_is_eu(const char * pszLocale);
      virtual bool locale_is_asia(const char * pszLocale);
      virtual bool locale_is_africa(const char * pszLocale);
      virtual bool locale_is_america(const char * pszLocale);
      virtual bool locale_is_caribe(const char * pszLocale);
      virtual bool locale_is_middle_east(const char * pszLocale);
      virtual bool locale_is_south_america(const char * pszLocale);
      virtual bool locale_is_latin_america(const char * pszLocale);
      virtual bool locale_is_north_america(const char * pszLocale);
      virtual bool locale_is_central_america(const char * pszLocale);
      virtual bool locale_is_oceania(const char * pszLocale);

   };


} // namespace ca2


