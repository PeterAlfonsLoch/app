#include "framework.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());
   
   string strDir(dir::name(strPath));

   string strParams = get_params();

   call_async(strPath, strParams, strDir, SW_HIDE);

   return true;

}