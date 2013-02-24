#include "framework.h"


int32_t cube_run(const char * id)
{

   vsstring strDir;
   vsstring strFile;

#ifdef X86

   strDir = dir::ca("\\stage\\x86");

#else

   strDir = dir::ca("\\stage\\x64");

#endif

   strFile = strDir;
   strFile += "\\app.exe";

   vsstring strParam;

   strParam = ": app=";
   strParam += id;

#ifdef METROWIN

   throw "todo";

#else

   call_async(strFile, strParam, strDir, SW_SHOW);

#endif

   return 0;

}

