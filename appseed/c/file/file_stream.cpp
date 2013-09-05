#include "framework.h"


namespace file
{


   stream::stream()
   {
   }

   stream::stream(reader * preader, writer * pwriter) :
      input_stream(preader),
      output_stream(pwriter)
   {
   }

   stream::stream(buffer * pbuffer) :
      input_stream(pbuffer),
      output_stream(pbuffer)
   {
   }

   stream::stream(const stream & stream) :
      input_stream(stream),
      output_stream(stream)
   {
   }

   stream::~stream()
   {
   }

   stream & stream::operator = (const stream & stream)
   {
      input_stream::operator = (stream);
      output_stream::operator = (stream);
      return *this;
   }

   bool stream::is_stream_null()
   {
      return is_writer_null() && is_reader_null();
   }

   bool stream::is_stream_set()
   {
      return is_writer_set() || is_reader_set();
   }

   void stream::close()
   {
      input_stream::close();
      output_stream::close();
   }


} // namespace file


