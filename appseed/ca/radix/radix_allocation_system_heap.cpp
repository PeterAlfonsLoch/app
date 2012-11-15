#include "framework.h"

#if defined(MACOS)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif


// DWORD aligned allocation

#ifdef WINDOWSEX

CLASS_DECL_ca HANDLE g_system_heap()
{
   
   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}

#endif

static simple_mutex g_mutexSystemHeap;


CLASS_DECL_ca void * system_heap_alloc(size_t size)
{
   mutex_lock lock(g_mutexSystemHeap, true);
//#if ZEROED_ALLOC
  // byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
//#else  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
#ifdef WINDOWSEX
   byte * p = (byte *) ::HeapAlloc(g_system_heap(), 0, ((size + 4 + sizeof(size_t) + 3) & ~3));
#else
   byte * p = (byte *) ::malloc((size + 4 +  sizeof(size_t)  + 3) & ~3);
#endif
//#endif
   if(p == NULL)
      return NULL;
   ((DWORD *)p)[0] = 0;
   *((size_t *)&((DWORD *)p)[1]) = size;
   int iMod = ((dword_ptr)p) % 4;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 + sizeof(size_t) - iMod];
}


CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(g_mutexSystemHeap, true);
   byte * pOld = (byte *) pvoidOld;
   int iSize = sizeof(size_t);
   int iMod = pOld[- 1 - iSize];
   if(iMod < 1 || iMod > 4)
      return NULL;
   size_t sizeOld = *((size_t *)&((DWORD *) (pOld - iMod - sizeof(size_t)))[1]);
#ifdef WINDOWSEX
   byte * p = (byte *) ::HeapReAlloc(g_system_heap(), 0, pOld - iMod- sizeof(size_t), ((size + 4+  sizeof(size_t)  + 3) & ~3));
#else
   byte * p = (byte *) ::realloc(pOld - iMod, ((size + 4 + 3) & ~3));
#endif
   if(p == NULL)
   {
      byte * pNew = (byte *) system_heap_alloc(size);
      if(pNew == NULL)
      {
         system_heap_free(pvoidOld);
         return NULL;
      }
      memcpy(pNew, pvoidOld, min(size, sizeOld));
//#if ZEROED_ALLOC
  //    if(size > sizeOld)
    //  {
      //   memset(&pNew[sizeOld], 0, size - sizeOld);
      //}
//#endif  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
      system_heap_free(pvoidOld);
      return pNew;
   }
   if(size > sizeOld)
   {
      // memset(&p[sizeOld], 0, ((size + 4 + 3) & ~3) - sizeOld);  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
   }
   ((DWORD *)p)[0] = 0;
   iMod = ((dword_ptr)p) % 4;
   *((size_t *)&((DWORD *)p)[1]) = size;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 + sizeof(size_t) - iMod];
}


CLASS_DECL_ca void system_heap_free(void * pvoid)
{

   mutex_lock lock(g_mutexSystemHeap, true);

   byte * p = (byte *) pvoid;

   int iSize = sizeof(size_t);

   int_ptr iMod = p[- 1 - iSize];

   if(iMod < 1 || iMod > 4)
      return;

#ifdef WINDOWSEX

   if(!::HeapFree(g_system_heap(), 0, p - iMod - sizeof(size_t)))
   {

      DWORD dw = ::GetLastError();

      ::OutputDebugString("system_heap_free : Failed to free memory");

   }

#else

   try
   {

      ::free(p - iMod);

   }
   catch(...)
   {

      ::OutputDebugStringW(L"system_heap_free : Failed to free memory");

   }

#endif

}





