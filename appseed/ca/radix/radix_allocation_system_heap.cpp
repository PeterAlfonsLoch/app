#include "framework.h"


// DWORD aligned allocation

#ifdef WINDOWS
static HANDLE g_hSystemHeap = ::HeapCreate(0, 0, 0);
#endif

static simple_mutex g_mutexSystemHeap;


CLASS_DECL_ca void * system_heap_alloc(size_t size)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
//#if ZEROED_ALLOC
  // byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
//#else  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
#ifdef WINDOWS
   byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, 0, ((size + 4 + 3) & ~3));
#else
   byte * p = (byte *) ::malloc((size + 4 + 3) & ~3);
#endif
//#endif
   if(p == NULL)
      return NULL;
   ((DWORD *)p)[0] = 0;
   int iMod = ((dword_ptr)p) % 4;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 - iMod];
}


CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
   byte * pOld = (byte *) pvoidOld;
   int iMod = pOld[-1];
   if(iMod < 1 || iMod > 4)
      return NULL;
#ifdef WINDOWS
   size_t sizeOld = ::HeapSize(g_hSystemHeap, 0, pOld - iMod);
   byte * p = (byte *) ::HeapReAlloc(g_hSystemHeap, 0, pOld - iMod, ((size + 4 + 3) & ~3));
#else
   size_t sizeOld = ::malloc_size(pOld - iMod);
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
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 - iMod];
}


CLASS_DECL_ca void system_heap_free(void * pvoid)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
   byte * p = (byte *) pvoid;
   int iMod = p[-1];
   if(iMod < 1 || iMod > 4)
      return;
#ifdef WINDOWS
   if(!::HeapFree(g_hSystemHeap, 0, p - iMod))
#else
   if(!::free(p - iMod))
#endif
   {
      DWORD dw = ::GetLastError();
      ::OutputDebugString("system_heap_free : Failed to free memory");
   }
}





