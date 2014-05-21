#include "framework.h"


#include "framework.h"


// Note: in separate module so it can be replaced if needed

void CLASS_DECL_BASE __abort()
{
   //   TRACE(::ca2::trace::category_AppMsg, 0, "AfxAbort called.\n");

   __android_term();
   abort();
}

/////////////////////////////////////////////////////////////////////////////









#ifdef DEBUG
bool CLASS_DECL_BASE __check_memory()
// check all of primitive::memory (look for primitive::memory tromps)
{
   return _CrtCheckMemory() != FALSE;
}
#endif























void CLASS_DECL_BASE __android_term()
{
}

