#include "StdAfx.h"


#ifdef WINDOWS

/*
#ifdef _WINDOWS
#define WINVER 0x0502
#define _WIN32_WINNT   0x0502
#include <windows.h>
#endif


static simple_mutex g_mutexCa2Alloc;

*/

void use_ca2_allocator()
{

   g_pfnca2_alloc       = &_ca2_alloc;
   g_pfnca2_alloc_dbg   = &_ca2_alloc_dbg;
   g_pfnca2_realloc     = &_ca2_realloc;
   g_pfnca2_free        = &_ca2_free;
   g_pfnca2_msize       = &_ca2_msize;

}



void * _ca2_alloc(size_t size)
{
   byte * p = (byte *) HeapAlloc(GetProcessHeap(), 0, size + 4 + 32);
   p[0] = 5;
   return p + 4 + 16;
}

void * _ca2_alloc_dbg(size_t size, int nBlockUse, const char * szFileName, int nLine)
{
   byte * p = (byte *) HeapAlloc(GetProcessHeap(), 0, size + 4 + 32);
   p[0] = 6;
   byte * pLine = (byte*)&nLine;
   if(nLine >= 0xffffff)
      nLine = 0;
   p[1] = pLine[0];
   p[2] = pLine[1];
   p[3] = pLine[2];
   if(szFileName != NULL)
   {
      if(strlen(szFileName) < 16)
      {
         strncpy((char *) &p[4], szFileName, strlen(szFileName));
         p[strlen(szFileName)] = '\0';
      }
      else
      {
         strncpy((char *) &p[4], szFileName + strlen(szFileName) - 16, 16);
      }
   }
   else
   {
      memset(&p[4], 0, 16);
   }
   return p + 4 + 16;
}

void * _ca2_realloc(void * pvoid, size_t size, int nBlockUse, const char * szFileName, int nLine)
{

   byte * p = (byte *) pvoid;
   if(p == NULL)
      return _ca2_alloc_dbg(size, nBlockUse, szFileName, nLine);
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         p = (byte *) HeapReAlloc(GetProcessHeap(), 0, p, size + 4 + 32);
      }
      else if(p[0] == 6)
      {
         p = (byte *) HeapReAlloc(GetProcessHeap(), 0, p, size + 4 + 32);
      }
      else
      {
         return _ca_realloc(pvoid, size, nBlockUse, szFileName, nLine);
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
         HeapFree(GetProcessHeap(), 0, p);
      }
      else if(p[0] == 6)
      {
         int iLine = (int) (*(int *)&p[1]);
         iLine = iLine & 0xffffff;
         vsstring strFile((const char *) &p[4], 16);
         HeapFree(GetProcessHeap(), 0, p);
      }
      else
      {
         return _ca_free(pvoid, iBlockType);
      }
   }
   catch(...)
   {
   }
}


size_t _ca2_msize(void * pvoid, int iBlockType)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return 0;
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         return HeapSize(GetProcessHeap(), 0, p)- (4 + 32);
      }
      else if(p[0] == 6)
      {
         return HeapSize(GetProcessHeap(), 0, p)- (4 + 32);
      }
      else
      {
         return _ca_msize(pvoid, iBlockType);
      }
   }
   catch(...)
   {
   }
   return 0;
}


#else



/*
#ifdef _WINDOWS
#define WINVER 0x0502
#define _WIN32_WINNT   0x0502
#include <windows.h>
#endif


static simple_mutex g_mutexCa2Alloc;

*/

void use_ca2_allocator()
{

   g_pfnca2_alloc       = &_ca2_alloc;
   g_pfnca2_alloc_dbg   = &_ca2_alloc_dbg;
   g_pfnca2_realloc     = &_ca2_realloc;
   g_pfnca2_free        = &_ca2_free;
   g_pfnca2_msize       = &_ca2_msize;

}



void * _ca2_alloc(size_t size)
{
   byte * p = (byte *) malloc(size + 4 + 32);
   p[0] = 5;
   return p + 4 + 16;
}

void * _ca2_alloc_dbg(size_t size, int nBlockUse, const char * szFileName, int nLine)
{
   byte * p = (byte *) malloc(size + 4 + 32);
   p[0] = 6;
   return p + 4 + 16;
}

void * _ca2_realloc(void * pvoid, size_t size, int nBlockUse, const char * szFileName, int nLine)
{

   byte * p = (byte *) pvoid;
   if(p == NULL)
      return _ca2_alloc_dbg(size, nBlockUse, szFileName, nLine);
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         p = (byte *) realloc(p, size + 4 + 32);
      }
      else if(p[0] == 6)
      {
         p = (byte *) realloc(p, size + 4 + 32);
      }
      else
      {
         return _ca_realloc(pvoid, size, nBlockUse, szFileName, nLine);
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
         free(p);
      }
      else
      {
         return _ca_free(pvoid, iBlockType);
      }
   }
   catch(...)
   {
   }
}


size_t _ca2_msize(void * pvoid, int iBlockType)
{
   byte * p = (byte *) pvoid;
   if(p == NULL)
      return 0;
   p -= (4 + 16);
   try
   {
      if(p[0] == 5)
      {
         return malloc_usable_size(p)- (4 + 32);
      }
      else if(p[0] == 6)
      {
         return malloc_usable_size(p)- (4 + 32);
      }
      else
      {
         return _ca_msize(pvoid, iBlockType);
      }
   }
   catch(...)
   {
   }
   return 0;
}


#endif
