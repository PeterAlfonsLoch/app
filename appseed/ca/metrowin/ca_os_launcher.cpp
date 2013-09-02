#include "framework.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   vsstring strPath(get_executable_path());
   
   vsstring strDir(dir::name(strPath));

   vsstring strParams = get_params();

#ifdef METROWIN

   throw "todo";

#else

   call_async(strPath, strParams, strDir, SW_HIDE);

#endif

   return true;

}