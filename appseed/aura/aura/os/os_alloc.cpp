#include "framework.h"


#define PREFER_MALLOC 0


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


void * os_impl_alloc(size_t size)
{

   cslock csl(g_pmutexSystemHeap);

   return ::HeapAlloc(g_system_heap(), 0, size);

   return  malloc(size);

}


void * os_impl_realloc(void * p, size_t size)
{


   cslock lock(g_pmutexSystemHeap);

   return ::HeapReAlloc(g_system_heap(), 0, p, size);



}


void os_impl_free(void * p)
{


   cslock lock(g_pmutexSystemHeap);


   if (!::HeapFree(g_system_heap(), 0, p))
   {

      uint32_t dw = ::GetLastError();

      ::OutputDebugString("system_heap_free : Failed to free memory");

   }

}


#else


void check_bounds(byte * p)
{



   uint_ptr * pui = (uint_ptr *)p;

   byte a[256];

   ZERO(a);

   if (memcmp(&p[sizeof(uint_ptr)], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption before allocation");

   }
   if (memcmp(&p[sizeof(uint_ptr) + 256 + *pui], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption after allocation");

   }

}

void * os_alloc(size_t size)
{

   return malloc(size);

}


void * os_impl_realloc(void * p, size_t size)
{
   
   return realloc(p, size);

}


void os_impl_free(void * p)
{

   free(p);

}


#endif

#ifndef BOUNDS_CHECK
#define BOUNDS_CHECK 0
#else


#if BOUNDS_CHECK


void os_alloc_check_bounds(byte * p)
{



   uint_ptr * pui = (uint_ptr *)p;

   byte a[256];

   ZERO(a);

   if (memcmp(&p[sizeof(uint_ptr)], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption before allocation");

   }
   if (memcmp(&p[sizeof(uint_ptr) + 256 + *pui], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption after allocation");

   }

}

void * os_alloc(size_t size)
{

   cslock sl(g_pmutexSystemHeap);

   byte * p = (byte *)os_impl_alloc(size + 512 + sizeof(uint_ptr));

   memset(&p[sizeof(uint_ptr)], 0, 256);

   memset(&p[sizeof(uint_ptr) + 256 + size], 0, 256);

   uint_ptr * pui = (uint_ptr *)p;

   *pui = size;

   return &p[sizeof(uint_ptr) + 256];


}


void * os_realloc(void * pParam, size_t size)
{
   
   cslock sl(g_pmutexSystemHeap);

   byte * p = &((byte *)pParam)[-(int_ptr)((sizeof(uint_ptr) + 256))];

   os_alloc_check_bounds(p);

   p = (byte *)os_impl_realloc(p, size + 512 + sizeof(uint_ptr));

   memset(&p[sizeof(uint_ptr)], 0, 256);

   memset(&p[sizeof(uint_ptr) + 256 + size], 0, 256);

   uint_ptr * pui = (uint_ptr *)p;

   *pui = size;

   return &p[sizeof(uint_ptr) + 256];

}


void os_free(void * pParam)
{

   cslock sl(g_pmutexSystemHeap);
   
   byte * p = &((byte *)pParam)[-(int_ptr)((sizeof(uint_ptr) + 256))];
   
   os_alloc_check_bounds(p);

   os_impl_free(p);

}

#else


void * os_alloc(size_t size)
{

   return os_impl_alloc(size);


}

void * os_realloc(void * p, size_t size)
{

   return os_impl_realloc(p, size);

}

void os_free(void * p)
{

   return os_impl_free(p);

}


#endif




END_EXTERN_C

