#pragma once


namespace http
{


   /** Parse/store a http query_string/form-data body.
      \ingroup webserver */
   class CLASS_DECL_BASE form :
      virtual public ::object
   {
   public:
      form(sp(::base::application) papp);
      /**
       * Default constructor (used in POST operations).
       * Input is read from stdin. Number of characters to read
       * can be found in the environment var CONTENT_LENGTH.
      */
      void parse_body(::file::stream_buffer *, const char * pszContentType, size_t content_length);
      /**
       * Another constructor (used in GET operations).
       * Input is read from the environment var QUERY_STRING.
       * @param query_string The httpd server provided QUERY_STRING
       * @param length Query string length.
      */
      void parse_query_string(const string & query_string,size_t length);
      virtual ~form();

      void EnableRaw(bool bRaw = true);

      /** Encode characters '<' '>' '&' as &lt; &gt; &amp; */
      void strcpyval(string &,const char *) const;

      /* get value */
      relation_set & get();
      relation_set & post();
      relation_set & request();

      string & boundary();

      void clear();

      form(const form& ) {}
      form& operator=(const form& ) { return *this; }
   protected:
      relation_set m_setGet;
      relation_set m_setPost;
      relation_set m_setRequest;
      string m_strBoundary;
      bool m_bRaw;
   };


   inline relation_set & form::get()
   {
      return m_setGet;
   }

   inline relation_set & form::post()
   {
      return m_setPost;
   }

   inline relation_set & form::request()
   {
      return m_setRequest;
   }

   inline void form::parse_query_string(const string & buffer, size_t)
   {
      m_setGet._parse_url_query(buffer);
   }


} // namespace http




