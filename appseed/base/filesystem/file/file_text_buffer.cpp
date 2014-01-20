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


   bool text_buffer::read_string(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      return false;
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



