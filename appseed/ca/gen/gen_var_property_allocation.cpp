#include "StdAfx.h"


#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)
#undef new


namespace gen
{


   static fixed_alloc g_fixedallocVar(ROUND4(sizeof(var_property) ), 1024);

   void * PASCAL var_property::operator new(size_t size, void * p)
      { 
         UNREFERENCED_PARAMETER(size);
         return p; 
      }

   void * PASCAL var_property::operator new(size_t nSize)
   {
      return g_fixedallocVar.Alloc();
   }

   void * PASCAL var_property::operator new(size_t nSize, const char * lpszFileName, int nLine)
   {
      return g_fixedallocVar.Alloc();
   }


   inline void PASCAL var_property::operator delete(void * p)
   {
      g_fixedallocVar.Free(p);
   }

   inline void PASCAL var_property::operator delete(void * p, void *)
   {
      g_fixedallocVar.Free(p);
   }

   inline void PASCAL var_property::operator delete(void *pvar, const char *, int)
   {
      g_fixedallocVar.Free(pvar);
   }



} // namespace gen


