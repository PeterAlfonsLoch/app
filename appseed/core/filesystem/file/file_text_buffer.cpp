#include "framework.h"


namespace file
{


   text_buffer::text_buffer()
   {

   }


   text_buffer::~text_buffer()
   {

   }


   void text_buffer::write_string(const char * lpsz)
   {

      UNREFERENCED_PARAMETER(lpsz);

   }


   UINT text_buffer::read_string(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      return 0;
   }


   UINT text_buffer::read_full_string(string & str)
   {
      UINT uiRead;
      UINT uiTotal = 0;
      string strLine;
      while((uiRead = read_string(strLine)) > 0)
      {
         str += strLine;
      }
      return uiTotal;
   }


} // namespace file



