#include "framework.h"


void strcpy_dup(char * dest, const char * cpy)
{
   if(cpy != NULL && dest != NULL)
   {
      strcpy(dest, cpy);
   }
   //*dest = '\0';
}

void strncpy_dup(char * dest, const char * cpy, ::count iLen)
{
   while(*cpy != 0 && iLen-- > 0)
      *dest++ = *cpy++;
}

void wcsncpy_dup(wchar_t * dest, const wchar_t * cpy, ::count iLen)
{
   while(*cpy != 0 && iLen-- > 0)
      *dest++ = *cpy++;
}

::count strlen_dup(const char * str)
{
   if(str == NULL)
      return 0;
   return strlen(str);
/*   const char * pszEnd = str;
   while(*pszEnd != 0)
      pszEnd++;
   return pszEnd - str;*/
}

char * strdup_dup(const char * src)
{

   ::count iLen = strlen_dup(src);

   char * dup = (char *) memory_alloc(iLen + 1);

   strcpy_dup(dup, src);

   return dup;

}

char * strndup_dup(const char * src, ::count iLen)
{
   char * dup = (char *) memory_alloc(iLen + 1);
   strncpy_dup(dup, src, iLen);
   dup[iLen] = '\0';
   return dup;
}


void wcscpy_dup(wchar_t * dest, const wchar_t * cpy)
{
   while(*cpy != 0)
      *dest++ = *cpy++;
   *dest = L'\0';
}

