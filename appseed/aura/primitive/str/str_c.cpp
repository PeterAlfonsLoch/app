#include "framework.h"
//#include "ca/x/x_defines.h"
//#include "ca/x/x_tables.h"
//#include "ca/x/x_charcategory_names.h"
//#include "ca/x/x_charcategory.h"


void strcat_dup(char * dest, const char * cat)
{
   if(dest == NULL)
      return;
   if(cat == NULL)
      return;
   strcat(dest, cat);
   /*while(*dest != 0)
      dest++;
   while(*cat != 0)
      *dest++ = *cat++;
   *dest = '\0';*/
}


#ifdef APPLEOS

int32_t stricmp(const char * sz1, const char * sz2)
{
   return stricmp_dup(sz1, sz2);
}

#endif


int32_t stricmp_dup(const char * sz1, const char * sz2)
{
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return -1;
   }
   else if(sz2 == NULL)
   {
      return 1;
   }
   int32_t iCmp = 0;
   while(*sz1 != '\0' && *sz2 != '\0')
   {
      iCmp = char_to_lower(*sz1) - char_to_lower(*sz2);
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return char_to_lower(*sz1) - char_to_lower(*sz2);
}

int32_t strcmp_dup(const char * sz1, const char * sz2)
{
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return -1;
   }
   else if(sz2 == NULL)
   {
      return 1;
   }
   int32_t iCmp;
   while(*sz1 != '\0' && *sz2 != '\0')
   {
      iCmp = *sz1 - *sz2;
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return *sz1 - *sz2;
}

int32_t strnicmp_dup(const char * sz1, const char * sz2, ::count iLen)
{

   if(iLen <= 0)
   {

      return 0; // equal

   }

   if(sz1 == NULL)
   {

      if(sz2 == NULL)
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if(sz2 == NULL)
   {

      return 1;

   }

   int32_t iCmp = 0;

   while(iLen > 0)
   {

      iCmp = char_to_lower(*sz1) - char_to_lower(*sz2);

      if(iCmp != 0)
      {

         return iCmp;

      }

      if(*sz1 == '\0' || *sz2 == '\0')
      {

         return iCmp;

      }

      sz1++;

      sz2++;

      iLen--;

   }

   return iCmp;

}

int32_t strncmp_dup(const char * sz1, const char * sz2, ::count iLen)
{
   if(iLen <= 0)
      return 0; // equal
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return -1;
   }
   else if(sz2 == NULL)
   {
      return 1;
   }
   int32_t iCmp = 0;
   while(iLen > 0 && *sz1 != '\0' && *sz2 != '\0')
   {
      iCmp = *sz1 - *sz2;
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
      iLen--;
   }
   return iCmp;
}

char * strrchr_dup(char * szStart, char ch)
{
   char * sz = szStart;
   while(*sz != '\0')
   {
      sz++;
   }
   while(sz != szStart)
   {
      sz--;
      if(*sz == ch)
         return sz;
   }
   return NULL;

}

char char_to_lower(int32_t ch)
{
   if(ch >= 'A' && ch <= 'Z')
   {
      ch = ch - 'A' + 'a';
   }
   return ch;
}

char * to_lower(char * pchParam)
{
   char * pch = pchParam;
   while(*pch != '\0')
   {
      *pch = char_to_lower(*pch);
      pch++;
   }
   return pchParam;
}


char char_to_upper(int32_t ch)
{
   if(ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }
   return ch;
}

char * to_upper(char * pchParam)
{
   char * pch = pchParam;
   while(*pch != '\0')
   {
      *pch = char_to_upper(*pch);
      pch++;
   }
   return pchParam;
}


char * strstr_dup(const char * src, const char * find)
{
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      while(*srcParse != '\0' && *findParse != '\0')
      {
         if(*srcParse != *findParse)
            break;
         srcParse++;
         findParse++;
      }
      if(*findParse == '\0')
         return (char *) src;
      src++;
   }
   return NULL;
}

char * stristr_dup(const char * src, const char * find)
{
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      while(*srcParse != '\0' && *findParse != '\0')
      {
         if(char_to_lower(*srcParse) != char_to_lower(*findParse))
            break;
         srcParse++;
         findParse++;
      }
      if(*findParse == '\0')
         return (char *) src;
      src++;
   }
   return NULL;
}

char * strnstr_dup(const char * src, const char * find, int_ptr iLen)
{
   if(iLen == 0)
      return (char *) src;
   if(iLen > strlen_dup(find))
      return NULL;
   int_ptr c;
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      c = iLen;
      while(*srcParse != '\0' && *findParse != '\0')
      {
         if(*srcParse != *findParse)
            break;
         srcParse++;
         findParse++;
         c--;
      }
      if(c == 0 || *findParse == '\0')
         return (char *) src;
      src++;
   }
   return NULL;
}

char * strnistr_dup(const char * src, const char * find, int_ptr iLen)
{
   if(iLen == 0)
      return (char *) src;
   if(iLen > strlen_dup(find))
      return NULL;
   int_ptr c;
   while(*src != '\0')
   {
      const char * srcParse = src;
      const char * findParse = find;
      c = iLen;
      while(c > 0 && *srcParse != '\0' && *findParse != '\0')
      {
         if(char_to_lower(*srcParse) != char_to_lower(*findParse))
            break;
         srcParse++;
         findParse++;
         c--;
      }
      if(c == 0 || *findParse == '\0')
         return (char *) src;
      src++;
   }
   return NULL;
}


void uitoa_dup(char * sz, uint64_t ui, int32_t iBase)
{
   if(ui == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   int32_t iIndex = 0;
   while(ui > 0)
   {
      int32_t iDigit = (ui % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      ui = ui / iBase;
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}



void itoa_dup(char * sz, int64_t i, int32_t iBase)
{
   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}




/*void l64toa_dup(char * sz, int64_t i, int64_t iBase)
{
   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int64_t iIndex = 0;
   while(i > 0)
   {
      int64_t iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}

void i64toa_dup(char * sz, int64_t i)
{
  l64toa_dup(sz, i, 10);
}*/


void str_reverse(char * sz)
{

   mem_reverse(sz, strlen_dup(sz));

}

void zero_pad(char * sz, ::count iPad)
{

   ::count iLen = strlen_dup(sz);

   ::count iZeroCount = iPad - iLen;

   if(iZeroCount > 0)
   {

      ::count iEnd = iLen - 1;

      ::count iFinalEnd = iEnd + iZeroCount;

      sz[iFinalEnd + 1] = '\0';

      for(; iEnd >= 0; iEnd--, iFinalEnd--)
      {
         sz[iFinalEnd] = sz[iEnd];
      }

      for(; iFinalEnd >= 0; iFinalEnd--)
      {
         sz[iFinalEnd] = '0';
      }

   }

}

char * str_begins_inc_dup(const char * sz1, const char * prefix)
{
   if(sz1 == NULL)
      return NULL;
   if(prefix == NULL)
      return (char *) sz1;
   while(*sz1 != '\0' && *prefix != '\0')
   {
      if(*sz1 != *prefix)
         return NULL;
      sz1++;
      prefix++;
   }
   if(*prefix == '\0')
      return (char *) sz1;
   else
      return NULL;
}


int32_t str_begins_dup(const char * sz1, const char * prefix)
{
   if(sz1 == NULL)
      return FALSE;
   if(prefix == NULL)
      return TRUE;
   while(*sz1 != '\0' && *prefix != '\0')
   {
      if(*sz1 != *prefix)
         return FALSE;
      sz1++;
      prefix++;
   }
   return *prefix == '\0';
}

int32_t str_begins_ci_dup(const char * sz1, const char * prefix)
{
   if(sz1 == NULL)
      return FALSE;
   if(prefix == NULL)
      return TRUE;
   while(*sz1 != '\0' && *prefix != '\0')
   {
      if(*sz1 != *prefix)
         return FALSE;
      sz1++;
      prefix++;
   }
   return *prefix == '\0';
}

int32_t str_ends_dup(const char * psz, const char * pszSuffix)
{

   ::count iLen = strlen_dup(psz);

   ::count iLenSuffix = strlen_dup(pszSuffix);

   if(iLen < iLenSuffix)
      return false;

   return strcmp_dup(&psz[iLen - iLenSuffix], pszSuffix) == 0;

}


int32_t str_ends_ci_dup(const char * psz, const char * pszSuffix)
{

   ::count iLen = strlen_dup(psz);

   ::count iLenSuffix = strlen_dup(pszSuffix);

   if(iLen < iLenSuffix)
      return false;

   return stricmp_dup(&psz[iLen - iLenSuffix], pszSuffix) == 0;

}

















#define NULCHAR     '\0'
#define TABCHAR     '\t'
#define SLASHCHAR   '\\'
#define SPACECHAR   ' '
#define DQUOTECHAR  '\"'


void __cdecl parse_cmdline(char *cmdstart, char **argv, char *args, int32_t * numargs, int32_t * numchars)
{
        char *p;
        char c;
        int32_t inquote;                    /* 1 = inside quotes */
        int32_t copychar;                   /* 1 = copy char to *args */
        uint32_t numslash;              /* num of backslashes seen */

        *numchars = 0;
        *numargs = 1;                   /* the program name at least */

        /* first scan the program name, copy it, and ::count the bytes */
        p = cmdstart;
        if (argv)
            *argv++ = args;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* A quoted program name is handled here. The handling is much
           simpler than for other arguments. Basically, whatever lies
           between the leading double-quote and next one, or a terminal NULL
           character is simply accepted. Fancier handling is not required
           because the program name must be a legal NTFS/HPFS file name.
           Note that the double-quote characters are not copied, nor do they
           contribute to numchars. */
        if ( *p == DQUOTECHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a NULL, whichever comes first */
            while ( (*(++p) != DQUOTECHAR) && (*p != NULCHAR) ) {

/*#ifdef _MBCS
                if (_ismbblead(*p)) {
                    ++*numchars;
                    if ( args )
                        *args++ = *p++;
                }
#endif  /* _MBCS */
                ++*numchars;
                if ( args )
                    *args++ = *p;
            }
            /* append the terminating NULL */
            ++*numchars;
            if ( args )
                *args++ = NULCHAR;

            /* if we stopped on a double-quote (usual case), skip over it */
            if ( *p == DQUOTECHAR )
                p++;
        }
        else {
            /* Not a quoted program name */
            do {
                ++*numchars;
                if (args)
                    *args++ = *p;

                c = (char) *p++;
/*#ifdef _MBCS
                if (_ismbblead(c)) {
                    ++*numchars;
                    if (args)
                        *args++ = *p;   /* copy 2nd byte too */
    //                p++;  /* skip over trail byte */
  //              }
//#endif  /* _MBCS */

            } while ( c != SPACECHAR && c != NULCHAR && c != TABCHAR );

            if ( c == NULCHAR ) {
                p--;
            } else {
                if (args)
                    *(args-1) = NULCHAR;
            }
        }

        inquote = 0;

        /* loop on each argument */
        for(;;) {

            if ( *p ) {
                while (*p == SPACECHAR || *p == TABCHAR)
                    ++p;
            }

            if (*p == NULCHAR)
                break;              /* end of args */

            /* scan an argument */
            if (argv)
                *argv++ = args;     /* store ptr to arg */
            ++*numargs;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* loop through scanning one argument */
        for (;;) {
            copychar = 1;
            /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
               2N+1 backslashes + " ==> N backslashes + literal "
               N backslashes ==> N backslashes */
            numslash = 0;
            while (*p == SLASHCHAR) {
                /* ::count number of backslashes for use below */
                ++p;
                ++numslash;
            }
            if (*p == DQUOTECHAR) {
                /* if 2N backslashes before, start/end quote, otherwise
                    copy literally */
                if (numslash % 2 == 0) {
                    if (inquote) {
                        if (p[1] == DQUOTECHAR)
                            p++;    /* Double quote inside quoted string */
                        else        /* skip first quote char and copy second */
                            copychar = 0;
                    } else
                        copychar = 0;       /* don't copy quote */

                    inquote = !inquote;
                }
                numslash /= 2;          /* divide numslash by two */
            }

            /* copy slashes */
            while (numslash--) {
                if (args)
                    *args++ = SLASHCHAR;
                ++*numchars;
            }

            /* if at end of arg, break loop */
            if (*p == NULCHAR || (!inquote && (*p == SPACECHAR || *p == TABCHAR)))
                break;

            /* copy character into argument */
/*#ifdef _MBCS
            if (copychar) {
                if (args) {
                    if (_ismbblead(*p)) {
                        *args++ = *p++;
                        ++*numchars;
                    }
                    *args++ = *p;
                } else {
                    if (_ismbblead(*p)) {
                        ++p;
                        ++*numchars;
                    }
                }
                ++*numchars;
            }
            ++p;
#else  /* _MBCS */
            if (copychar) {
                if (args)
                    *args++ = *p;
                ++*numchars;
            }
            ++p;
//#endif  /* _MBCS */
            }

            /* NULL-terminate the argument */

            if (args)
                *args++ = NULCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a NULL ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}







char * strchr_dup(const char * sz, char ch)
{
   if(sz == NULL)
      return NULL;
   while(true)
   {
      if(*sz == ch)
         return (char *) sz;
      if(*sz == '\0')
         return NULL;
      sz++;
   }
}


int32_t isdigit_dup(int32_t ch)
{
   return ch >= '0' && ch <= '9';
}

int32_t isxdigit_dup(int32_t ch)
{
   return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

int32_t isalpha_dup(int32_t ch)
{
   return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int32_t isalnum_dup(int32_t ch)
{
   return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}

int32_t isspace_dup(int32_t ch)
{
   return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\t';
}



char * strpbrk_dup(char * sz, const char * szFind)
{
   char * pszRet = NULL;
   while(*szFind != '\0')
   {
      char * psz = strchr_dup(sz, *szFind);
      if(psz != NULL && (pszRet == NULL || psz < pszRet))
      {
         pszRet = psz;
      }
      szFind++;
   }
   return pszRet;
}




/*string str_replace_dup(const char * psz, const char * pszFind, const char * pszReplace)
{
   string str(psz);
   str.replace(pszFind, pszReplace);
   return str;
}
*/

string itoa_dup(int64_t i)
{
   char sz[256];
   itoa_dup(sz, i, 10);
   return string(sz);
}

/*
string itohex_dup(int64_t i)
{
   char sz[256];
   itoa_dup(sz, i, 16);
   return string(sz);
}
*/

/*
string itohexpad_dup(int64_t i, int32_t iPad)
{
   string str = itohex_dup(i);
   while(iPad > str.length())
      str = "0" + str;
   return str;
}
*/
/*string i64toa_dup(int64_t i)
{
   char sz[512];
   i64toa_dup(sz, i);
   return string(sz);
}*/

#ifdef WINDOWSEX

string read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = ::FindResource(hinst, MAKEINTRESOURCE(nID), lpcszType);

   if(hrsrc == NULL)
		return "";

   HGLOBAL hres = ::LoadResource(hinst, hrsrc);

   if(hres == NULL)
		return "";

   uint32_t dwResSize = ::SizeofResource(hinst, hrsrc);

   string str;
   char * psz = NULL;

	if(hres != NULL)
   {

      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);

      psz = str.GetBufferSetLength(dwResSize);
      memcpy(psz, lpnRes, dwResSize);
      psz[dwResSize] = '\0';
      str.ReleaseBuffer(dwResSize);
      ::FreeResource(hres);
	}
   return str;

}


#endif


char * strtok_r_dup(char *s1, const char *s2, char **lasts)
{
  char *ret;

  if (s1 == NULL)
    s1 = *lasts;
  while(*s1 && strchr_dup(s2, *s1))
    ++s1;
  if(*s1 == '\0')
    return NULL;
  ret = s1;
  while(*s1 && !strchr_dup(s2, *s1))
    ++s1;
  if(*s1)
    *s1++ = '\0';
  *lasts = s1;
  return ret;
}






#if !defined(WINDOWS)

char * strlwr(char * pszParam)
{

   char * psz = pszParam;

   if(psz == NULL)
      return NULL;

   while(*psz != '\0')
   {
      if(*psz >= 'A' && *psz <= 'Z')
      {
         *psz = *psz - 'A' + 'a';
      }
      psz++;
   }

   return pszParam;

}

char * strupr(char * pszParam)
{

   char * psz = pszParam;

   if(psz == NULL)
      return NULL;

   while(*psz != '\0')
   {
      if(*psz >= 'a' && *psz <= 'z')
      {
         *psz = *psz - 'a' + 'A';
      }
      psz++;
   }

   return pszParam;

}

#endif



void zero_pad(string & str, ::count iPad)
{

   while(str.length() < iPad)
   {

      str = "0" + str;

   }

}

const char * wildcard_next_stop(const char * pszCriteria)
{

   if(pszCriteria == NULL)
      return NULL;


   const char * pszAsterisk = strstr_dup(pszCriteria, "*");
   const char * pszQuestion = strstr_dup(pszCriteria, "?");

   if(pszAsterisk == NULL && pszQuestion == NULL)
      return NULL;

   if(pszAsterisk == NULL)
      return pszQuestion;
   else if(pszQuestion == NULL)
      return pszAsterisk;
   else if(pszAsterisk < pszQuestion)
      return pszAsterisk;
   else
      return pszQuestion;

}



int_bool matches_wildcard_criteria(const char * pszCriteria, const char * pszValue)
{


   const char * pszFind;
   const char * pszStop;

   int_ptr iLen;

   while(true)
   {

      pszFind = wildcard_next_stop(pszCriteria);

      if(pszFind == NULL)
         break;

      iLen = pszFind - pszCriteria;

      if(*pszFind == '?')
      {

         if(pszFind > pszCriteria)
         {
            if(strncmp(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue       += iLen;
            pszCriteria    += iLen;
         }

         if(*pszValue == '\0')
            return false;

         pszCriteria++;
         pszValue++;

      }
      else if(*pszFind == '*')
      {

         if(pszFind > pszCriteria)
         {
            if(strncmp(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue       += iLen;
            pszCriteria    += iLen;
         }

         pszStop = wildcard_next_stop(pszFind + 1);

         if(pszStop == NULL)
            return true;

         iLen = pszStop - (pszFind + 1);

         pszValue = strnstr_dup(pszValue, pszFind + 1, iLen);

         if(pszValue == NULL)
            return false;

         pszValue    = pszValue + iLen;
         pszCriteria = pszStop;

      }
      else
      {
         throw "not_expected, check wildcard_next_stop function";
      }


   }

   if(strcmp(pszValue, pszCriteria) != 0)
      return false;

   return true;

}

int_bool matches_wildcard_criteria_ci(const char * pszCriteria, const char * pszValue)
{

   const char * pszFind;
   const char * pszStop;

   int_ptr iLen;

   while(true)
   {

      pszFind = wildcard_next_stop(pszCriteria);

      if(pszFind == NULL)
         break;

      iLen = pszFind - pszCriteria;

      if(*pszFind == '?')
      {

         if(pszFind > pszCriteria)
         {
            if(strnicmp_dup(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue       += iLen;
            pszCriteria    += iLen;
         }

         if(*pszValue == '\0')
            return false;

         pszCriteria++;
         pszValue++;

      }
      else if(*pszFind == '*')
      {

         if(pszFind > pszCriteria)
         {
            if(strnicmp_dup(pszValue, pszCriteria, iLen) != 0)
               return false;
            pszValue       += iLen;
            pszCriteria    += iLen;
         }

         pszStop = wildcard_next_stop(pszFind + 1);

         if(pszStop == NULL)
            pszStop = pszFind + strlen_dup(pszFind);

         iLen = pszStop - (pszFind + 1);

         pszValue = strnistr_dup(pszValue, pszFind + 1, iLen);

         if(pszValue == NULL)
            return false;

         pszValue       = pszValue + iLen;
         pszCriteria    = pszStop;

      }
      else
      {
         throw "not_expected, check wildcard_next_stop function";
      }


   }

   if(stricmp_dup(pszValue, pszCriteria) != 0)
      return false;

   return true;

}


CLASS_DECL_AURA string get_md5(const char * psz)
{
   return get_md5(psz, strlen(psz));
}

/*
CLASS_DECL_AURA void zero_pad(string & str, count iPad)
{
   while(str.get_length() < iPad)
   {
      str = "0" + str;
   }
}*/




CLASS_DECL_AURA void * memmem_dup(const void * src, strsize srclen, const void * find, strsize findlen)
{

   if(src == NULL)
      return NULL;

   if(find == NULL)
      return src;

   if(findlen <= 0)
      return src;

   strsize i = srclen - findlen;

   if(i < 0)
      return NULL;

   char * psrc = src;

   strsize j;

   for(; i >= 0; i--)
   {

      char * pcmp1 = psrc;

      char * pcmp2 = find;

      for(j = findlen; j > 0; j--)
      {

         if(*pcmp1 != *pcmp2)
            break;

      }

      if(j <= 0)
         return psrc;

      psrc++;
      i--;

   }

   return NULL;

}
