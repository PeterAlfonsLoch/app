#include "StdAfx.h"

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
      for(int i = m_stylea.get_upper_bound(); i >= 0; i--)
      {
         class style & style = m_stylea.element_at(i);
         if(style.matches(pszTag, pszClass, pszSubClass, pszName))
            return &style;
      }
      return NULL;
   }

} // namespace html
