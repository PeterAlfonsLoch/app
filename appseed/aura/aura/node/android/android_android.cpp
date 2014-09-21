#include "framework.h"
#include "android.h"
#include "android1.h"




void CLASS_DECL_AURA __abort()
{
   //__android_term();
   abort();
}





#ifdef DEBUG
bool CLASS_DECL_AURA __check_memory()
// check all of primitive::memory (look for primitive::memory tromps)
{
   //return _CrtCheckMemory() != FALSE;
   return true;
}
#endif


























namespace android
{

   int32_t function()
   {
      return 0;
   }


   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8,::str::international::utf8_to_unicode(str,MAX_PATH * 8));
   }

} // namespace android



