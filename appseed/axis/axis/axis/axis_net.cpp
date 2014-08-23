#include "framework.h"


CLASS_DECL_AXIS string url_decode_dup(const char * psz)
{
   string str(psz);

   string strDecode;

   str.replace("+"," ");

   strsize iStart = 0;

   while(true)
   {

      strsize iFind = str.find("%",iStart);

      if(iFind == -1)
      {
         strDecode += str.Mid(iStart);
         break;
      }

      strDecode += str.Mid(iStart,iFind - iStart);

      if(str[iFind + 1] == '%')
      {

         strDecode += "%";
         iStart = iFind + 2;

      }
      else
      {

         char ch = (char)strtol(str.Mid(iFind + 1,2),NULL,16);

         if(ch != 0)
         {
            strDecode += ch;
         }

         iStart = iFind + 3;

      }


   }

   return strDecode;


}



string url_decode_dup(const char * lpszUrl,strsize iLen)
{

   string strDecode;

   char * psz = strDecode.GetBufferSetLength(iLen * 4);

   strsize i = 0;

   while(*lpszUrl != '\0' && i < iLen)
   {
      if(*lpszUrl == '+')
      {
         i++;
         *psz = ' ';
         psz++;
         lpszUrl++;
      }
      else if(*lpszUrl == '%')
      {
         iLen--;
         lpszUrl++;
         if(*lpszUrl == '%')
         {
            i++;
            *psz = '%';
            psz++;
            lpszUrl++;
         }
         else
         {
            i++;
            iLen--;
            *psz = (char)(uchar)(hex::to(*lpszUrl) * 16 + hex::to(*(lpszUrl + 1)));
            psz++;
            lpszUrl += 2;
         }
      }
      else
      {
         i++;
         *psz = *lpszUrl;
         psz++;
         lpszUrl++;
      }
   }

   strDecode.ReleaseBuffer(iLen);

   return strDecode;

}






CLASS_DECL_AXIS bool url_query_get_param_dup(string & strParam,const char * pszKey,const char * pszUrl)
{

   const char * pszBeg;
   const char * pszEnd;

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         strParam = "";

         return true;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         strParam = "";

         return true;

      }

   }

   return false;

success:

   pszEnd = strstr_dup(pszBeg,"&");

   if(pszEnd == NULL)
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = string(pszBeg,pszEnd - pszBeg);
   }

   return true;

}








string url_encode_dup(const char * psz)
{
   string str;
   char sz[256];
   while(*psz != '\0')
   {
      unsigned char uch = *psz;
      if(isdigit_dup(uch)
         || isalpha_dup(uch)
         || uch == '.'
         || uch == '-'
         || uch == '_')
      {
         str += uch;
      }
      else if(uch == ' ')
      {
         str += "+";
      }
      else
      {
         itoa_dup(sz,uch,16);
         if(strlen_dup(sz) == 0)
         {
            str += "%00";
         }
         else if(strlen_dup(sz) == 1)
         {
            str += "%0";
            str += sz;
         }
         else if(strlen_dup(sz) == 2)
         {
            str += "%";
            str += sz;
         }
      }
      psz++;
   }
   return str;
}



















