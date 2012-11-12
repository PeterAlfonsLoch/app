// atol.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"

int atoi_dup(const char * psz)
{
   int iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult = iResult * 10 + (ch - '0');
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
      iResult = iResult * 10 + (ch - '0');
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}


/*int64_t atoi64_dup(const char *str)
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
total = 10*total + (cur-'0');			// add this digit to the total.
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
      total = 10*total + (cur-L'0');			// add this digit to the total.
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
      iResult = iResult * iBase + (ch - '0');
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



int natoi_dup(const char * psz, int iLen)
{
   int iResult = 0;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult = iResult * 10 + (ch - '0');
      psz++;
      iLen--;
   }
   return iResult;
}

int natoi_dup(const char *psz, const char ** pszEnd, int iLen)
{
   int iResult = 0;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
      iResult = iResult * 10 + (ch - '0');
      psz++;
      iLen--;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}


/*int64_t atoi64_dup(const char *str)
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
total = 10*total + (cur-'0');			// add this digit to the total.
cur = *str++;							// Do the next character.
}

// If we have a negative sign, convert the value.
if (neg == '-')
return -total;
else
return total;*/
//}



long nwtol_dup(const wchar_t *str, int iLen)
{
   while (iLen > 0 && iswspace_dup(*str))			// skip whitespace
   {
      ++str;
      iLen--;
   }

   if(iLen <= 0)
      return 0;

   int cur = *str++;
   int neg = cur;					// Save the negative sign, if it exists

   if (cur == L'-' || cur == L'+')
   {
      cur = *str++;
      iLen--;
      if(iLen <= 0)
         return 0;
   }


   // While we have digits, add 'em up.

   long total = 0;
   while (iswdigit_dup(cur))
   {
      iLen--;
      if(iLen <= 0)
         break;
      total = 10*total + (cur-L'0');			// add this digit to the total.
      cur = *str++;							// Do the next character.
   }

   // If we have a negative sign, convert the value.
   if (neg == L'-')
      return -total;
   else
      return total;
}

int nwtoi_dup(const wchar_t *str, int iLen)
{
   return (int)nwtol_dup(str, iLen);
}

int _digit_natoi_dup(const char * psz, const char ** pszEnd, int iBase, int iLen)
{
   int iResult = 0;
   char chMax = '0' + iBase;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > chMax)
         break;
      iResult = iResult * iBase + (ch - '0');
      psz++;
      iLen--;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int _natoi_dup(const char * psz, const char ** pszEnd, int iBase, int iLen)
{
   int iResult = 0;
   char chMax = 'a' + iBase - 10;
   while(iLen > 0)
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
      iLen--;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = psz;
   }
   return iResult;
}

int natoi_dup(const char * psz, const char ** pszEnd, int iBase, int iLen)
{
   if(iBase <= 0)
      return 0;
   else if(iBase == 10)
      return natoi_dup(psz, pszEnd, iLen);
   else if(iBase < 10)
      return _digit_natoi_dup(psz, pszEnd, iBase, iLen);
   else if(iBase < 36)
      return _natoi_dup(psz, pszEnd, iBase, iLen);
   else
      return 0;
}




#include "framework.h"


int64_t atoi64_dup(const char * psz)
{
   int64_t iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
#ifdef WINDOWS
      iResult = iResult * 10i64 + (ch - '0');
#else
      iResult = iResult * 10+ (ch - '0');
#endif
      psz++;
   }
   return iResult;
}

int64_t atoi64_dup(const char *psz, char ** pszEnd)
{
   int64_t iResult = 0;
   while(true)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
#ifdef WINDOWS
      iResult = iResult * 10i64 + (ch - '0');
#else
      iResult = iResult * 10+ (ch - '0');
#endif
      psz++;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}

int64_t _digit_atoi64_dup(const char * psz, char ** pszEnd, int iBase)
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
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}

int64_t _atoi64_dup(const char * psz, char ** pszEnd, int iBase)
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
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}

int64_t atoi64_dup(const char * psz, char ** pszEnd, int iBase)
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

/*int64_t atol64_dup(const char * sz, const char ** pszEnd, int iBase)
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
   int64_t iResult = 0;
   int64_t iPow = 1;
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


int64_t natoi64_dup(const char * psz, int iLen)
{
   int64_t iResult = 0;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
#ifdef WINDOWS
      iResult = iResult * 10i64 + (ch - '0');
#else
      iResult = iResult * 10+ (ch - '0');
#endif
      psz++;
      iLen--;
   }
   return iResult;
}

int64_t natoi64_dup(const char *psz, char ** pszEnd, int iLen)
{
   int64_t iResult = 0;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > '9')
         break;
#ifdef WINDOWS
      iResult = iResult * 10i64 + (ch - '0');
#else
      iResult = iResult * 10+ (ch - '0');
#endif
      psz++;
      iLen--;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}

int64_t _digit_natoi64_dup(const char * psz, char ** pszEnd, int iBase, int iLen)
{
   int64_t iResult = 0;
   char chMax = '0' + iBase;
   while(iLen > 0)
   {
      char ch = *psz;
      if(ch == '\0' || ch < '0' || ch > chMax)
         break;
      iResult = iResult * iBase + (ch - '0');
      psz++;
      iLen--;
   }
   if(pszEnd != NULL)
   {
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}

int64_t _natoi64_dup(const char * psz, char ** pszEnd, int iBase, int iLen)
{
   int64_t iResult = 0;
   char chMax = 'a' + iBase - 10;
   while(iLen > 0)
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
      iLen--;

   }
   if(pszEnd != NULL)
   {
      *pszEnd = const_cast < char * > (psz);
   }
   return iResult;
}


int64_t natoi64_dup(const char * psz, char ** pszEnd, int iBase, int iLen)
{
   if(iBase <= 0)
      return 0;
   else if(iBase == 10)
      return atoi64_dup(psz, pszEnd, iLen);
   else if(iBase < 10)
      return _digit_natoi64_dup(psz, pszEnd, iBase, iLen);
   else if(iBase < 36)
      return _natoi64_dup(psz, pszEnd, iBase, iLen);
   else
      return 0;
}

int64_t nwtoi64_dup(const wchar_t * str, const wchar_t ** pszEnd, int iBase, int iLen)
{
   while (iLen > 0 && iswspace_dup(*str))			// skip whitespace
   {
      ++str;
      iLen--;
   }

   if(iLen <= 0)
      return 0;

   int cur = *str++;
   int neg = cur;					// Save the negative sign, if it exists

   if (cur == L'-' || cur == L'+')
   {
      cur = *str++;
      iLen--;
      if(iLen <= 0)
         return 0;
   }


   // While we have digits, add 'em up.

   int64_t total = 0;
   int iDigit;
   while (iswalnum_dup(cur))
   {
      iLen--;
      if(iLen <= 0)
         break;
      if(cur >= L'0' && cur <= L'9')
      {
         iDigit = cur - L'0';
      }
      else if(cur >= L'A' && cur <= L'Z')
      {
         iDigit = cur - L'A';
      }
      else if(cur >= L'a' && cur <= L'z')
      {
         iDigit = cur - L'a';
      }
      else
      {
         break;
      }
      if(iDigit >= iBase)
         break;
      total = iBase * total + iDigit;			// add this digit to the total.
      cur = *str++;							// Do the next character.
   }

   if(pszEnd != NULL)
   {
      *pszEnd = str;
   }

   // If we have a negative sign, convert the value.
   if (neg == L'-')
      return -total;
   else
      return total;
}


int64_t wtoi64_dup(const wchar_t * str, const wchar_t ** pszEnd, int iBase)
{

   while(*str != L'\0' && iswspace_dup(*str))			// skip whitespace
   {
      ++str;
   }


   int cur = *str++;
   int neg = cur;					// Save the negative sign, if it exists

   if(cur == L'\0')
      return 0;

   if (cur == L'-' || cur == L'+')
   {
      cur = *str++;
   }


   // While we have digits, add 'em up.

   int64_t total = 0;
   int iDigit;
   while(cur != L'\0' && iswalnum_dup(cur))
   {
      if(cur >= L'0' && cur <= L'9')
      {
         iDigit = cur - L'0';
      }
      else if(cur >= L'A' && cur <= L'Z')
      {
         iDigit = cur - L'A';
      }
      else if(cur >= L'a' && cur <= L'z')
      {
         iDigit = cur - L'a';
      }
      else
      {
         break;
      }
      if(iDigit >= iBase)
         break;
      total = iBase * total + iDigit;			// add this digit to the total.
      cur = *str++;							// Do the next character.
   }

   if(pszEnd != NULL)
   {
      *pszEnd = str;
   }

   // If we have a negative sign, convert the value.
   if (neg == L'-')
      return -total;
   else
      return total;
}


CLASS_DECL_c int64_t wtoi64_dup(const wchar_t * sz, const wchar_t ** pszEnd)
{

   return wtoi64_dup(sz, NULL, 10);

}

CLASS_DECL_c int64_t wtoi64_dup(const wchar_t * sz)
{

   return wtoi64_dup(sz, NULL);

}
