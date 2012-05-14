#include "framework.h"

namespace html
{

   style_sheet_array::style_sheet_array()
   {
   }


   style * style_sheet_array::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      style * pstyle = NULL;
      for(index i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind(pszTag, pszClass, pszSubClass, pszName);
         if(pstyle != NULL)
            break;
      }
      return pstyle;
   }

   const style * style_sheet_array::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const
   {

      return const_cast < style_sheet_array * > (this)->rfind(pszTag, pszClass, pszSubClass, pszName);

   }

} // namespace html
