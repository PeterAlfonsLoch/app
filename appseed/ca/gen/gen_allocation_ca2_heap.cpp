#include "framework.h"


extern CLASS_DECL_ca plex_heap_alloc_array g_heap;


CLASS_DECL_ca void * ca2_heap_alloc(size_t size)
{
   size_t * psize = (size_t *) g_heap.alloc(size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
}

CLASS_DECL_ca void * ca2_heap_realloc(void * pvoidOld, size_t size)
{
   size_t * psize = (size_t *) g_heap.realloc(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
}


CLASS_DECL_ca void ca2_heap_free(void * pvoid)
{
   return g_heap.free(&((size_t *)pvoid)[-1], ((size_t *)pvoid)[-1]);
}

#define LAST_MEM_FILE_AND_LINE 0


CLASS_DECL_ca void * ca2_heap_alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_heap.alloc_dbg(size + sizeof(size_t), nBlockUse, pszFileName, iLine);
   psize[0] = size + sizeof(size_t);
   memset(&psize[1], 0, size);
   return &psize[1];
#else
#if LAST_MEM_FILE_AND_LINE
   string str;
   str.Format("%s(%d)", pszFileName, iLine);
   size_t * psize = (size_t *) g_heap.alloc(size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   strncpy((char *) &psize[1], str.Mid(max(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#else
   size_t * psize = (size_t *) g_heap.alloc(size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#endif
#endif
}

CLASS_DECL_ca void * ca2_heap_realloc_dbg(void * pvoidOld, size_t size, int32_t nBlockUse, const char * szFileName, int32_t iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_heap.realloc_dbg(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t), nBlockUse, szFileName, iLine);
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#else
#if LAST_MEM_FILE_AND_LINE
   string str;
   str.Format("%s(%d)", szFileName, iLine);
   size_t * psize = (size_t *) g_heap.realloc(&((size_t *)(((byte *)pvoidOld) - 128))[-1], ((size_t *)(((byte *)pvoidOld) - 128))[-1], size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   strncpy((char *) &psize[1], str.Mid(max(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#else
   size_t * psize = (size_t *) g_heap.realloc(&((size_t *)(((byte *)pvoidOld)))[-1], ((size_t *)(((byte *)pvoidOld)))[-1], size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#endif
#endif
}


CLASS_DECL_ca void ca2_heap_free_dbg(void * pvoid)
{
#ifdef MEMDLEAK
   return g_heap.free_dbg(&((size_t *)pvoid)[-1], ((size_t *)pvoid)[-1]);
#else
#if LAST_MEM_FILE_AND_LINE
   return g_heap.free(&((size_t *)(((byte *)pvoid) - 128))[-1], (((size_t *)(((byte *)pvoid) - 128))[-1]));
#else
   return g_heap.free(&((size_t *)(((byte *)pvoid)))[-1], (((size_t *)(((byte *)pvoid)))[-1]));
#endif
#endif
}










static mutex * s_pmutexHeap = NULL;

CLASS_DECL_ca void set_heap_mutex(mutex * pmutex)
{
   s_pmutexHeap = pmutex;
}

CLASS_DECL_ca mutex * get_heap_mutex()
{
   return s_pmutexHeap;
}
