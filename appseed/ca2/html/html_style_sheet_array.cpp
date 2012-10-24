#include "framework.h"

namespace html
{

   style_sheet_array::style_sheet_array()
   {
   }


   style * style_sheet_array::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      style * pstyle = NULL;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind(pszTag, pszClass, pszSubClass, pszName);
         if(pstyle != NULL)
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f)
   {
      style * pstyle = NULL;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind_border_width(pszTag, pszClass, pszSubClass, pszName, f);
         if(pstyle != NULL)
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr)
   {
      style * pstyle = NULL;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind_border_color(pszTag, pszClass, pszSubClass, pszName, cr);
         if(pstyle != NULL)
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::greater(style * pstyle1, style * pstyle2)
   {
      if(pstyle1 == NULL)
      {
         if(pstyle2 == NULL)
         {
            return NULL;
         }
         else
         {
            return pstyle2;
         }
      }
      else if(pstyle2 == NULL)
      {
         return pstyle1;
      }
      style * pstyle;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         const style_sheet & sheet = this->element_at(i);
         pstyle = sheet.greater(pstyle1, pstyle2);
         if(pstyle != NULL)
            return pstyle;
      }
      return NULL;
   }


   bool style_sheet_array::greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2)
   {
      if(pstyle1 == NULL)
      {
         if(pstyle2 == NULL)
         {
            return false;
         }
         else
         {
            pstyleRet   = pstyle2;
            iRet        = i2;
            varRet      = var2;
            return true;
         }
      }
      else if(pstyle2 == NULL)
      {
         pstyleRet   = pstyle1;
         iRet        = i1;
         varRet      = var1;
         return true;
      }
      else if(pstyle1 == pstyle2)
      {
         if(i1 > i2)
         {
            pstyleRet   = pstyle1;
            iRet        = i1;
            varRet      = var1;
         }
         else
         {
            pstyleRet   = pstyle2;
            iRet        = i2;
            varRet      = var2;
         }
         return true;
      }
      style * pstyle;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         const style_sheet & sheet = this->element_at(i);
         if(sheet.greater(pstyleRet, iRet, varRet, pstyle1, i1, var1, pstyle2, i2, var2))
            return true;
      }
      return false;
   }


} // namespace html
