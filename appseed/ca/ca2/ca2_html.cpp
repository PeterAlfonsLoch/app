#include "framework.h"


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
         int iChar = (int) gen::ch::uni_index(gen::str::utf8_char(psz));
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
         else if(iChar < 128)
         {
            str += (char) iChar;
         }
         else
         {
            strChar.Format("&#%d;", iChar);
            str += strChar;
         }
         psz = gen::str::utf8_inc(psz);
      }
      return str;
   }


} // namespace ca2