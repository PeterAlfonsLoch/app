#include "framework.h"


int cube_run(const char * id)
{

   vsstring strDir;
   vsstring strFile;

#ifdef _X86_
   strDir = dir::ca2("\\stage\\x86");
#else
   strDir = dir::ca2("\\stage\\x64");
#endif

   strFile = strDir;
   strFile += "\\app.exe";

   vsstring strParam;

   strParam = ": app=";
   strParam += id;

   call_async(strFile, strParam, strDir, SW_SHOW);

   return 0;

}

