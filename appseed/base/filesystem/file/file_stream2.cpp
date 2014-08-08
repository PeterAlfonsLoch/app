#include "framework.h"


namespace file
{



   output_stream2::output_stream2()
   {
   }

   output_stream2::output_stream2(writer * pwriter)
   {

      m_spbuffer = pwriter;

   }

   output_stream2::~output_stream2()
   {
   }





   output_stream2 & output_stream2::operator << (uchar uch)
   {
      output_stream::operator << (uch);
      return *this;
   }

   output_stream2 & output_stream2::operator << (uint16_t ui)
   {
      output_stream::operator << (ui);
      return *this;
   }

   output_stream2 & output_stream2::operator << (int32_t i)
   {
      output_stream::operator << (i);
      return *this;
   }

   output_stream2 & output_stream2::operator << (uint32_t ui)
   {
      output_stream::operator << (ui);
      return *this;
   }

   output_stream2 & output_stream2::operator << (const RECT & rect)
   {
      output_stream::operator << (rect);
      return *this;
   }


   output_stream2 & output_stream2::operator << (serializable & serializable)
   {
      output_stream::operator << (serializable);
      return *this;
   }

   output_stream2 & output_stream2::operator << (const char * psz)
   {
      write((void *)psz, strlen(psz));
      return *this;
   }

   output_stream2 & output_stream2::operator << (const string & str)
   {
      operator <<((const char *)str);
      return *this;
   }


} // namespace file



