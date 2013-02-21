#include "framework.h"


namespace ex1
{
   output_stream2::output_stream2()
   {
   }

   output_stream2::output_stream2(writer * pwriter)
   {
      m_spwriter = pwriter;
   }

   output_stream2::~output_stream2()
   {
   }





output_stream2 & output_stream2::operator << (uchar uch)
{
   byte_output_stream::operator << (uch);
   return *this;
}

output_stream2 & output_stream2::operator << (uint16_t ui)
{
   byte_output_stream::operator << (ui);
   return *this;
}

output_stream2 & output_stream2::operator << (int32_t i)
{
   byte_output_stream::operator << (i);
   return *this;
}

output_stream2 & output_stream2::operator << (uint32_t ui)
{
   byte_output_stream::operator << (ui);
   return *this;
}

output_stream2 & output_stream2::operator << (LPCRECT lpcrect)
{
   byte_output_stream::operator << (lpcrect);
   return *this;
}


output_stream2 & output_stream2::operator << (byte_serializable & serializable)
{
   byte_output_stream::operator << (serializable);
   return *this;
}

output_stream2 & output_stream2::operator << (const char * psz)
{
   write((void *) psz, strlen(psz));
   return *this;
}

output_stream2 & output_stream2::operator << (const string & str)
{
   operator <<((const char *) str);
   return *this;
}


}