#include "StdAfx.h"

#if defined(MACOS)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif


CLASS_DECL_c void * (*g_pfnca2_alloc)(size_t size) = NULL;
CLASS_DECL_c void * (*g_pfnca2_alloc_dbg)(size_t nSize, int nBlockUse, const char * szFileName, int nLine) = NULL;
CLASS_DECL_c void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine) = NULL;
CLASS_DECL_c void   (*g_pfnca2_free)(void * pvoid, int iBlockType) = NULL;
CLASS_DECL_c size_t (*g_pfnca2_msize)(void * pvoid, int iBlockType) = NULL;

DECL_SPEC_ANY simple_mutex * g_pmutexCa2Alloc = NULL;

BEGIN_EXTERN_C

void * ca2_alloc(size_t size)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_alloc(size);
}

void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}

void * ca2_realloc(void * pvoid, size_t nSize)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_realloc(pvoid, nSize, 0, NULL, -1);
}

void * ca2_realloc_dbg(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_realloc(pvoid, nSize, nBlockUse, szFileName, nLine);
}

void ca2_free(void * pvoid)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_free(pvoid, 0);
}

void ca2_free_dbg(void * pvoid, int iBlockType)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_free(pvoid, iBlockType);
}

size_t ca2_msize(void * pvoid)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_msize(pvoid, 0);
}

size_t ca2_msize_dbg(void * pvoid, int iBlockType)
{
   mutex_lock lock(g_pmutexCa2Alloc, true);
   return g_pfnca2_msize(pvoid, iBlockType);
}


END_EXTERN_C

void * _ca_alloc(size_t size)
{
#ifdef WINDOWS
   byte * p = (byte *) HeapAlloc(::GetProcessHeap(), 0, size + 4 + 32);
#else
   byte * p = (byte *) malloc(size + 4 + 32);
#endif
   p[0] = 22;
   return p + 4 + 16;
}

void * _ca_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   return _ca_alloc(nSize);
}


void * _ca_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return _ca_alloc(nSize);
   p -= (4 + 16);
   if(p[0] == 22)
   {
#ifdef WINDOWS
      p = (byte *) HeapReAlloc(::GetProcessHeap(), 0, p, nSize + 4 + 32);
#else
      p = (byte *) realloc(p, nSize + 4 + 32);
#endif
   }
   return p + 4 + 16;
}

void _ca_free(void * pvoid, int iBlockType)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return;
   p -= (4 + 16);
   if(p[0] == 22)
   {
#ifdef WINDOWS
      HeapFree(::GetProcessHeap(), 0, p);
#else
      free(p);
#endif
   }
}

size_t _ca_msize(void * pvoid, int iBlockType)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return 0;
   p -= (4 + 16);
   if(p[0] == 22)
   {
#ifdef WINDOWS
      return HeapSize(::GetProcessHeap(), 0, p)  - (4 + 16);
#elif defined(MACOS)
      return malloc_size(p);
#else
      return malloc_usable_size(p);
#endif
   }
   return 0;
}



void initialize_primitive_heap()
{
   if(g_pfnca2_alloc == NULL)
   {
      g_pfnca2_alloc       = _ca_alloc;
   }
   if(g_pfnca2_alloc_dbg == NULL)
   {
      g_pfnca2_alloc_dbg   = _ca_alloc_dbg;
   }
   if(g_pfnca2_realloc == NULL)
   {
      g_pfnca2_realloc     = _ca_realloc;
   }
   if(g_pfnca2_free == NULL)
   {
      g_pfnca2_free        = _ca_free;
   }
   if(g_pfnca2_msize == NULL)
   {
      g_pfnca2_msize       = _ca_msize;
   }
   if(g_pmutexCa2Alloc == NULL)
   {
      g_pmutexCa2Alloc     = new simple_mutex();
   }

}

void finalize_primitive_heap()
{
   if(g_pmutexCa2Alloc != NULL)
   {
      delete g_pmutexCa2Alloc;
      g_pmutexCa2Alloc = NULL;
   }
}


BEGIN_EXTERN_C

   CLASS_DECL_c void * c_alloc(size_t size)
{
   return ca2_alloc(size);
}
   CLASS_DECL_c void * c_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   return ca2_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}
   CLASS_DECL_c void * c_realloc(void * pvoid, size_t nSize)
{
   return ca2_realloc(pvoid, nSize);
}
   CLASS_DECL_c void * c_realloc_dbg(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   return ca2_realloc_dbg(pvoid, nSize, nBlockUse, szFileName, nLine);
}
   CLASS_DECL_c void   c_free(void * pvoid)
{
   return ca2_free(pvoid);
}
   CLASS_DECL_c void   c_free_dbg(void * pvoid, int iBlockType)
   {
      return ca2_free_dbg(pvoid, iBlockType);
   }
   CLASS_DECL_c size_t c_msize(void * p)
{
   return ca2_msize(p);
}
   CLASS_DECL_c size_t c_msize_dbg(void * p, int iBlockType)
{
   return ca2_msize_dbg(p, iBlockType);
}

END_EXTERN_C
