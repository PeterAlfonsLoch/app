#include "framework.h"

namespace gen
{

   text_file::text_file()
   {
   }

   text_file::~text_file()
   {
   }

   void text_file::write_string(const char * lpsz)
   {
      UNREFERENCED_PARAMETER(lpsz);
   }

   UINT text_file::read_string(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      return 0;
   }


   UINT text_file::read_full_string(string & str)
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

} // namespace gen