#include "StdAfx.h"


int64_t atoi64_dup(const char * psz)
{
   int64_t iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult = iResult * 10i64 + (ch - '0');
      psz++;
   }
   return iResult;
}

int64_t atoi64_dup(const char *psz, const char ** pszEnd)
{
   int64_t iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult = iResult * 10i64 + (ch - '0');
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int64_t _digit_atoi64_dup(const char * psz, const char ** pszEnd, int iBase)
{
   int64_t iResult = 0;
   char chMax = '0' + iBase;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > chMax)
         break;
      iResult = iResult * iBase + (ch - '0');
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int64_t _atoi64_dup(const char * psz, const char ** pszEnd, int iBase)
{
   int64_t iResult = 0;
   char chMax = 'a' + iBase - 10;
   while(true)
   {

      char ch = to_lower(*psz);

      if(ch == '\0')
      {
         break;
      }
      else if(ch >= '0' && ch <= '9')
      {
         iResult = iResult * iBase + (ch - '0');
      }
      else if(ch >= 'a' && ch <= chMax)
      {
         iResult = iResult * iBase + (ch - 'a' + 10);
      }
      else
      {
         break;
      }
      
      psz++;

   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int64_t atoi64_dup(const char * psz, const char ** pszEnd, int iBase)
{
   if(iBase <= 0)
      return 0;
   else if(iBase == 10)
      return atoi64_dup(psz, pszEnd);
   else if(iBase < 10)
      return _digit_atoi64_dup(psz, pszEnd, iBase);
   else if(iBase < 36)
      return _atoi64_dup(psz, pszEnd, iBase);
   else
      return 0;
}

/*__int64 atol64_dup(const char * sz, const char ** pszEnd, int iBase)
{
   const char * szIter = sz;
   while(*szIter != '\0' && ((*szIter >= '0' && *szIter <= ('0' + min(9, iBase))) || (to_lower(*szIter) >= 'a' && to_lower(*szIter) <= ('a' + iBase - 10))))
   {
      szIter++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = szIter;
   }
   szIter--;
   __int64 iResult = 0;
   __int64 iPow = 1;
   while(szIter >= sz)
   {
      char ch = *szIter;
      int iDigit;
      if(ch >= '0' && ch <= '9')
      {
         iDigit = ch - '0';
      }
      else
      {
         iDigit = to_lower(ch) - 'a';
      }
      iResult += iDigit * iPow;
      iPow = iPow * iBase;
      szIter--;
   }
   return iResult;
}

*/
