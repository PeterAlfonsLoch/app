#include "framework.h"


namespace file
{


   plain_text_stream::plain_text_stream()
   {
   }

   plain_text_stream::plain_text_stream(reader * preader, writer * pwriter) :
      plain_text_input_stream(preader),
      plain_text_output_stream(pwriter)
   {
   }

   plain_text_stream::plain_text_stream(buffer * pbuffer) :
      plain_text_input_stream(pbuffer),
      plain_text_output_stream(pbuffer)
   {
   }

   plain_text_stream::plain_text_stream(const stream & stream) :
      plain_text_input_stream(stream),
      plain_text_output_stream(stream)
   {
   }

   plain_text_stream::~plain_text_stream()
   {
   }

   stream & plain_text_stream::operator = (const stream & stream)
   {
      plain_text_input_stream::operator = (stream);
      plain_text_output_stream::operator = (stream);
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
      plain_text_input_stream::close();
      plain_text_output_stream::close();
   }


} // namespace file


