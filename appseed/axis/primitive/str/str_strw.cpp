#include "framework.h"




::count wcslen_dup(const wchar_t * str)
{

   if(str == NULL)
      return 0;

   const wchar_t * pszEnd = str;

   while(*pszEnd != 0)
      pszEnd++;

   return pszEnd - str;

}

int32_t iswalpha_dup(int32_t ch)
{
   return (ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z');
}


int32_t iswdigit_dup(int32_t ch)
{
   return ch >= L'0' && ch <= L'9';
}


int32_t iswspace_dup(int32_t ch)
{
   return ch == L' ' || ch == L'\t' || ch == L'\r' || ch == L'\n' || ch == L'\t';
}


int32_t wcsicmp_dup(const wchar_t * sz1, const wchar_t * sz2)
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
   while(*sz1 != L'\0' && *sz2 != L'\0')
   {
      iCmp = w_to_lower(*sz1) - w_to_lower(*sz2);
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return iCmp;
}

int32_t wcscmp_dup(const wchar_t * sz1, const wchar_t * sz2)
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
   while(*sz1 != L'\0' && *sz2 != L'\0')
   {
      iCmp = *sz1 - *sz2;
      if(iCmp != 0)
         return iCmp;
      sz1++;
      sz2++;
   }
   return iCmp;
}




errno_t wcslwr_s_dup(wchar_t * sz, size_t size)
{

        while(size > 0 && *sz != L'\0')
        {
            *sz = w_to_lower(*sz);
            size--;
            sz++;
        }


        return 0;

}


errno_t wcsupr_s_dup(wchar_t * sz, size_t size)
{

        while(size > 0 && *sz != L'\0')
        {
            *sz = w_to_lower(*sz);
            size--;
            sz++;
        }


        return 0;

}


int32_t iswalnum_dup(int32_t wch)
{
   if(wch >= 256 || wch <= -128)
      return 0;
   return isdigit_dup(wch) || isalpha_dup(wch);
}


wchar_t * wcschr_dup(const wchar_t * sz, wchar_t ch)
{
   if(sz == NULL)
      return NULL;
   while(true)
   {
      if(*sz == ch)
         return (wchar_t *) sz;
      if(*sz == L'\0')
         return NULL;
      sz++;
   }
}


#define NULWCHAR     L'\0'
#define TABWCHAR     L'\t'
#define SLASHWCHAR   L'\\'
#define SPACEWCHAR   L' '
#define DQUOTEWCHAR  L'\"'





void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, int32_t * numargs, int32_t * numchars)
{
        WCHAR *p;
        WCHAR c;
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
        if ( *p == DQUOTEWCHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a NULL, whichever comes first */
            while ( (*(++p) != DQUOTEWCHAR) && (*p != NULWCHAR) ) {

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
                *args++ = NULWCHAR;

            /* if we stopped on a double-quote (usual case), skip over it */
            if ( *p == DQUOTEWCHAR )
                p++;
        }
        else {
            /* Not a quoted program name */
            do {
                ++*numchars;
                if (args)
                    *args++ = *p;

                c = (WCHAR) *p++;
/*#ifdef _MBCS
                if (_ismbblead(c)) {
                    ++*numchars;
                    if (args)
                        *args++ = *p;   /* copy 2nd byte too */
    //                p++;  /* skip over trail byte */
  //              }
//#endif  /* _MBCS */

            } while ( c != SPACEWCHAR && c != NULWCHAR && c != TABWCHAR );

            if ( c == NULWCHAR ) {
                p--;
            } else {
                if (args)
                    *(args-1) = NULWCHAR;
            }
        }

        inquote = 0;

        /* loop on each argument */
        for(;;) {

            if ( *p ) {
                while (*p == SPACEWCHAR || *p == TABWCHAR)
                    ++p;
            }

            if (*p == NULWCHAR)
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
            while (*p == SLASHWCHAR) {
                /* ::count number of backslashes for use below */
                ++p;
                ++numslash;
            }
            if (*p == DQUOTEWCHAR) {
                /* if 2N backslashes before, start/end quote, otherwise
                    copy literally */
                if (numslash % 2 == 0) {
                    if (inquote) {
                        if (p[1] == DQUOTEWCHAR)
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
                    *args++ = SLASHWCHAR;
                ++*numchars;
            }

            /* if at end of arg, break loop */
            if (*p == NULWCHAR || (!inquote && (*p == SPACEWCHAR || *p == TABWCHAR)))
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
                *args++ = NULWCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a NULL ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}








void wcscat_dup(wchar_t * dest, const wchar_t * cat)
{
   if(dest == NULL)
      return;
   if(cat == NULL)
      return;
   while(*dest != 0)
      dest++;
   while(*cat != 0)
      *dest++ = *cat++;
   *dest = L'\0';
}





void uitow_dup(wchar_t * sz, uint32_t ui, int32_t iAxis)
{
   if(ui == 0)
   {
      sz[0] = L'0';
      sz[1] = L'\0';
      return;
   }
   int32_t iIndex = 0;
   while(ui > 0)
   {
      int32_t iDigit = (ui % iAxis);
      wchar_t wch;
      if(iDigit <= 9)
      {
         wch = iDigit + L'0';
      }
      else
      {
         wch = iDigit - 10 + L'a';
      }
      sz[iIndex] =  wch;
      ui = ui / iAxis;
      iIndex++;
   }
   sz[iIndex] = L'\0';
   wcs_reverse(sz);
}



void itow_dup(wchar_t * sz, int32_t i, int32_t iAxis)
{
   if(i == 0)
   {
      sz[0] = L'0';
      sz[1] =  L'\0';
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
      int32_t iDigit = (i % iAxis);
      wchar_t wch;
      if(iDigit <= 9)
      {
         wch = iDigit + L'0';
      }
      else
      {
         wch = iDigit - 10 + L'a';
      }
      sz[iIndex] =  wch;
      i = i / iAxis;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = L'-';
      iIndex++;
   }
   sz[iIndex] = L'\0';
   wcs_reverse(sz);
}




void wcs_reverse(wchar_t * sz)
{

   ::count iLen = wcslen_dup(sz);

   ::count iMid = iLen / 2;

   ::count iL = 0;

   ::count iR = iLen - 1;

   wchar_t ch;

   for(; iL < iMid; iL++, iR--)
   {
      ch = sz[iL];
      sz[iL] = sz[iR];
      sz[iR] = ch;
   }

}

void w_zero_pad(wchar_t * sz, ::count iPad)
{

   ::count iLen = wcslen_dup(sz);

   ::count iZeroCount = iPad - iLen;

   if(iZeroCount > 0)
   {

      ::count iEnd = iLen - 1;

      ::count iFinalEnd = iEnd + iZeroCount;

      sz[iFinalEnd + 1] = L'\0';

      for(; iEnd >= 0; iEnd--, iFinalEnd--)
      {
         sz[iFinalEnd] = sz[iEnd];
      }

      for(; iFinalEnd >= 0; iFinalEnd--)
      {
         sz[iFinalEnd] = L'0';
      }

   }

}



