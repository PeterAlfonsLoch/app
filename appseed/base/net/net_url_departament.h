#pragma once




namespace url
{


   bool CLASS_DECL_BASE is_url(const char * pszCandidate, const char ** ppszRequest = NULL);


   class CLASS_DECL_BASE departament :
      virtual public ::aura::departament
   {
   public:


      departament(sp(::aura::application) papp);
      virtual ~departament();


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
      string string_set(string & strUrl, const char * pszKey, var var);
      var & var_set(var & varUrl, const char * pszKey, var var);
      property & property_set(property & propUrl, const char * pszKey, var var);
      string set_script(const char * pszUrl, const char * pszScript);
      string override_if_empty(const char * pszDest, const char * pszSrc, bool bOverrideQuery = false);
      string override_if_set_at_source(const char * pszDest, const char * pszSrc);
      string remove_key(const char * pszUrl, const char * pszKey);
      string string_remove(string & strUrl, const char * pszKey);
      var & var_remove(var & varUrl, const char * pszKey);
      property & property_remove(property & propUrl, const char * pszKey);
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
      bool query_get_param(string & strValue, const string & strUrl, const string & strKey);
      bool query_has_param(const string & strUrl, const string & strKey);
      bool query_param_has_char(const string & strUrl, const string & strKey);

      var get_var(const char * pszQuery, const char * pszKey);
      var query_get_var(const char * pszQuery, const char * pszKey);
      string get_param(const char * pszQuery, const char * pszKey);
      string query_get_param(const string & strQuery, const string & strKey);
      bool query_has_param_replace(string & strQuery, const string & strKey, const string & strValue);
      string __query_remove(const char * pszQuery, const char * pszAndKeyEqual);
      bool get_param(string & strValue, const string & strUrl, const string & strKey);
      bool has_param(const string & strUrl, const string & strKey);
      bool param_has_char(const string & strUrl, const string & strKey);
      bool has_param_replace(string & strUrl, const string & strKey, const string & strValue);

      virtual bool locale_is_eu(id pszLocale);
      virtual bool locale_is_asia(id pszLocale);
      virtual bool locale_is_africa(id pszLocale);
      virtual bool locale_is_america(id pszLocale);
      virtual bool locale_is_caribe(id pszLocale);
      virtual bool locale_is_middle_east(id pszLocale);
      virtual bool locale_is_south_america(id pszLocale);
      virtual bool locale_is_latin_america(id pszLocale);
      virtual bool locale_is_north_america(id pszLocale);
      virtual bool locale_is_central_america(id pszLocale);
      virtual bool locale_is_oceania(id pszLocale);


      virtual string to_punycode(const char * psz);
      virtual string from_punycode(const char * psz);

   };


} // namespace url



