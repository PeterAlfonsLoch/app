#include "framework.h"


#define PREFER_MALLOC 1


// uint32_t aligned allocation

#if defined(WINDOWSEX) && !defined(__VLD) && !defined(__MCRTDBG)

HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}

#endif

critical_section * g_pmutexSystemHeap = NULL;


BEGIN_EXTERN_C


#if defined(WINDOWSEX) && !PREFER_MALLOC  && !(defined(__VLD) || defined(__MCRTDBG))


void * os_alloc(size_t size)
{

   cslock csl(g_pmutexSystemHeap);

   return ::HeapAlloc(g_system_heap(), 0, size);

   return  malloc(size);

}


void * os_realloc(void * p,size_t size)
{


   cslock lock(g_pmutexSystemHeap);

   return ::HeapReAlloc(g_system_heap(), 0, p, size);



}


void os_free(void * p)
{


   cslock lock(g_pmutexSystemHeap);


   if (!::HeapFree(g_system_heap(), 0, p))
   {

      uint32_t dw = ::GetLastError();

      ::OutputDebugString("system_heap_free : Failed to free memory");

   }

}


#else


void * os_alloc(size_t size)
{

   return  malloc(size);

}


void * os_realloc(void * p, size_t size)
{


   return realloc(p, size);

}


void os_free(void * p)
{


   free(p);

}


#endif


END_EXTERN_C






