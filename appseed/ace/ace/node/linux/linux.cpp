#include "framework.h"
#include "ace/node/ansios/ansios.h"
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




void CLASS_DECL_ACE __lnx_term()
{



}











