#include "framework.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   vsstring strPath(get_executable_path());
   
   vsstring strDir(dir::name(strPath));

   vsstring strParams = get_params();

   call_async(strPath, strParams, strDir, SW_HIDE);

   return true;

}