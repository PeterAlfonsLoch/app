#include "_.h"

#define WINVER 0x0502
#define _WIN32_WINNT   0x0502
#include <windows.h>



static HANDLE g_hmutexCa2Alloc = ::CreateMutex(FALSE, NULL, FALSE);


CLASS_DECL__ void * (*g_pfnca2_alloc)(size_t size) = _ca2_alloc;
CLASS_DECL__ void * (*g_pfnca2_alloc_dbg)(size_t nSize, int nBlockUse, const char * szFileName, int nLine) = _ca2_alloc_dbg;
CLASS_DECL__ void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine) = _ca2_realloc;
CLASS_DECL__ void   (*g_pfnca2_free)(void * pvoid, int iBlockType) = _ca2_free;



void * ca2_alloc(size_t size)
{
   mutex_lock lock(g_hmutexCa2Alloc);
   return g_pfnca2_alloc(size);
}

void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   mutex_lock lock(g_hmutexCa2Alloc);
   return g_pfnca2_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
}

void * ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   mutex_lock lock(g_hmutexCa2Alloc);
   return g_pfnca2_realloc(pvoid, nSize, nBlockUse, szFileName, nLine);
}

void ca2_free(void * pvoid, int iBlockType)
{
   mutex_lock lock(g_hmutexCa2Alloc);
   return g_pfnca2_free(pvoid, iBlockType);
}








void * _ca2_alloc(size_t size)
{
   byte * p = (byte *) malloc(size + 4 + 32);
   p[0] = 5;
   return p + 4 + 16;
}

void * _ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   byte * p = (byte *) _malloc_dbg(nSize + 4 + 32, nBlockUse, szFileName, nLine);
   p[0] = 6;
   return p + 4 + 16;
}

void * _ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return _ca2_alloc_dbg(nSize, nBlockUse, szFileName, nLine);
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         p = (byte *) realloc(p, nSize + 4 + 32);
      }
      else if(p[0] == 6)
      {
         p = (byte *) _realloc_dbg(p, nSize + 4 + 32, nBlockUse, szFileName, nLine);
      }
      else
      {
         throw 0;
      }
   }
   catch(...)
   {
   }
   return p + 4 + 16;
}

void _ca2_free(void * pvoid, int iBlockType)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return;
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         free(p);
      }
      else if(p[0] == 6)
      {
         _free_dbg(p, iBlockType);
      }
      else
      {
         throw 0;
      }
   }
   catch(...)
   {
      // todo: rethrow free exception
   }
}
