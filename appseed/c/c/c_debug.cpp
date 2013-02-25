#include "framework.h"


CLASS_DECL_c int32_t FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags)
{

   return MessageBox(::ca::null(), pszMessage, pszTitle, iFlags);

}
