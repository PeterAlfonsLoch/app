#include "framework.h"


namespace gen
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
      ::gen::reader(reader),
      ::gen::writer(writer)
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

} // namespace gen


