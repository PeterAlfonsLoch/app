//#include "framework.h"


namespace file
{



   ostream2::ostream2()
   {
   }

   ostream2::ostream2(writer * pwriter)
   {

      m_spbuffer = pwriter;

   }

   ostream2::~ostream2()
   {
   }





   ostream2 & ostream2::operator << (uchar uch)
   {
      ostream::operator << (uch);
      return *this;
   }

   ostream2 & ostream2::operator << (uint16_t ui)
   {
      ostream::operator << (ui);
      return *this;
   }

   ostream2 & ostream2::operator << (int32_t i)
   {
      ostream::operator << (i);
      return *this;
   }

   ostream2 & ostream2::operator << (uint32_t ui)
   {
      ostream::operator << (ui);
      return *this;
   }

   ostream2 & ostream2::operator << (const RECT & rect)
   {
      ostream::operator << (rect);
      return *this;
   }


   ostream2 & ostream2::operator << (serializable & serializable)
   {
      ostream::operator << (serializable);
      return *this;
   }

   ostream2 & ostream2::operator << (const char * psz)
   {
      write((void *)psz, strlen(psz));
      return *this;
   }

   ostream2 & ostream2::operator << (const string & str)
   {
      operator <<((const char *)str);
      return *this;
   }


} // namespace file



