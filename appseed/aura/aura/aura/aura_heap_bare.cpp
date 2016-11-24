#include "framework.h"


BEGIN_EXTERN_C


void * aligned_memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}


void * aligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(size);

}

void * unaligned_memory_alloc_dbg(size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(size);

}




void * memory_alloc(size_t size)
{

   return system_heap_alloc(size);

}


void * memory_calloc(size_t size, size_t bytes)
{

   return calloc(size, bytes);

}


void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{

   return system_heap_alloc(nSize);

}


void * memory_realloc(void * pvoid, size_t nSize)
{

   return system_heap_realloc(pvoid, nSize);

}


void * memory_realloc_dbg(void * pvoid, size_t size, int32_t nBlockUse, const char * szFileName, int32_t nLine)
{


   return system_heap_realloc(pvoid, size);



}

void memory_free(void * pvoid)
{
   return system_heap_free(pvoid);
}


size_t memory_size(void * pvoid)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else
   return system_heap_alloc_size(pvoid);
#endif
}


void memory_free_dbg(void * pvoid, int32_t iBlockType)
{

   memory_free(pvoid);

}


size_t memory_size_dbg(void * pvoid, int32_t iBlockType)
{
#ifdef WINDOWS
   return _msize(pvoid);
#else

   return system_heap_alloc_size(pvoid);
#endif
}




END_EXTERN_C



