#include "StdAfx.h"
#ifdef WINDOWS
#include <Shlobj.h>
#endif

vsstring dir::afterca2()
{
   return ca2();
}

vsstring dir::appdata(const char * lpcsz)
{
   vsstring str;
#ifdef WIN32
   char * buf = (char *) ca2_alloc(4096);
   memset_dup(buf, 0, sizeof(buf));
   SHGetSpecialFolderPath(
      NULL,
      buf,
      CSIDL_COMMON_APPDATA,
      FALSE);
   str = path(buf, "ca2");
   ca2_free(buf);
#endif
   vsstring strCa2 = dir::ca2();
   index iFind = strCa2.find(':');
   if(iFind >= 0)
   {
      int iFind1 = strCa2.rfind('\\', iFind);
      int iFind2 = strCa2.rfind('/', iFind);
      int iStart = max(iFind1 + 1, iFind2 + 1);
      strCa2 = strCa2.substr(0, iFind - 1) + "_" + strCa2.substr(iStart, iFind - iStart) + strCa2.substr(iFind + 1);
   }
   str = path(str, strCa2);
   return path(str, lpcsz);
}
