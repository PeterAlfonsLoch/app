#include "framework.h"


string consume_param(const char * pszCommandLine, const char ** pszEndPtr)
{

   if(pszCommandLine == NULL)
      return "";

   const char * psz = pszCommandLine;

   while(*psz && isspace_dup(*psz))
      psz++;

   const char * pszStart;

   bool bQuoted = *psz == '\"';

   if(bQuoted)
   {
      psz++;
      pszStart = psz;
      while(*psz != '\0' && *psz != '\"')
         psz++;
   }
   else
   {
      pszStart = psz;
      while(*psz != '\0' &&!isspace_dup(*psz))
         psz++;
   }
   
   const char * pszEnd = psz;

   if(pszEndPtr != NULL)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(pszStart, pszEnd - pszStart);

}



string get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam)
{

   string strValue = get_command_line_param(pszCommandLine, pszParam);

   if(strValue == pszIfParamValue)
   {
         
      string strReplace = get_command_line_param(pszCommandLine, pszReplaceParam);

      if(strReplace.has_char())
      {
         strValue = strReplace;
      }

   }

   return strValue;

}

string get_command_line_param(const char * pszCommandLine, const char * pszParam)
{

   string strParam(pszParam);

   strParam = strParam + "=";

   string strValue;

   const char * pszValue = strstr_dup(pszCommandLine, strParam);

   if(pszValue == NULL)
      return "";

   pszValue += strParam.length();


   if(*pszValue == '"')
   {

      const char * pszValueEnd = strchr_dup(pszValue + 1, '"');

      if(pszValueEnd == NULL)
      {
         strValue = string(pszValue);
      }
      else
      {
         strValue = string(pszValue, pszValueEnd - pszValue + 1);
      }

   }
   else
   {

      const char * pszValueEnd = strstr_dup(pszValue, " ");

      if(pszValueEnd == NULL)
      {
         strValue = string(pszValue);
      }
      else
      {
         strValue = string(pszValue, pszValueEnd - pszValue);
      }

   }

   return strValue;


}



