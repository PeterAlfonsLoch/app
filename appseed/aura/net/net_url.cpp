#include "framework.h"


namespace url
{

   bool is_url(const char * pszCandidate,const char ** ppszRequest)
   {
      const char * psz = pszCandidate;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || isalnum_dup(*psz)))
      {
         psz++;
      }
      if(psz == pszCandidate)
         return false;
      if(*psz != ':')
         return false;
      psz++;
      if(*psz != '/' && *psz != '\\')
         return false;
      psz++;
      if(*psz != '/' && *psz != '\\')
         return false;
      psz++;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || isalnum_dup(*psz)))
      {
         psz++;
      }
      if(*psz != '\0' && *psz != '/' && *psz != '\\')
         return false;
      if(ppszRequest != NULL)
      {
         *ppszRequest = psz;
      }
      return true;

   }



} // namespace url




































