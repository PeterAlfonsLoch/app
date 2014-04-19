#include "framework.h"
#include <unistd.h>


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());
   string strDir(dir::name(strPath));
    

    /*vsstring strPath

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = strPath;
   infoa.lpDirectory    = strDir;*/

    execlp(strPath, strPath, (char *) 0);

   return true;

}