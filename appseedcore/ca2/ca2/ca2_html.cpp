#include "StdAfx.h"

namespace ca2
{

   string html::special_chars(const char * psz)
   {
      string str(psz);
      str.replace("&"      , "&amp;");
      str.replace("\""     , "&quot;"); // quando ENT_NOQUOTES n縊 est・definida.
      str.replace("'"      , "&#039;"); // apenas quando ENT_QUOTES est・definida.
      str.replace("<"      , "&lt;");
      str.replace(">"      , "&gt;");
      return str;
   }


   string html::entities(const char * psz)
   {
      if(psz == NULL)
         return "";
      string str;
      string strChar;
      while(*psz != '\0')
      {
         int iChar = (int) *psz;
         if(iChar == '&')
         {
            str += "&amp;";
         }
         else if(iChar == '\"')
         {
            str += "&quot;";
         }
         else if(iChar == '\'')
         {
            str += "&#039;"; // apenas quando ENT_QUOTES est・definida.
         }
         else if(iChar == '<')
         {
            str += "&lt;";
         }
         else if(iChar == '>')
         {
            str += "&gt;";
         }
         else if(iChar < 0)
         {
            strChar.Format("&#%d;", iChar);
            str += strChar;
         }
         else
         {
            str += (char) iChar;
         }
         psz++;
      }
      return str;
   }


} // namespace ca2