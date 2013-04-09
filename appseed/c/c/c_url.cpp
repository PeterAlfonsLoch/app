#include "framework.h"


CLASS_DECL_c bool url_query_get_param_dup(vsstring & strParam, const char * pszKey, const char * pszUrl)
{

   const char * pszBeg;
   const char * pszEnd;

   {
    
      vsstring strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl, strKey);

      if(pszBeg != ::null())
      {
         
         pszBeg += strKey.get_length();

         goto success;
      
      }

   }

   {
    
      vsstring strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl, strKey);

      if(pszBeg != ::null())
      {
         
         pszBeg += strKey.get_length();

         goto success;
      
      }

   }

   {
    
      vsstring strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl, strKey);

      if(pszBeg != ::null())
      {

         strParam = "";
         
         return true;

      }

   }

   {
    
      vsstring strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl, strKey);

      if(pszBeg != ::null())
      {

         strParam = "";
         
         return true;

      }

   }

   return false;

success:

   pszEnd = strstr_dup(pszBeg, "&");

   if(pszEnd == ::null())
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = vsstring(pszBeg, pszEnd - pszBeg);
   }

   return true;

}




