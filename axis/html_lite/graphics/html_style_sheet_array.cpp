#include "framework.h"


namespace html
{


   style_sheet_array::style_sheet_array()
   {

   }


   style * style_sheet_array::rfind(e_tag etag, const string & strClass, const string & strSubClass, id idName)
   {

      style * pstyle = NULL;

      index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rfind(etag, strClass, strSubClass, idName);

         if(pstyle != NULL)
            break;

      }

      return pstyle;

   }


   style * style_sheet_array::rfind_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f)
   {

      style * pstyle = NULL;

      index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rfind_border_width(etag, strClass, strSubClass, idName, f);

         if(pstyle != NULL)
            break;

      }

      return pstyle;

   }


   style * style_sheet_array::rfind_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, COLORREF & cr)
   {

      style * pstyle = NULL;

      index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rfind_border_color(etag, strClass, strSubClass, idName, cr);

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
      
         const style_sheet & sheet = *this->element_at(i);

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

      index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         const style_sheet & sheet = *this->element_at(i);

         if(sheet.greater(pstyleRet, iRet, varRet, pstyle1, i1, var1, pstyle2, i2, var2))
            return true;

      }

      return false;

   }


} // namespace html





