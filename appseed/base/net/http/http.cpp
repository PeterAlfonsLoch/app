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









string url_encode_dup(const char * psz)
{
   string str;
   char sz[256];
   while (*psz != '\0')
   {
      unsigned char uch = *psz;
      if (isdigit_dup(uch)
         || isalpha_dup(uch)
         || uch == '.'
         || uch == '-'
         || uch == '_')
      {
         str += uch;
      }
      else if (uch == ' ')
      {
         str += "+";
      }
      else
      {
         itoa_dup(sz, uch, 16);
         if (strlen_dup(sz) == 0)
         {
            str += "%00";
         }
         else if (strlen_dup(sz) == 1)
         {
            str += "%0";
            str += sz;
         }
         else if (strlen_dup(sz) == 2)
         {
            str += "%";
            str += sz;
         }
      }
      psz++;
   }
   return str;
}

