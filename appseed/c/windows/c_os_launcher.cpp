#include "framework.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   vsstring strPath(get_executable_path());
   
   vsstring strDir(dir::name(strPath));

   call_async(strPath, NULL, strDir, SW_HIDE);

   return true;

}