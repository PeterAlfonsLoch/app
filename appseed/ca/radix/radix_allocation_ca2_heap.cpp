#include "StdAfx.h"

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


CLASS_DECL_ca void * ca2_heap_alloc_dbg(size_t size, int nBlockUse, const char * pszFileName, int iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_heap.alloc_dbg(size + sizeof(size_t), nBlockUse, pszFileName, iLine);
   psize[0] = size + sizeof(size_t);
   memset(&psize[1], 0, size);
   return &psize[1];
#else
   string str;
   str.Format("%s(%d)", pszFileName, iLine);
   size_t * psize = (size_t *) g_heap.alloc(size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   memset(&psize[1], 0, size);
   strncpy((char *) &psize[1], str.Mid(max(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#endif
}

CLASS_DECL_ca void * ca2_heap_realloc_dbg(void * pvoidOld, size_t size, int nBlockUse, const char * szFileName, int iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_heap.realloc_dbg(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t), nBlockUse, szFileName, iLine);
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#else
   string str;
   str.Format("%s(%d)", szFileName, iLine);
   size_t * psize = (size_t *) g_heap.realloc(&((size_t *)(((byte *)pvoidOld) - 128))[-1], ((size_t *)(((byte *)pvoidOld) - 128))[-1], size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   memset(&psize[1], 0, size);
   strncpy((char *) &psize[1], str.Mid(max(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#endif
}


CLASS_DECL_ca void ca2_heap_free_dbg(void * pvoid)
{
#ifdef MEMDLEAK
   return g_heap.free_dbg(&((size_t *)pvoid)[-1], ((size_t *)pvoid)[-1]);
#else
   return g_heap.free(&((size_t *)(((byte *)pvoid) - 128))[-1], (((size_t *)(((byte *)pvoid) - 128))[-1]));
#endif
}








// DWORD aligned allocation

static HANDLE g_hSystemHeap = ::HeapCreate(0, 0, 0);
static simple_mutex g_mutexSystemHeap;

CLASS_DECL_ca void * system_heap_alloc(size_t size)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
#if ZEROED_ALLOC
   byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, HEAP_ZERO_MEMORY, ((size + 4 + 3) & ~3));
#else
   byte * p = (byte *) ::HeapAlloc(g_hSystemHeap, 0, ((size + 4 + 3) & ~3));
#endif
   if(p == NULL)
      return NULL;
   ((DWORD *)p)[0] = 0;
   int iMod = ((DWORD_PTR)p) % 4;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 - iMod];
}

CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
   byte * pOld = (byte *) pvoidOld;
   int iMod = pOld[-1];
   if(iMod < 1 || iMod > 4)
      return NULL;
   size_t sizeOld = ::HeapSize(g_hSystemHeap, 0, pOld - iMod);
   byte * p = (byte *) ::HeapReAlloc(g_hSystemHeap, 0, pOld - iMod, ((size + 4 + 3) & ~3));
   if(p == NULL)
   {
      byte * pNew = (byte *) system_heap_alloc(size);
      if(pNew == NULL)
      {
         system_heap_free(pvoidOld);
         return NULL;
      }
      memcpy(pNew, pvoidOld, min(size, sizeOld));
#if ZEROED_ALLOC
      if(size > sizeOld)
      {
         memset(&pNew[sizeOld], 0, size - sizeOld);
      }
#endif
      system_heap_free(pvoidOld);
      return pNew;
   }
   if(size > sizeOld)
   {
      memset(&p[sizeOld], 0, ((size + 4 + 3) & ~3) - sizeOld);
   }
   ((DWORD *)p)[0] = 0;
   iMod = ((DWORD_PTR)p) % 4;
   p[3 - iMod] = (uint8_t) (4 - iMod);
   return &p[4 - iMod];
}


CLASS_DECL_ca void system_heap_free(void * pvoid)
{
   mutex_lock lock(&g_mutexSystemHeap, true);
   byte * p = (byte *) pvoid;
   int iMod = p[-1];
   if(iMod < 1 || iMod > 4)
      return;
   if(!::HeapFree(g_hSystemHeap, 0, p - iMod))
   {
      DWORD dw = ::GetLastError();
      ::OutputDebugString("system_heap_free : Failed to free memory");
   }
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
