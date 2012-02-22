// atol.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "StdAfx.h"

int atoi_dup(const char * psz)
{
   int iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult += iResult * 10 + (ch - '0');
      psz++;
   }
   return iResult;
}

int atoi_dup(const char *psz, const char ** pszEnd)
{
   int iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult += iResult * 10 + (ch - '0');
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}


/*__int64 atoi64_dup(const char *str)
{
   return atol64_dup(str, NULL, 10);
/*    while (isspace_dup(*str))			// skip whitespace
        ++str;

    int cur = *str++;
    int neg = cur;					// Save the negative sign, if it exists

    if (cur == '-' || cur == '+')
        cur = *str++;

    // While we have digits, add 'em up.

	long total = 0;
    while (isdigit_dup(cur))
    {
        total = 10*total + (cur-'0');			// Add this digit to the total.
        cur = *str++;							// Do the next character.
    }

    // If we have a negative sign, convert the value.
    if (neg == '-')
        return -total;
    else
        return total;*/
//}



long wtol_dup(const wchar_t *str)
{
    while (iswspace_dup(*str))			// skip whitespace
        ++str;

    int cur = *str++;
    int neg = cur;					// Save the negative sign, if it exists

    if (cur == L'-' || cur == L'+')
        cur = *str++;

    // While we have digits, add 'em up.

	long total = 0;
    while (iswdigit_dup(cur))
    {
        total = 10*total + (cur-L'0');			// Add this digit to the total.
        cur = *str++;							// Do the next character.
    }

    // If we have a negative sign, convert the value.
    if (neg == L'-')
        return -total;
    else
        return total;
}

int wtoi_dup(const wchar_t *str)
{
    return (int)wtol_dup(str);
}

int _digit_atoi_dup(const char * psz, const char ** pszEnd, int iBase)
{
   int iResult = 0;
   char chMax = '0' + iBase;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > chMax)
         break;
      iResult += iResult * iBase + (ch - '0');
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int _atoi_dup(const char * psz, const char ** pszEnd, int iBase)
{
   int iResult = 0;
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
         iResult += iResult * iBase + (ch - '0');
      }
      else if(ch >= 'a' && ch <= chMax)
      {
         iResult += iResult * iBase + (ch - 'a' + 10);
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

int atoi_dup(const char * psz, const char ** pszEnd, int iBase)
{
   if(iBase <= 0)
      return 0;
   else if(iBase == 10)
      return atoi_dup(psz, pszEnd);
   else if(iBase < 10)
      return _digit_atoi_dup(psz, pszEnd, iBase);
   else if(iBase < 36)
      return _atoi_dup(psz, pszEnd, iBase);
   else
      return 0;
}

