#include "framework.h"


bool ishexdigit(char ch)
{
   if(ch >= '0' && ch <= '9')
      return true;
   if(ch >= 'a' && ch <= 'f')
      return true;
   if(ch >= 'A' && ch <= 'F')
      return true;
   return false;
}


namespace html
{


   style::style()
   {
   }

   style::style(const style & style)
   {
      operator = (style);
   }

   style & style::operator = (const style & style)
   {
      if(this != &style)
      {
         m_strTag       = style.m_strTag;
         m_strName      = style.m_strName;
         m_strSubClass  = style.m_strSubClass;
         m_propertyset  = style.m_propertyset;
      }
      return *this;
   }

   COLORREF style::parse_color(const char * psz)
   {
      string str(psz);
      str.trim();
      if(str.Left(1) == "#" && str.get_length() >= 7 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]) && ishexdigit(str[4])
          && ishexdigit(str[5]) && ishexdigit(str[6]))
      {
         if(str.get_length() >= 9 && ishexdigit(str[7]) && ishexdigit(str[8]) && !ishexdigit(str[9]))
         {
            int a, r, g, b;
            sscanf(str, "#%02x%02x%02x%02x", &a, &r, &g, &b);
            return ARGB(a, r, g, b);
         }
         else if(!ishexdigit(str[7]))
         {
            int r, g, b;
            sscanf(str, "#%02x%02x%02x", &r, &g, &b);
            return ARGB(255, r, g, b);
         }
      }
      else if(gen::str::begins_eat_ci(str, "rgb") || gen::str::begins_eat_ci(str, "argb"))
      {
         str.trim();
         if(gen::str::begins_eat_ci(str, "("))
         {
            str.trim();
            if(gen::str::ends_eat_ci(str, ")"))
            {
               str.trim();
               var a;
               a.stra().explode(",", str);
               int_array & ia = a.inta();
               if(ia.get_count() == 3)
               {
                  return ARGB(255, ia[0], ia[1], ia[2]);
               }
               else if(ia.get_count() == 4)
               {
                  return ARGB(ia[0], ia[1], ia[2], ia[3]);
               }
            }
         }
      }
      return 0;
   }

   bool style::get_color(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, COLORREF & cr) const
   {
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent != NULL && pelemental->m_pparent->get_tag()->get_attr_value("class"))
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      if(m_propertyset.is_new_or_null(pszName))
      {
         const style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
         {
            if(pelemental->m_pparent != NULL && _stricmp(pszName, "background-color"))
            {
               if(pelemental->m_pparent->m_style.get_color(pszName, pszSubClass, pdata, pelemental->m_pparent, cr))
               {
                  return true;
               }
            }
            return false;
         }
         return pstyle->get_color(pszName, pszSubClass, pdata, pelemental, cr);
      }
      cr = parse_color(m_propertyset[pszName]);
      return true;
   }

   bool style::get_text(const char * pszName, const char * pszSubClass, const data * pdata, const elemental * pelemental, string & str) const
   {
      string strTag;
      string strClass;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      
      if(m_propertyset.is_new_or_null(pszName))
      {
         const style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
         {
            if(pelemental->m_pparent != NULL)
            {
               if(pelemental->m_pparent->m_style.get_text(pszName, pszSubClass, pdata, pelemental->m_pparent, str))
               {
                  return true;
               }
            }
            if(strTag == "h1")
            {
               if(_stricmp("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(_stricmp("font-size", pszName) == 0)
               {
                  str = "30";
                  return true;
               }
               else if(_stricmp("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(strTag == "h2")
            {
               if(_stricmp("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(_stricmp("font-size", pszName) == 0)
               {
                  str = "23";
                  return true;
               }
               else if(_stricmp("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(strTag == "h3")
            {
               if(_stricmp("font-family", pszName) == 0)
               {
                  str = "Times New Roman";
                  return true;
               }
               else if(_stricmp("font-size", pszName) == 0)
               {
                  str = "18";
                  return true;
               }
               else if(_stricmp("font-weight", pszName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else
            {
               return false;
            }
         }
         return pstyle->get_text(pszName, pszSubClass, pdata, pelemental, str);
      }
      str = m_propertyset[pszName];
      string strEm = str;
      if(string(pszName).CompareNoCase("font-size") == 0)
      {
         if(gen::str::find_awwci("em", str) > 0)
         {
            if(pelemental->m_pparent != NULL)
            {
               string strParent;
               if(pelemental->m_pparent->m_style.get_text(pszName, pszSubClass, pdata, pelemental->m_pparent, strParent))
               {
                  str = gen::str::from((int)((double) atof(str) * atoi(strParent)));
               }
               else
               {
                  str = gen::str::from((int)((double) atof(str) * 12));
               }
            }
            else
            {
               str = gen::str::from((int)((double) atof(str) * 12));
            }
         }
      }
      return true;
   }

   bool style::get_alpha(const char * pszSubClass, const data * pdata, const elemental * pelemental, double & d) const
   {
      const char* pszName = "alpha";
      string strTag;
      if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
      {
         strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         strTag = pelemental->m_propertyset["PropertyTag"];
      }
      string strClass;
      if(pelemental->m_pparent->get_tag()->get_attr_value("class"))
      {
         strClass = pelemental->m_pparent->get_tag()->get_attr_value("class");
      }
      else
      {
         strClass = pelemental->get_tag()->get_attr_value("class");
      }
      if(m_propertyset.is_new_or_null(pszName))
      {
         const style * pstyle = pdata->m_stylesheeta.rfind(strTag, strClass, pszSubClass, pszName);
         if(pstyle == NULL)
            return false;
         return pstyle->get_alpha(pszSubClass, pdata, pelemental, d);
      }
      d = m_propertyset["alpha"];
      return true;
   }

   const char * style::parse(data * pdata, const char * psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      while(*psz != '\0' && *psz != '}')
      {
         const char * pszStart = psz;
         while(*psz != ':' && *psz != '\0' && *psz != '}')
         {
            psz++;
         }
         if(*psz == '\0' || *psz == '}')
            return psz;
         string strKey(pszStart, psz - pszStart);
         strKey.trim();

         char chQuote = '\0';
         psz++;
         pszStart = psz;
         while((chQuote != '\0' || *psz != ';') && *psz != '\0' && *psz != '}')
         {
            psz++;
            if(chQuote != '\0' && chQuote == *psz && *(psz - 1) != '\\')
            {
               chQuote = '\0';
            }
            else if(*psz == '\"' || *psz == '\'')
            {
               chQuote = *psz;
            }
         }
         string strValue(pszStart, psz - pszStart);
         m_propertyset[strKey] = strValue;
         if(*psz == ';')
         {
            psz++;
         }
      }

      return psz;

   }

   bool style::matches(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName) const
   {
      if(pszTag != NULL && m_strTag.has_char())
         if(m_strTag != pszTag)
            return false;
      if(pszClass != NULL && m_strName.has_char())
         if(m_strName != pszClass)
            return false;
      if(pszSubClass != NULL && m_strSubClass.has_char())
         if(m_strSubClass != pszSubClass)
            return false;
      if(pszName != NULL)
         if(!m_propertyset.has_property(pszName))
            return false;
      return true;
   }

} // namespace html