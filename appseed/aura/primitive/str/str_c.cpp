//#include "framework.h"
////#include "ca/x/x_defines.h"
////#include "ca/x/x_tables.h"
////#include "ca/x/x_charcategory_names.h"
////#include "ca/x/x_charcategory.h"


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
         {
            return ::str::ends(pszValue, pszFind+1);
         }

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


//CLASS_DECL_AURA string get_md5(const char * psz)
//{
//   return get_md5(psz, strlen(psz));
//}

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
      return (void *) src;

   if(findlen <= 0)
      return (void *) src;

   strsize i = srclen - findlen;

   if(i < 0)
      return (void *) NULL;

   char * psrc = (char *) src;

   strsize j;

   for(; i >= 0; i--)
   {

      char * pcmp1 = psrc;

      char * pcmp2 = (char *) find;

      for(j = findlen; j > 0; j--)
      {

         if(*pcmp1 != *pcmp2)
            break;

         pcmp1++;

         pcmp2++;

      }

      if(j <= 0)
         return psrc;

      psrc++;
      i--;

   }

   return NULL;

}


// http://stackoverflow.com/questions/23919515/how-to-convert-from-utf-16-to-utf-32-on-linux-with-std-library

// peppe
// http://stackoverflow.com/users/1873944/peppe

//peppe top 3% this year
//
//Software engineer at KDAB, the Qt experts.
//
//Qt and Linux hacker.
//
//Free Software advocate.
//
//Refined chef.
//

int is_surrogate(unichar uc) { return (uc - 0xd800) < 2048; }
int is_high_surrogate(unichar uc) { return (uc & 0xfffffc00) == 0xd800; }
int is_low_surrogate(unichar uc) { return (uc & 0xfffffc00) == 0xdc00; }

unichar32 surrogate_to_utf32(unichar high, unichar low)
{
   return (high << 10) + low - 0x35fdc00;
}

strsize utf16_to_utf32(unichar32 * output, const unichar *input, strsize input_size)
{

   unichar32 * start = output;

   const unichar * const end = input + input_size;

   while (input < end)
   {

      const unichar uc = *input++;

      if (!is_surrogate(uc))
      {

         *output++ = uc;

      }
      else
      {

         if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
         {

            *output++ = surrogate_to_utf32(uc, *input++);

         }
         else
         {

            throw simple_exception(get_thread_app(), "utf16_to_utf32_len");

         }

      }

   }

   return output - start;

}


strsize utf16_to_utf32_len(const unichar *input, strsize input_size)
{

   const unichar * const end = input + input_size;

   int c = 0;

   while (((input_size < 0) && *input) || ((input_size >= 0) && input < end))
   {

      const unichar uc = *input++;

      if (!is_surrogate(uc))
      {

         c++;

      }
      else
      {

         if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
         {

            c++;

         }
         else
         {

            throw simple_exception(get_thread_app(), "utf16_to_utf32_len");

         }

      }

   }

   return c;

}



unichar32 * utf16_to_utf32(const unichar *input, strsize input_size)
{

   strsize s = utf16_to_utf32_len(input, input_size);

   unichar32 * v = (unichar32 *) memory_alloc(sizeof(unichar32) * (s+1));

   utf16_to_utf32(v, input, s);

   v[s] = 0;

   return v;

}

// http://stackoverflow.com/questions/29433124/how-to-convert-a-codepoint-32bit-integer-array-utf-32-to-windows-native-strin

// http://stackoverflow.com/users/65863/remy-lebeau
//Remy Lebeau
//
//I am a highly visible member of the Embarcadero developer forums, which are public forums for software developers who use Borland/CodeGear/Embarcadero development tools (Delphi, C++Builder, RAD Studio, etc) to talk to each other, help each other out with problems in their projects and source code, and to provide expert advise to each other.
//
//I am a primary member of the development and admin teams for the Internet Direct (Indy) open source project and its support forums and newsgroups.
//
//I am a contributing author to the C++Builder Developer's Journal and its support forums. BCBJ is a monthly online magazine devoted to all things related to the Borland/CodeGear/Embarcadero C++Builder development IDE and compiler.
//6,121 answers
//4 questions
//~5.0m people reached
//
//United States
//lebeausoftware.org
//Member for 6 years, 5 months
//12,656 profile views
//Last seen 2 hours ago
//
//Communities (5)
//
//Stack Overflow 175.2k 175.2k 896198
//Anime & Manga 178 178 5
//Science Fiction & Fantasy 173 173 6
//Meta Stack Exchange 121 121 5
//Cryptography 108 108 4
//
//Top Network Posts
//
//5Is it possible for a genin to become a jonin?
//View more network posts →



// on Windows, wchar_t is 2 bytes, suitable for UTF-16
//std::wstring Utf32ToUtf16(const std::vector<uint32_t> &codepoints)
//{
//   std::wstring result;
//   int len = 0;
//
//   for (std::vector<uint32_t>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//   {
//      uint32_t cp = *iter;
//      if (cp < 0x10000) {
//         ++len;
//      }
//      else if (cp <= 0x10FFFF) {
//         len += 2;
//      }
//      else {
//         // invalid code_point, do something !
//         ++len;
//      }
//   }
//
//   if (len > 0)
//   {
//      result.resize(len);
//      len = 0;
//
//      for (std::vector<uint32_t>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//      {
//         uint32_t cp = *iter;
//         if (cp < 0x10000) {
//            result[len++] = static_cast<wchar_t>(cp);
//         }
//         else if (cp <= 0x10FFFF) {
//            cp -= 0x10000;
//            result[len++] = static_cast<wchar_t>((cp >> 10) + 0xD800);
//            result[len++] = static_cast<wchar_t>((cp & 0x3FF) + 0xDC00);
//         }
//         else {
//            result[len++] = static_cast<wchar_t>(0xFFFD);
//         }
//      }
//   }
//
//   return result;
//}

strsize utf32_to_utf8_len(const unichar32 * pwsz, strsize input_size)
{
   if(pwsz == NULL)
      return -1;
   int32_t len = 0;
   int32_t n;
   char sz[16];
   while(input_size != 0 && *pwsz != L'\0')
   {
      n = uni_to_utf8(sz,*pwsz);
      if(n <= 0)
         break;
      len += n;
      input_size--;
      pwsz++;
   }
   return len;
}

strsize utf32_to_utf8(char * psz,const unichar32 * pwsz, strsize srclen)
{
   //unsigned short * pwsz = (unsigned short *)pwszParam;
   strsize c = 0;
   int32_t n;
   while(srclen != 0 && *pwsz != L'\0')
   {
      n = uni_to_utf8(psz,*pwsz);
      if(n <= 0)
         break;
      c+=n;
      pwsz++;
      psz += n;
      srclen--;
   }

   *psz = L'\0';
   return c;
}

string utf32_to_utf8(const unichar32 *input, strsize input_size)
{

   strsize s = utf32_to_utf8_len(input, input_size);

   string str;

   char * p = str.GetBufferSetLength(s);

   utf32_to_utf8(p, input, s);

   p[s] = 0;

   return str;

}

strsize utf8_to_utf32_len(const char * psz, strsize srclen)
{

   strsize len;

   while(srclen != 0 && psz != NULL && *psz != '\0')
   {

      ::str::ch::uni_index_len(psz, len);

      psz += len;

      srclen--;

   }

   return len;

}

strsize utf8_to_utf32(unichar32 * pwsz,const char * psz, strsize srclen)
{

   strsize len;

   while(srclen != 0 && psz != NULL && *psz != '\0')
   {

      *pwsz++ = ::str::ch::uni_index_len(psz,len);

      psz += len;

      srclen -= len;

   }

   if(psz != NULL)
   {

      *pwsz = L'\0';

   }

   return len;

}




unichar32 * utf8_to_utf32(const char *input, strsize input_size)
{

   strsize s = utf8_to_utf32_len(input, input_size);

   unichar32 * v = (unichar32 *) memory_alloc(sizeof(unichar32) * (s+1));

   utf8_to_utf32(v, input, s);

   v[s] = 0;

   return v;

}



strsize utf32_to_utf16_len(const unichar32 * codepoints, strsize input_size)
{

   strsize len = 0;

   while(input_size != 0)
   {

      uint32_t cp = *codepoints++;

      input_size--;

      if(cp == 0)
         break;

      if (cp < 0x10000)
      {

         ++len;

      }
      else if (cp <= 0x10FFFF)
      {

         len += 2;

      }
      else
      {

         // invalid code_point, do something !
         throw simple_exception(::get_thread_app(), "utf32_to_utf16_len :: invalid code_point, do something ! ");

         ++len;

      }

   }

   return len;

}


strsize utf32_to_utf16(unichar * p, const unichar32 * codepoints, strsize input_size)
{

   strsize len = 0;

   while(input_size != 0)
   {

      uint32_t cp = *codepoints++;

      input_size--;

      if(cp == 0)
         break;

      if (cp < 0x10000)
      {

         *p++ = static_cast<unichar>(cp);

      }
      else if (cp <= 0x10FFFF)
      {

         cp -= 0x10000;

         *p++ = static_cast<unichar>((cp >> 10) + 0xD800);

         *p++ = static_cast<unichar>((cp & 0x3FF) + 0xDC00);

      }
      else
      {

         *p++ = static_cast<unichar>(0xFFFD);

      }

   }

   return len;

}


wstring utf32_to_utf16(const unichar32 *input, strsize input_size)
{

   strsize s = utf32_to_utf16_len(input, input_size);

   wstring wstr;

   unichar * p = wstr.alloc(s);

   utf32_to_utf16(p, input, s);

   p[s] = 0;

   return wstr;

}

#ifdef WINDOWS
CLASS_DECL_AURA string w_to_8(const wchar_t * pcwsz, strsize input_size)
{
   return utf16_to_utf8(pcwsz, input_size);
}
#else
CLASS_DECL_AURA string w_to_8(const wchar_t * pcwsz, strsize input_size)
{
   return utf32_to_utf8(pcwsz, input_size);
}
#endif



