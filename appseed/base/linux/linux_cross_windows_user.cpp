#include "framework.h"


int_bool MessageBoxA(oswindow window, const char * psz, const char * pszTitle, uint32_t uiFlags)
{

   string str(pszTitle);

   if(str.has_char())
   {

      str += " : ";

   }

   str += psz;

   if(uiFlags & MB_ICONEXCLAMATION || uiFlags & MB_ICONSTOP)
   {

      fputs(str, stderr);

   }
   else
   {

      fputs(str, stdout);

   }

   return MB_OK;

}

