#include "StdAfx.h"


namespace ex1
{
   output_stream2::output_stream2()
   {
      m_pwriter = NULL;
   }

   output_stream2::output_stream2(writer * pwriter)

   {
      m_pwriter = pwriter;
   }

   output_stream2::~output_stream2()
   {
   }





output_stream2 & output_stream2::operator << (unsigned char uch)
{
   output_stream::operator << (uch);
   return *this;
}

output_stream2 & output_stream2::operator << (unsigned short ush)
{
   output_stream::operator << (ush);
   return *this;
}

output_stream2 & output_stream2::operator << (int i)
{
   output_stream::operator << (i);
   return *this;
}

output_stream2 & output_stream2::operator << (unsigned long ul)
{
   output_stream::operator << (ul);
   return *this;
}

output_stream2 & output_stream2::operator << (LPCRECT lpcrect)
{
   output_stream::operator << (lpcrect);
   return *this;
}


output_stream2 & output_stream2::operator << (serializable & serializable)
{
   output_stream::operator << (serializable);
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