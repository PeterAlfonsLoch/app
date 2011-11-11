#include "StdAfx.h"

namespace ex1
{

   exception::exception()
   {
   }

   exception::exception(const exception & e) :
   base_exception(e)
   {
   }

   void PASCAL exception::operator delete(void * pbData)
   {
      base_exception::operator delete(pbData);
   }

   void PASCAL exception::operator delete(void * pbData, const char * lpszFileName, int nLine)
   {
      base_exception::operator delete(pbData, lpszFileName, nLine);
   }

} // namespace ex1