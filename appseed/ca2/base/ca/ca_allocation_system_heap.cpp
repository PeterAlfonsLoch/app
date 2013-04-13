#include "framework.h"


// uint32_t aligned allocation

#ifdef WINDOWSEX

CLASS_DECL_ca2 HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}

#endif

static simple_mutex g_mutexSystemHeap;


CLASS_DECL_ca2 void * system_heap_alloc(size_t size)
{

   mutex_lock lock(g_mutexSystemHeap, true);

   size_t sizeAlloc = (size + 4 + sizeof(size_t) + 3) & ~3;

//#if ZEROED_ALLOC
  // byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
//#else  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
#ifdef WINDOWSEX

   byte * p = (byte *) ::HeapAlloc(g_system_heap(), 0, sizeAlloc);

#else

   byte * p = (byte *) ::malloc(sizeAlloc);

#endif
//#endif

   if(p == ::null())
      return ::null();

   ((uint32_t *)p)[0] = 0;

   *((size_t *)&((uint32_t *)p)[1]) = size;

   int32_t iMod = ((uint_ptr)p) % 4;

   p[3 - iMod] = (uint8_t) (4 - iMod);

   return &p[4 + sizeof(size_t) - iMod];

}


CLASS_DECL_ca2 void * system_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(g_mutexSystemHeap, true);
   byte * pOld = (byte *) pvoidOld;
   int32_t iSize = sizeof(size_t);
   int32_t iMod = pOld[- 1 - iSize];
   if(iMod < 1 || iMod > 4)
      return ::null();
   size_t sizeOld = *((size_t *)&((uint32_t *) (pOld - iMod - sizeof(size_t)))[1]);
#ifdef WINDOWSEX
   byte * p = (byte *) ::HeapReAlloc(g_system_heap(), 0, pOld - iMod- sizeof(size_t), ((size + 4+  sizeof(size_t)  + 3) & ~3));
#else
   byte * p = (byte *) ::realloc(pOld - iMod- sizeof(size_t), ((size + 4 +  sizeof(size_t) + 3) & ~3));
#endif
   if(p == ::null())
   {
      byte * pNew = (byte *) system_heap_alloc(size);
      if(pNew == ::null())
      {
         system_heap_free(pvoidOld);
         return ::null();
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
   ((uint32_t *)p)[0] = 0;
   iMod = ((uint_ptr)p) % 4;
   *((size_t *)&((uint32_t *)p)[1]) = size;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 + sizeof(size_t) - iMod];
}


CLASS_DECL_ca2 void system_heap_free(void * pvoid)
{

   mutex_lock lock(g_mutexSystemHeap, true);

   byte * p = (byte *) pvoid;

   int32_t iSize = sizeof(size_t);

   int_ptr iMod = p[- 1 - iSize];

   if(iMod < 1 || iMod > 4)
      return;

#ifdef WINDOWSEX

   if(!::HeapFree(g_system_heap(), 0, p - iMod - sizeof(size_t)))
   {

      uint32_t dw = ::GetLastError();

      ::OutputDebugString("system_heap_free : Failed to free memory");

   }

#else

   try
   {

      ::free(p - iMod - sizeof(size_t));

   }
   catch(...)
   {

      ::OutputDebugStringW(L"system_heap_free : Failed to free memory");

   }

#endif

}





