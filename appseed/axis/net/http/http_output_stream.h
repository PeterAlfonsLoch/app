#pragma once


namespace http
{


   class CLASS_DECL_AXIS output_stream :
      virtual public ::file::plain_text_output_stream
   {
   public:


      //bool read_string(string & str);
      //virtual void to_string(string & str);

      output_stream();
      output_stream(::file::stream_buffer * pbuffer);
      virtual ~output_stream();


      using ::file::plain_text_output_stream::write;
      //virtual void write(const char * lpcsz);
      virtual void write (const string & str);


      using ::file::plain_text_output_stream::operator<<;
      ::file::output_stream & operator << (::file::memory_buffer & memfile);

      ::file::output_stream & operator << (::file::buffer_sp filesp);




   };


} // namespace http





