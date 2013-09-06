#include "framework.h"


int32_t cube_run(const char * id)
{

   string strDir;
   string strFile;

#ifdef X86

   strDir = dir::element("\\stage\\x86");

#else

   strDir = dir::element("\\stage\\x64");

#endif

   strFile = strDir;
   strFile += "\\app.exe";

   string strParam;

   strParam = ": app=";
   strParam += id;

#ifdef METROWIN

   throw "todo";

#else

   call_async(strFile, strParam, strDir, SW_SHOW);

#endif

   return 0;

}

