#pragma once


namespace sip
{


   class CLASS_DECL_AXIS response :
      virtual public transaction
   {
   public:


      response(::axis::application * papp, const string & version = "HTTP/1.0");
      response(const response& src);
      ~response();

      response& operator=(const response& src);



      //void SetCookie(const string & value);
      //string Cookie(const string & name);
      //list<string> CookieNames() const;

      file::memory_buffer & file() { return m_memfileBody; }

      /** replace memfile with file on disk, opened for read. */
   //   void SetFile( const string & path );

      void clear();

   protected:

      //Utility::ncmap<string> m_cookie;
      file::memory_buffer m_memfileBody;


   }; // end of class


} // namespace http


