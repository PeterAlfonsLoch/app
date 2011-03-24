#include "StdAfx.h"


#include "ccvotagus/source/spalib/machine_event_data.h"

extern CLASS_DECL_ca plex_heap_alloc_array g_heap;
static HANDLE g_hCa2HeapMutex = ::CreateMutex(NULL, FALSE, NULL);

CLASS_DECL_ca void * ca2_heap_alloc(size_t size)
{
   mutex_lock lock(g_hCa2HeapMutex);
   size_t * psize = (size_t *) g_heap.alloc(size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   memset(&psize[1], 0, size);
   return &psize[1];
}

CLASS_DECL_ca void * ca2_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(g_hCa2HeapMutex);
   size_t * psize = (size_t *) g_heap.realloc(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
}


CLASS_DECL_ca void ca2_heap_free(void * pvoid)
{
   mutex_lock lock(g_hCa2HeapMutex);
   return g_heap.free(&((size_t *)pvoid)[-1], ((size_t *)pvoid)[-1]);
}









// DWORD aligned allocation

static HANDLE g_hSystemHeap = ::HeapCreate(0, 0, 0);
static HANDLE g_hSystemHeapMutex = ::CreateMutex(NULL, FALSE, NULL);

CLASS_DECL_ca void * system_heap_alloc(size_t size)
{
   mutex_lock lock(g_hSystemHeapMutex);
   byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, 0, ((size + 4 + 3) & ~3));
   if(p == NULL)
      return NULL;
   memset(p, 0, ((size + 4 + 3) & ~3));
   ((DWORD *)p)[0] = 0;
   int iMod = ((DWORD_PTR)p) % 4;
   p[3 - iMod] = 4 - iMod;
   return &p[4 - iMod];
}

CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(g_hSystemHeapMutex);
   byte * pOld = (byte *) pvoidOld;
   int iMod = pOld[-1];
   if(iMod < 1 || iMod > 4)
      return ca2_heap_alloc(size);
   size_t sizeOld = ::HeapSize(g_hSystemHeap, 0, pvoidOld);
   byte * p = (byte *) ::HeapReAlloc(g_hSystemHeap, 0, pOld - iMod, ((size + 4 + 3) & ~3));
   if(p == NULL)
   {
      ca2_heap_free(pvoidOld);
      return ca2_heap_alloc(size);
   }
   memset(&p[sizeOld], 0, ((size + 4 + 3) & ~3) - sizeOld);
   ((DWORD *)p)[0] = 0;
   iMod = ((DWORD_PTR)p) % 4;
   p[3 - iMod] = 4 - iMod;
   return &p[4 - iMod];
}


CLASS_DECL_ca void system_heap_free(void * pvoid)
{
   mutex_lock lock(g_hSystemHeapMutex);
   byte * p = (byte *) pvoid;
   int iMod = p[-1];
   if(iMod < 1 || iMod > 4)
      return;
   ::HeapFree(g_hSystemHeap, 0, p - iMod);
}

