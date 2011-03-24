#include "install_spaboot.h"



HANDLE g_hheap = NULL;



void initialize_heap()
{
   if(g_hheap == NULL)
   {
      g_hheap = ::HeapCreate(0, 0, 0);
   }
}


void finalize_heap()
{
   if(g_hheap != NULL)
   {
      ::HeapDestroy(g_hheap);
   }
}


void * malloc(size_t size)
{
   return ::HeapAlloc(g_hheap, 0, size);
}

void free(void * p)
{
   ::HeapFree(g_hheap, 0, p);
}



