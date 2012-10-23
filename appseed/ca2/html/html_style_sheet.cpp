#include "framework.h"

namespace html
{

   style_sheet::style_sheet()
   {
   }


   void style_sheet::parse(data * pdata, const char * psz)
   {
      while(*psz != '\0')
      {
         const char * pszStart = psz;
         while(*psz != '{' && *psz != '\0')
         {
            psz++;
         }
         if(*psz == '\0')
            return;
         const char * pszRestart = psz + 1;
         string str(pszStart, psz - pszStart);
         str.trim();
         if(str.get_length() <= 0)
            return;

         pszStart = str;
         psz = pszStart;
         while(*psz != '.' && *psz != '\0')
         {
            psz++;
         }
         class style style;
         style.m_strTag = str.Left(psz - pszStart);
         if(*psz == '.')
         {
            str = str.Mid(psz - pszStart + 1);
         }
         else
         {
            str.Empty();
         }
         str.trim();
         if(str.get_length() > 0)
         {
            pszStart = str;
            psz = pszStart;
            while(*psz != ':' && *psz != '\0')
            {
               psz++;
            }
            style.m_strName = str.Left(psz - pszStart);
            if(*psz == ':')
            {
               str = str.Mid(psz - pszStart + 1);
            }
            else
            {
               str.Empty();
            }
            style.m_strSubClass = str;
         }
         psz = style.parse(pdata, pszRestart);
         if(*psz == '}')
            psz++;
         m_stylea.add(style);
      }
   }

   style * style_sheet::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName)
   {
      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         class style & style = m_stylea.element_at(i);
         if(style.matches(pszTag, pszClass, pszSubClass, pszName))
            return &style;
      }
      return NULL;
   }

   const style * style_sheet::rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const
   {
      return ((style_sheet *) this)->rfind(pszTag, pszClass, pszSubClass, pszName);
   }

   style * style_sheet::rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f)
   {
      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         class style & style = m_stylea.element_at(i);
         if(style.matches_border_width(pszTag, pszClass, pszSubClass, pszName, f))
            return &style;
      }
      return NULL;
   }

   const style * style_sheet::rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f) const
   {
      return ((style_sheet *) this)->rfind_border_width(pszTag, pszClass, pszSubClass, pszName, f);
   }

   style * style_sheet::rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr)
   {
      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         class style & style = m_stylea.element_at(i);
         if(style.matches_border_color(pszTag, pszClass, pszSubClass, pszName, cr))
            return &style;
      }
      return NULL;
   }

   const style * style_sheet::rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr) const
   {
      return ((style_sheet *) this)->rfind_border_color(pszTag, pszClass, pszSubClass, pszName, cr);
   }

   style * style_sheet::greater(style * pstyle1, style * pstyle2) const
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
      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         const class style & style = m_stylea.element_at(i);
         if(&style == pstyle1)
            return pstyle1;
         else if(&style == pstyle2)
            return pstyle2;
      }
      return NULL;
   }

   const style * style_sheet::greater(const style * pstyle1, const style * pstyle2) const
   {
      return greater((style *) pstyle1, (style *) pstyle2);
   }


   bool style_sheet::greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2) const
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
      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         const class style & style = m_stylea.element_at(i);
         if(&style == pstyle1)
            return pstyle1;
         else if(&style == pstyle2)
            return pstyle2;
      }
      return NULL;
   }

   bool style_sheet::greater(const style * & pstyleRet, index & iRet, var & varRet, const style * pstyle1, index i1, const var & var1, const style * pstyle2, index i2, const var & var2) const
   {
      return greater((style * &) pstyleRet, iRet, varRet, (style *) pstyle1, i1, var1, (style *) pstyle2, i2, var2);
   }


} // namespace html
