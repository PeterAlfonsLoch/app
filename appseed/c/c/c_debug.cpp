#include "framework.h"


CLASS_DECL_c int FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int iFlags)
{

   return MessageBox(NULL, pszMessage, pszTitle, iFlags);

}