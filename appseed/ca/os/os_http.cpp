#include "framework.h"

CLASS_DECL_ca vsstring defer_ls_get(const char * pszUrl, const char * pszLocale, const char * pszSchema)
{
   
   vsstring str;

   int32_t iAttempt = 0;

   vsstring strUrl(pszUrl);

   if(strUrl.find("?") >= 0)
   {

      strUrl += "&";

   }
   else
   {

      strUrl += "?";

   }

   strUrl += "lang=" + vsstring(pszLocale) + "&styl=" +  vsstring(pszSchema);

   while((str = ms_get_dup(strUrl)).is_empty())
   {
      iAttempt++;
      if(iAttempt > 11)
         return "";
      Sleep(iAttempt * 840);
   }

   return str;

}