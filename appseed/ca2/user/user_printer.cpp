#include "StdAfx.h"
#include <WinSpool.h>

namespace user
{

   printer::printer(::ax::application * papp) :
      ax(papp)
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

   ::ax::graphics * printer::create_graphics()
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