#include "framework.h"

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)
#undef new


static fixed_alloc g_fixedallocVar(ROUND4(sizeof(var) ), 1024);

void * var::operator new(size_t size, void * p)
   { 
      UNREFERENCED_PARAMETER(size);
      return p; 
   }

void * var::operator new(size_t nSize)
{
   return g_fixedallocVar.Alloc();
}

#ifdef DEBUG

void * var::operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
{
   return g_fixedallocVar.Alloc();
}

#endif

inline void var::operator delete(void * p)
{
   g_fixedallocVar.Free(p);
}

#ifdef DEBUG

inline void var::operator delete(void * p, void *)
{
   g_fixedallocVar.Free(p);
}

inline void var::operator delete(void *pvar, const char *, int32_t)
{
   g_fixedallocVar.Free(pvar);
}

#endif