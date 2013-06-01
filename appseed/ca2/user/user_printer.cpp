#include "framework.h"


namespace user
{

   printer::printer(sp(::ca::application) papp) :
      ca(papp)
   {
   }

   printer::~printer()
   {
      close();
   }

   bool printer::open(const char * pszDeviceName)
   {
      UNREFERENCED_PARAMETER(pszDeviceName);
      return false;
   }

   ::ca::graphics * printer::create_graphics()
   {
      return NULL;
   }

   bool printer::is_opened()
   {
      return false;
   }

   bool printer::close()
   {
      return true;
   }


} // namespace user
