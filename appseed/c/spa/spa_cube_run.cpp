#include "StdAfx.h"

int cube_run(const char * id)
{

   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) ca2_alloc(iLenBuf);

   strcpy_dup(lpszDir, dir::ca2());
   strcat_dup(lpszDir, "\\stage");
#ifdef _X86_
   strcat_dup(lpszDir, "\\x86");
#else
   strcat_dup(lpszDir, "\\x64");
#endif
   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\aaaaaaplication.exe");

   char param[MAX_PATH];

   strcpy_dup(param, ": app=");
   strcat_dup(param, id);

   #if defined(_WINDOWS)

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize            = sizeof(infoa);
   infoa.lpFile            = lpszFile;
   infoa.lpParameters      = param;
#ifdef _X86_
   infoa.lpDirectory       = dir::ca2("stage\\x86");
#else
   infoa.lpDirectory       = dir::ca2("stage\\x64");
#endif


   ::ShellExecuteExA(&infoa);
   #else

      throw 0;

   #endif

   return 0;

}
