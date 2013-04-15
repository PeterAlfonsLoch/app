#pragma once


namespace sip
{

   class CLASS_DECL_ca2 request :
      virtual public transaction
   {
   public:
      request(::ca::application * papp);
      request(const request& src);
      ~request();


      /** Cookies */
      void add_cookie(const char * pszSetCookie);

      /** open file for body data */
      void InitBody( size_t sz );

      /** write body data */
      void write( const char *buf, size_t sz );

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

} // namespace http
