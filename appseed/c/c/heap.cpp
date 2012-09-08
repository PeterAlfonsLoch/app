#include "framework.h"

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

BEGIN_EXTERN_C

void * ca2_alloc(size_t size)
{
   return g_pfnca2_alloc(size);
}

void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   return g_pfnca2_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}

void * ca2_realloc(void * pvoid, size_t nSize)
{
   return g_pfnca2_realloc(pvoid, nSize, 0, NULL, -1);
}

void * ca2_realloc_dbg(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   return g_pfnca2_realloc(pvoid, nSize, nBlockUse, szFileName, nLine);
}

void ca2_free(void * pvoid)
{
   return g_pfnca2_free(pvoid, 0);
}

void ca2_free_dbg(void * pvoid, int iBlockType)
{
   return g_pfnca2_free(pvoid, iBlockType);
}

size_t ca2_msize(void * pvoid)
{
   return g_pfnca2_msize(pvoid, 0);
}

size_t ca2_msize_dbg(void * pvoid, int iBlockType)
{
   return g_pfnca2_msize(pvoid, iBlockType);
}


END_EXTERN_C

void * _ca_alloc(size_t size)
{
#ifdef WINDOWS
#if ZEROED_ALLOC
   byte * p = (byte *) HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size + 4 + 32);
#else
   byte * p = (byte *) HeapAlloc(::GetProcessHeap(), 0, size + 4 + 32);
#endif
#else
   byte * p = (byte *) malloc(size + 4 + 32);
#if ZEROED_ALLOC
   memset_dup(p, 0, size);
#endif
#endif
   p[0] = 22;
   *((size_t *) &p[1]) = size;
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
#if ZEROED_ALLOC
      p = (byte *) HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, p, nSize + 4 + 32);
#else
      p = (byte *) HeapAlloc(::GetProcessHeap(), 0, p, nSize + 4 + 32);
#endif
      //p = (byte *) HeapReAlloc(::GetProcessHeap(), 0, p, nSize + 4 + 32);
#else
      p = (byte *) realloc(p, nSize + 4 + 32);
#if ZEROED_ALLOC
      if(nSize > *((size_t *) &p[1]))
      {
         memset_dup(&p[4 + 16 + *((size_t *) &p[1])], 0, nSize - *((size_t *) &p[1]));
      }
#endif
#endif

   }
   *((size_t *) &p[1]) = nSize;
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
//#ifdef WINDOWS
//      return HeapSize(::GetProcessHeap(), 0, p)  - (4 + 16);
//#elif defined(MACOS)
//      return malloc_size(p);
//#else
      return *((size_t *) &p[1]);
      //return malloc_usable_size(p);
//#endif
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

}

void finalize_primitive_heap()
{
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



c_class c_class::s_cclass;


c_class::c_class()
{
}

c_class::c_class(const c_class &)
{
}

c_class::~c_class()
{
}

