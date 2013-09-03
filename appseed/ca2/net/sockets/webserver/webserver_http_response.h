#pragma once


namespace http
{


   class CLASS_DECL_ca2 response : public http::transaction
   {
   public:


      //Utility::ncmap<string> m_cookie;
      http::memory_file m_memfileBody;
   


      response(sp(base_application) papp, const string & version = "HTTP/1.0");
      response(const response& src);
      ~response();

      response& operator=(const response& src);



      //void SetCookie(const string & value);
      //string Cookie(const string & name);
      //list<string> CookieNames() const;

      http::memory_file & file() { return m_memfileBody; }

      /** replace memfile with file on disk, opened for read. */
   //   void SetFile( const string & path );

      void clear();

   }; // end of class


} // namespace http




