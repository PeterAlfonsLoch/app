#include "framework.h"


namespace ex1
{


   exception::exception(::ca::application * papp) :
      ca(papp),
      ::call_stack(papp),
      ::base_exception(papp)
   {

   }


   exception::exception(const exception & e) :
      ca(e.get_app()),
      ::call_stack(e.get_app()),
      ::base_exception(e)
   {

   }

   void PASCAL exception::operator delete(void * pbData)
   {
      base_exception::operator delete(pbData);
   }

   void PASCAL exception::operator delete(void * pbData, const char * lpszFileName, int32_t nLine)
   {
      base_exception::operator delete(pbData, lpszFileName, nLine);
   }


} // namespace ex1



