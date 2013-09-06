#include "framework.h"


int_bool file_copy_dup(const char * pszDup, const char * pszSrc) // , bool bOverwrite = true)
{

   return file_copy_dup(pszDup, pszSrc, true);

}
