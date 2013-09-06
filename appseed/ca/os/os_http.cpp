#include "framework.h"

CLASS_DECL_ca string defer_ls_get(const char * pszUrl, const char * pszLocale, const char * pszSchema)
{
   
   string str;

   int32_t iAttempt = 0;

   string strUrl(pszUrl);

   if(strUrl.find("?") >= 0)
   {

      strUrl += "&";

   }
   else
   {

      strUrl += "?";

   }

   strUrl += "lang=" + string(pszLocale) + "&styl=" +  string(pszSchema);

   while((str = http_get_dup(strUrl)).is_empty())
   {
      iAttempt++;
      if(iAttempt > 11)
         return "";
      Sleep(iAttempt * 840);
   }

   return str;

}