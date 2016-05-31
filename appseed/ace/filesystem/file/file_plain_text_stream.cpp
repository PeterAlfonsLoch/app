//#include "framework.h"


namespace file
{


   plain_text_stream::plain_text_stream()
   {
   }

   plain_text_stream::plain_text_stream(stream_buffer * pbuffer) :
      plain_text_ostream(pbuffer),
      plain_text_istream(pbuffer)
   {
   }

   plain_text_stream::plain_text_stream(const stream & stream) :
      plain_text_ostream(stream),
      plain_text_istream(stream)
   {
   }

   plain_text_stream::~plain_text_stream()
   {
   }

   stream & plain_text_stream::operator = (const stream & stream)
   {
      plain_text_istream::operator = (stream);
      plain_text_ostream::operator = (stream);
      return *this;
   }

   bool plain_text_stream::is_stream_null()
   {
      return is_writer_null() && is_reader_null();
   }

   bool plain_text_stream::is_stream_set()
   {
      return is_writer_set() || is_reader_set();
   }

   void plain_text_stream::close()
   {
      plain_text_istream::close();
      plain_text_ostream::close();
   }


   


} // namespace file


