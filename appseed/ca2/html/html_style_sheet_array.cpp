#include "framework.h"

namespace html
{

   style_sheet_array::style_sheet_array()
   {
   }


   style * style_sheet_array::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      style * pstyle = ::null();
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind(pszTag, pszClass, pszSubClass, pszName);
         if(pstyle != ::null())
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f)
   {
      style * pstyle = ::null();
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind_border_width(pszTag, pszClass, pszSubClass, pszName, f);
         if(pstyle != ::null())
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr)
   {
      style * pstyle = ::null();
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         style_sheet & sheet = this->element_at(i);
         pstyle = sheet.rfind_border_color(pszTag, pszClass, pszSubClass, pszName, cr);
         if(pstyle != ::null())
            break;
      }
      return pstyle;
   }


   style * style_sheet_array::greater(style * pstyle1, style * pstyle2)
   {
      if(pstyle1 == ::null())
      {
         if(pstyle2 == ::null())
         {
            return ::null();
         }
         else
         {
            return pstyle2;
         }
      }
      else if(pstyle2 == ::null())
      {
         return pstyle1;
      }
      style * pstyle;
      index i;
      for(i = get_upper_bound(); i >= 0; i--)
      {
         const style_sheet & sheet = this->element_at(i);
         pstyle = sheet.greater(pstyle1, pstyle2);
         if(pstyle != ::null())
            return pstyle;
      }
      return ::null();
   }


   bool style_sheet_array::greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2)
   {
      if(pstyle1 == ::null())
      {
         if(pstyle2 == ::null())
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
      else if(pstyle2 == ::null())
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
//      style * pstyle;
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
