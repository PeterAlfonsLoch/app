// atol.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "StdAfx.h"

int atoi_dup(const char *str)
{
   return atol_dup(str, NULL, 10);
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


int atol_dup(const char * sz, const char ** pszEnd, int iBase)
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
   int iResult = 0;
   int iPow = 1;
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
