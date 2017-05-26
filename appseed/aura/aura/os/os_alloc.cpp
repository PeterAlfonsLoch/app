#include "framework.h"


#ifndef PREFER_MALLOC
#define PREFER_MALLOC 0
#endif


#if defined(WINDOWSEX) && !defined(__VLD) && !defined(__MCRTDBG)


HANDLE g_system_heap()
{

   static HANDLE s_hSystemHeap = HeapCreate(0, 0, 0);

   return s_hSystemHeap;

}


#endif


critical_section * g_pmutexSystemHeap = NULL;


#if defined(WINDOWSEX) && !PREFER_MALLOC  && !(defined(__VLD) || defined(__MCRTDBG))


#include "aura/aura/aura/os_alloc/os_alloc_WindowsHeapAlloc.cpp"


#else


#include "aura/aura/aura/os_alloc/os_alloc_malloc.cpp"


#endif


#ifndef BOUNDS_CHECK
#define BOUNDS_CHECK 0
#endif


#if BOUNDS_CHECK


#include "aura/aura/aura/os_alloc/os_alloc_bounds_check.cpp"


#else


#include "aura/aura/aura/os_alloc/os_alloc_no_bounds_check.cpp"


#endif


