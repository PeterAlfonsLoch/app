//#include "framework.h"

#define PREFER_MALLOC 0

// uint32_t aligned allocation

#ifdef WINDOWSEX

HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}

#endif


critical_section * g_pmutexSystemHeap = NULL;


void * system_heap_alloc(size_t size)
{
   
   if(size > 16 * 1024)
   {

      ::OutputDebugStringA("allocating memory block greater than 16kb\n");
      
   }

   //synch_lock lock(g_pmutexSystemHeap);

//#if ZEROED_ALLOC
  // byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
//#else  // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
   
   void * p;

#if defined(WINDOWSEX) && !PREFER_MALLOC

   cslock csl(g_pmutexSystemHeap);

   p = ::HeapAlloc(g_system_heap(), 0, size);

#else

   p = ::malloc(size);
   
#endif
//#endif

   if(p == NULL)
   {

      throw_memory_exception();

   }
   
   memset(p, 0x00, size);

   return p;

}


void * system_heap_realloc(void * p, size_t size)
{

#if defined(WINDOWSEX) && !PREFER_MALLOC

   cslock lock(g_pmutexSystemHeap);

   return ::HeapReAlloc(g_system_heap(), 0, p, size);

#else

   return ::realloc(p, size);

#endif

}


void system_heap_free(void * p)
{

#if defined(WINDOWSEX) && !PREFER_MALLOC

   cslock lock(g_pmutexSystemHeap);

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

      ::output_debug_string("system_heap_free : Failed to free memory");

   }

#endif

}





