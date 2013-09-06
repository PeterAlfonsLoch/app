#include "framework.h"


namespace file
{


   byte_stream::byte_stream()
   {
   }

   byte_stream::byte_stream(reader * preader, writer * pwriter) :
      input_stream(preader),
      output_stream(pwriter)
   {
   }

   byte_stream::byte_stream(stream_buffer * pbuffer) :
      input_stream(pbuffer),
      output_stream(pbuffer)
   {
   }

   byte_stream::byte_stream(const stream & stream) :
      input_stream(stream),
      output_stream(stream)
   {
   }

   byte_stream::~byte_stream()
   {
   }

   stream & byte_stream::operator = (const stream & stream)
   {
      input_stream::operator = (stream);
      output_stream::operator = (stream);
      return *this;
   }

   bool byte_stream::is_stream_null()
   {
      return is_writer_null() && is_reader_null();
   }

   bool byte_stream::is_stream_set()
   {
      return is_writer_set() || is_reader_set();
   }

   void byte_stream::close()
   {
      input_stream::close();
      output_stream::close();
   }


} // namespace file


