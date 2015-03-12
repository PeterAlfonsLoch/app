#pragma once


namespace http
{


   class CLASS_DECL_AXIS ostream :
      virtual public ::file::plain_text_ostream
   {
   public:


      //bool read_string(string & str);
      //virtual void to_string(string & str);

      ostream();
      ostream(::file::stream_buffer * pbuffer);
      virtual ~ostream();


      using ::file::plain_text_ostream::write;
      //virtual void write(const char * lpcsz);
      virtual void write (const string & str);


      using ::file::plain_text_ostream::operator<<;
      ::file::ostream & operator << (::file::memory_buffer & memfile);

      ::file::ostream & operator << (::file::buffer_sp filesp);




   };


} // namespace http





