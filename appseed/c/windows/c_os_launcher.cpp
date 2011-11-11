#include "StdAfx.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   vsstring strPath(get_executable_path());
   vsstring strDir(dir::name(strPath));

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = strPath;
   infoa.lpDirectory    = strDir;

   ::ShellExecuteExA(&infoa);

   return true;

}