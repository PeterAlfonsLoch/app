#include "framework.h"


#undef new


fixed_alloc * g_pfixedallocVar = NULL;

void * var::operator new(size_t size, void * p)
   { 
      UNREFERENCED_PARAMETER(size);
      return p; 
   }

void * var::operator new(size_t nSize)
{
   return g_pfixedallocVar->Alloc();
}

#ifdef DEBUG

void * var::operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
{
   return g_pfixedallocVar->Alloc();
}

#endif

inline void var::operator delete(void * p)
{
   g_pfixedallocVar->Free(p);
}

#ifdef DEBUG

inline void var::operator delete(void * p, void *)
{
   g_pfixedallocVar->Free(p);
}

inline void var::operator delete(void *pvar, const char *, int32_t)
{
   g_pfixedallocVar->Free(pvar);
}

#endif