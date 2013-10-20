#include "framework.h"


CLASS_DECL_BOOT bool url_query_get_param_dup(string & strParam, const char * pszKey, const char * pszUrl)
{

   const char * pszBeg;
   const char * pszEnd;

   {
    
      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl, strKey);

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

      pszBeg = strstr_dup(pszUrl, strKey);

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

      pszBeg = strstr_dup(pszUrl, strKey);

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

      pszBeg = strstr_dup(pszUrl, strKey);

      if(pszBeg != NULL)
      {

         strParam = "";
         
         return true;

      }

   }

   return false;

success:

   pszEnd = strstr_dup(pszBeg, "&");

   if(pszEnd == NULL)
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = string(pszBeg, pszEnd - pszBeg);
   }

   return true;

}




