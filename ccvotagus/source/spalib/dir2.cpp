#include "StdAfx.h"

std::string dir::afterca2()
{
   return ca2().c_str();
}

std::string dir::appdata(const char * lpcsz)
{
   std::string str;
#ifdef WIN32
   char buf[4096];
   memset(buf, 0, sizeof(buf));
   SHGetSpecialFolderPath(
      NULL,
      buf,
      CSIDL_COMMON_APPDATA,
      FALSE);
   str = path(buf, "ca2");
#endif
   str = path(str.c_str(), "appdata");
   return path(str.c_str(), lpcsz);
}
