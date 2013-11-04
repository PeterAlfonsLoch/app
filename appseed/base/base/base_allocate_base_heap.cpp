#include "framework.h"


static mutex * s_pmutexHeap = NULL;


void set_heap_mutex(mutex * pmutex)
{

   s_pmutexHeap = pmutex;
   
}


mutex * get_heap_mutex()
{
   
   return s_pmutexHeap;
   
}


