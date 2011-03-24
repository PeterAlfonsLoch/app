#include "version.h"

#include <stdio.h>
#include <time.h>

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

   if(lpCmdLine[0] != '\0')
   {
      FILE * f = _wfopen(lpCmdLine, L"w");
      fputs("// CarlosGustavoCecynLundgren1984+kaarurosu\n", f);
      fputs("// < Thanks and dedicated to\n", f);
      fputs("// Thanks to and in honor of God.\n", f);
      fputs("// for ca2 and 5!!\n", f);
      fputs("// you(1) and me(2) and God(345) make 5...\n", f);
      fputs("\n", f);
      fputs("#include \"StdAfx.h\"\n", f);
      fputs("\n", f);
      char szModuleVersion[1024];
      time_t t = time(NULL);
      tm * ptm = ::gmtime(&t);
      sprintf(szModuleVersion, "_declspec(dllexport) void ca2_get_module_version(char * psz)\n{\n   const char * pszSrc = \"%08d-%02d-%02d %02d-%02d-%02d\";\n   while(*pszSrc != '\\0')\n      *psz++ = *pszSrc++;\n}\n", 
         ptm->tm_year + 1900,
         ptm->tm_mon + 1,
         ptm->tm_mday,
         ptm->tm_hour,
         ptm->tm_min,
         ptm->tm_sec);
      fputs(szModuleVersion, f);
      fclose(f);
   }

	return (int) 0;
}



