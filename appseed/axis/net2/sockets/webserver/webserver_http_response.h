#pragma once


namespace http
{


   class CLASS_DECL_AXIS response : public http::transaction
   {
   public:


      //Utility::ncmap<string>         m_cookie;
      file::memory_buffer              m_memfileBody;
      ::http::output_stream            m_ostream;
   


      response(sp(::axis::application) papp, const string & version = "HTTP/1.0");
      response(const response& src);
      ~response();

      response& operator=(const response& src);



      //void SetCookie(const string & value);
      //string Cookie(const string & name);
      //list<string> CookieNames() const;

      ::http::output_stream & ostream()   { return m_ostream; }
      ::file::stream_buffer & file()      { return m_memfileBody; }

      /** replace memfile with file on disk, opened for read. */
   //   void SetFile( const string & path );

      void clear();

   }; // end of class


} // namespace http




