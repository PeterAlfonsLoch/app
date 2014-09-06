#pragma once




namespace http
{


   class CLASS_DECL_BASE application :
      virtual public signalizable
   {
   public:


      application();
      virtual ~application();


      sp(::sockets::http_client_socket) get(sp(::sockets::socket_handler) sphandler, const char * pszUrl, property_set & set);


      DECL_GEN_SIGNAL(get);

      property_set & process_set(property_set & set, const char * pszUrl);


      bool get(const char * pszUrl, primitive::memory_base & memory, property_set & set);
      bool get(const char * pszUrl, string & str, property_set & set);

      bool exists(const char * pszUrl, property_set & set);
      bool exists(const char * pszUrl, var * pvarQuery, property_set & set);

      var length(const char * pszUrl, property_set & set);
      var length(const char * pszUrl, var * pvarQuery, property_set & set);

      string get(const char * pszUrl, property_set & set);

      //bool request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, property_set & set);
      //bool request(const char * pszRequest, const char * pszUrl, string & str, property_set & set);

      bool request(const char * pszRequest, const char * pszUrl, property_set & set);

      bool download(const char * pszUrl, const char * pszFile, property_set & set);


      bool put(const char * pszUrl, primitive::memory & memory, property_set & set);
      bool put(const char * pszUrl, ::file::buffer_sp  pfile, property_set & set);

      virtual string locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      virtual string get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

   };


} // namespace htttp
