#include "framework.h"


int_bool file_copy_dup(const char * pszDup, const char * pszSrc) // , bool bOverwrite = true)
{

   return file_copy_dup(pszDup, pszSrc, true);

}


int_bool file_put_contents_dup(const char * path, const char * contents)
{

   return file_put_contents_dup(path, contents, strlen(contents));

}
