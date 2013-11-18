#include "framework.h"


CLASS_DECL_BASE void reset_http()
{

}
CLASS_DECL_BASE void prepare_http()
{

}


CLASS_DECL_BASE bool http_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode, int32_t * piStatus, void(*callback)(void *, int32_t, uint_ptr), void * callback_param)
{

   return false;

}


CLASS_DECL_BASE string http_get_dup(const char * pszUrl, bool bCache, void(*callback)(void *, int32_t, uint_ptr), void * callback_param, bool bProgressCallback)
{

   base_application app;

   return app.http().get(pszUrl);

}


CLASS_DECL_BASE string http_defer_locale_schema_get(const char * pszUrl, const char * pszLocale, const char * pszSchema)
{

   string str;

   int32_t iAttempt = 0;

   string strUrl(pszUrl);

   if (strUrl.find("?") >= 0)
   {

      strUrl += "&";

   }
   else
   {

      strUrl += "?";

   }

   strUrl += "lang=" + string(pszLocale) + "&styl=" + string(pszSchema);

   while ((str = http_get_dup(strUrl)).is_empty())
   {
      iAttempt++;
      if (iAttempt > 11)
         return "";
      Sleep(iAttempt * 840);
   }

   return str;

}






