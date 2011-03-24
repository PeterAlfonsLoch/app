#include "StdAfx.h"

namespace html
{

   style_sheet_array::style_sheet_array()
   {
   }


   style * style_sheet_array::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      style * pstyle = NULL;
      for(int i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = element_at(i);
         pstyle = sheet.rfind(pszTag, pszClass, pszSubClass, pszName);
         if(pstyle != NULL)
            break;
      }
      return pstyle;
   }

} // namespace html