#include "framework.h"


CLASS_DECL_c int debug_box_function(const char * pszMessage, const char * pszTitle, int iFlags)
{

   return MessageBox(NULL, pszMessage, pszTitle, iFlags);

}