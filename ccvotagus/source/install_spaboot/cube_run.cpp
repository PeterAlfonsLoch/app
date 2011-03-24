#include "install_spaboot.h"

int cube_run(const char * id)
{

   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage");
#ifdef _X86_
   strcat_dup(lpszDir, "\\x86");
#else
   strcat_dup(lpszDir, "\\x64");
#endif
   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\cubeapp.exe");

   char param[MAX_PATH];

   strcpy_dup(param, ": app=");
   strcat_dup(param, id);

   SHELLEXECUTEINFOA infoa;
      
   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize = sizeof(infoa);
   infoa.lpFile = lpszFile;
   infoa.lpParameters = param;

   ::ShellExecuteExA(&infoa);

   return 0;

}
