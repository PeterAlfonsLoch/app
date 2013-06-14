#include "framework.h"


namespace ca2
{


   stream::stream()
   {
   }

   stream::stream(reader * preader, writer * pwriter) :
      reader(preader),
      writer(pwriter)
   {
   }

   stream::stream(const reader & reader, const writer & writer) :
      ::ca2::reader(reader),
      ::ca2::writer(writer)
   {
   }

   stream::stream(const stream & stream) :
      reader(stream),
      writer(stream)
   {
   }

   stream::~stream()
   {
   }

   stream & stream::operator = (const stream & stream)
   {
      reader::operator = (stream);
      writer::operator = (stream);
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
      reader::close();
      writer::close();
   }

} // namespace ca2


