#include "framework.h"
#include "aura/node/ansios/ansios.h"
#include "linux.h"


namespace linux
{

   int32_t function()
   {
      return 0;
   }


   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));
   }

} // namespace linux




void CLASS_DECL_AURA __lnx_term()
{



}











