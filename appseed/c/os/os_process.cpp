#include "StdAfx.h"


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