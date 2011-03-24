#include "StdAfx.h"

namespace html
{

COLORREF style::parse_color(const char * psz)
{
   string str(psz);
   str.Trim();
   if(str.Left(1) == "#")
   {
      int r, g, b;
      sscanf(str, "#%02x%02x%02x", &r, &g, &b);
      return RGB(r, g, b);
   }
   return 0;
}

bool style::get_background_color(COLORREF & cr)
{
   if(m_propertyset["background-color"] == NULL)
      return false;
   cr = parse_color(m_propertyset["background-color"]->GetValue().GetValueString());
   return true;
}

void style::parse(const char * psz)
{
   while(*psz != '\0')
   {
      const char * pszStart = psz;
      while(*psz != ':' && *psz != '\0')
      {
         psz++;
      }
      if(*psz == '\0')
         return;
      string strKey(pszStart, psz - pszStart);
      strKey.Trim();

      char chQuote = '\0';
      psz++;
      pszStart = psz;
      while((chQuote != '\0' || *psz != ';') && psz != '\0')
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
      m_propertyset.AddProperty(strKey, -1, gen::VariableString);
      m_propertyset[strKey]->GetValue().SetValueString(strValue);
   }

}


} // namespace html