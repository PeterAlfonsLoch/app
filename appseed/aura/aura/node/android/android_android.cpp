#include "framework.h"



void CLASS_DECL_AURA __abort()
{
   __android_term();
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























