#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <string>
#include <stdio.h>
#include <math.h>

#define NULWCHAR     L'\0'
#define TABWCHAR     L'\t'
#define SLASHWCHAR   L'\\'
#define SPACEWCHAR   L' '
#define DQUOTEWCHAR  L'\"'

void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    )
{
        WCHAR *p;
        WCHAR c;
        int inquote;                    /* 1 = inside quotes */
        int copychar;                   /* 1 = copy char to *args */
        unsigned numslash;              /* num of backslashes seen */

        *numchars = 0;
        *numargs = 1;                   /* the program name at least */

        /* first scan the program name, copy it, and count the bytes */
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
           between the leading double-quote and next one, or a terminal null
           character is simply accepted. Fancier handling is not required
           because the program name must be a legal NTFS/HPFS file name.
           Note that the double-quote characters are not copied, nor do they
           contribute to numchars. */
        if ( *p == DQUOTEWCHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a null, whichever comes first */
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
            /* append the terminating null */
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
                /* count number of backslashes for use below */
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

            /* null-terminate the argument */

            if (args)
                *args++ = NULWCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a null ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}



WCHAR * utf8_to_16(const char * psz)
{
   int iCount = MultiByteToWideChar(
		CP_UTF8,
		0,
		psz,
		-1,
		NULL,
		0);
   WCHAR * pwz = new WCHAR[iCount + 1];
   MultiByteToWideChar(
		CP_UTF8,
		0,
		psz,
		-1,
		pwz,
		iCount);
   return pwz;
}

CHAR * utf16_to_8(const wchar_t * psz)
{
   int iCount = WideCharToMultiByte(
		CP_UTF8,
		0,
		psz,
		-1,
		NULL,
		0,
      NULL,
      NULL);
   CHAR * pwz = new CHAR[iCount + 1];
   WideCharToMultiByte(
		CP_UTF8,
		0,
		psz,
		-1,
		pwz,
		iCount,
      NULL,
      NULL);
   return pwz;
}

std::string salt()
{
   srand(::GetTickCount());
   int iMod = 2;
   int iRoundRandomSize = 16;
   int iRoundSize = iRoundRandomSize + iMod;
   int iRoundRepeat = 8;
   int iTotalSize = iRoundSize * iRoundRepeat;
   std::string strSalt;
   char sz[1024];
   int s1;
   int s2;
   int s5;
   int s8;
   for(int i = 0; i < iTotalSize; i++)
   {
      int iShare = (i % iRoundSize);
      if(iShare >= iMod)
      {
         iShare = rand() % iMod;
      }
      s1 = max(1, rand());
      s2 = max(2, rand());
      s5 = max(5, rand());
      s8 = max(8, rand());
      sprintf(sz, "M%02d(%d, %d, %d, %d)\r\n", iShare, s1, s2, s5, s8);
      strSalt += sz;
   }
   return strSalt;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   wchar_t * lpwstr = ::GetCommandLineW();
   int numargs;
   int numchars;
   wparse_cmdline(
      lpwstr, 
      NULL, 
      NULL,
      &numargs,
      &numchars);

   wchar_t * pszCmdLine = new WCHAR[numchars];
   wchar_t ** argv = new WCHAR*[numargs];

   wparse_cmdline(
      lpwstr, 
      argv, 
      pszCmdLine,
      &numargs,
      &numchars);

   if(numargs >= 2)
   {
      std::string strSalt(utf16_to_8(argv[3]));
      FILE * f = fopen(utf16_to_8(argv[1]), "wb");
      if(!f)
         return -1;
      fwrite(strSalt.c_str(), 1, strSalt.length(), f);
      fclose(f);
   }
   ::CreateProcess(NULL, "svn commit \"C:\\telmico\\production\\app\"", NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL);
   return 0;
}


