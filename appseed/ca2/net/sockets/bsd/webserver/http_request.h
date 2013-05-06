#pragma once


namespace http
{

   class form;

   class CLASS_DECL_ca2 request : public transaction
   {
   public:


      
      string      m_strRequestUri;
      string      m_strQueryString;
      string      m_strHttpHost;
      id          m_idHttpMethod;




      request(sp(::ca::application) papp);
      request(const request& src);
      ~request();


      /** Cookies */
      void add_cookie(const char * pszSetCookie);

      /** open file for body data */
      void InitBody( size_t sz );

      /** write body data */
      void write( const char *buf, ::primitive::memory_size sz );

      /** No more writing */
      void CloseBody();

      void ParseBody();

      http::form & form();

      http::memory_file & file() { return m_file; }

      virtual void clear();

   private:
      string m_null;
      http::memory_file m_file;
      http::form m_form;
      

   }; // end of class



   // --------------------------------------------------------------------------------------
   inline http::form & request::form()
   {
      return m_form;
   }


} // namespace http




