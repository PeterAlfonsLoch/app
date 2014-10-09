#include "framework.h"

#define PREFER_MALLOC 1

// uint32_t aligned allocation

#ifdef WINDOWSEX

HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}

#endif


mutex * g_pmutexSystemHeap = NULL;


void * system_heap_alloc(size_t size)
{

   synch_lock lock(g_pmutexSystemHeap);

//#if ZEROED_ALLOC
  // byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
//#else  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
   
   void * p;

#if defined(WINDOWSEX) && !defined(PREFER_MALLOC)

   p = ::HeapAlloc(g_system_heap(), 0, size);

#else

   p = ::malloc(size);

#endif
//#endif

   if(p == NULL)
   {

      throw_memory_exception();

   }

   return p;

}


void * system_heap_realloc(void * p, size_t size)
{

   synch_lock lock(g_pmutexSystemHeap);

#if defined(WINDOWSEX) && !defined(PREFER_MALLOC)

   return ::HeapReAlloc(g_system_heap(), 0, p, size);

#else

   return ::realloc(p, size);

#endif

}


void system_heap_free(void * p)
{

   synch_lock lock(g_pmutexSystemHeap);

#if defined(WINDOWSEX) && !defined(PREFER_MALLOC)

   if(!::HeapFree(g_system_heap(), 0, p))
   {

      uint32_t dw = ::GetLastError();

      ::OutputDebugString("system_heap_free : Failed to free memory");

   }

#else

   try
   {

      ::free(p);

   }
   catch(...)
   {

      ::OutputDebugStringW(L"system_heap_free : Failed to free memory");

   }

#endif

}





