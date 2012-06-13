#include "framework.h"


vsstring consume_param(const char * pszCommandLine, const char ** pszEndPtr)
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

   return vsstring(pszStart, pszEnd - pszStart);

}



vsstring get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam)
{

   vsstring strValue = get_command_line_param(pszCommandLine, pszParam);

   if(strValue == pszIfParamValue)
   {
         
      vsstring strReplace = get_command_line_param(pszCommandLine, pszReplaceParam);

      if(strReplace.has_char())
      {
         strValue = strReplace;
      }

   }

   return strValue;

}

vsstring get_command_line_param(const char * pszCommandLine, const char * pszParam)
{

   vsstring strParam(pszParam);

   strParam = strParam + "=";

   vsstring strValue;

   const char * pszValue = strstr_dup(pszCommandLine, strParam);

   if(pszValue == NULL)
      return "";

   pszValue += strParam.length();

   const char * pszValueEnd = strstr_dup(pszValue, " ");

   if(pszValueEnd == NULL)
   {
      strValue = vsstring(pszValue);
   }
   else
   {
      strValue = vsstring(pszValue, pszValueEnd - pszValue);
   }

   return strValue;

}
