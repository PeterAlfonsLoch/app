#pragma once


namespace http
{


   class CLASS_DECL_AURA ostream :
      virtual public ::file::plain_text_ostream
   {
   public:


      //bool read_string(string & str);
      //virtual void to_string(string & str);

      ostream();
      ostream(::file::file * pbuffer);
      virtual ~ostream();


      using ::file::plain_text_ostream::write;
      //virtual void write(const char * lpcsz);
      virtual void write (const string & str);


      using ::file::plain_text_ostream::operator<<;
      ::file::ostream & operator << (::memory_file & memfile);

      ::file::ostream & operator << (::file::file_sp filesp);




   };


} // namespace http





