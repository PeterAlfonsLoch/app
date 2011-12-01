/* Alloc.h -- Memory allocation functions
2009-02-07 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once

#include "heap.h"


CLASS_DECL_ca void * MyAlloc(size_t size);
CLASS_DECL_ca void MyFree(void *address);

#ifdef _WIN32

void SetLargePageSize();


CLASS_DECL_ca void * MidAlloc(size_t size);
CLASS_DECL_ca void * MidRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_ca void MidFree(void *address);
CLASS_DECL_ca void * BigAlloc(size_t size);
CLASS_DECL_ca void BigFree(void *address);

#else

#define MidAlloc(size) MyAlloc(size)
#define MidFree(address) MyFree(address)
#define BigAlloc(size) MyAlloc(size)
#define BigFree(address) MyFree(address)

#endif

CLASS_DECL_ca void   use_base_ca2_allocator();
CLASS_DECL_ca void * base_ca2_alloc(size_t size);
CLASS_DECL_ca void * base_ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void * base_ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void   base_ca2_free(void * pvoid, int iBlockType);


/////////////////////////////////////////////////////////////////////////////
// Debug primitive::memory globals and implementation helpers




#ifdef _DEBUG       // most of this file is for debugging

#undef new

/////////////////////////////////////////////////////////////////////////////
// test allocation routines


#ifndef _AFX_NO_DEBUG_CRT

CLASS_DECL_ca void * AfxAllocMemoryDebug(size_t nSize, BOOL bIsObject,  const char * lpszFileName, int nLine);
CLASS_DECL_ca void AfxFreeMemoryDebug(void * pbData, BOOL bIsObject);

/////////////////////////////////////////////////////////////////////////////
// allocation failure hook, tracking turn on

CLASS_DECL_ca BOOL _AfxDefaultAllocHook(size_t, BOOL, LONG);
   
CLASS_DECL_ca int __cdecl _AfxAllocHookProxy(int nAllocType, void * pvData, size_t nSize, int nBlockUse, long lRequest, const unsigned char * szFilename, int nLine);
CLASS_DECL_ca AFX_ALLOC_HOOK AfxSetAllocHook(AFX_ALLOC_HOOK pfnNewHook);

CLASS_DECL_ca BOOL AfxEnableMemoryLeakOverride(BOOL bEnable);
CLASS_DECL_ca BOOL AfxEnableMemoryTracking(BOOL bTrack);

/////////////////////////////////////////////////////////////////////////////
// Enumerate all objects allocated in the diagnostic primitive::memory heap

struct CLASS_DECL_ca _AFX_ENUM_CONTEXT
{
   void (*m_pfn)(::radix::object*,void *);
   void * m_pContext;
};

CLASS_DECL_ca AFX_STATIC void _AfxDoForAllObjectsProxy(void * pObject, void * pContext);
CLASS_DECL_ca void AFXAPI AfxDoForAllObjects(void (AFX_CDECL *pfn)(::radix::object*, void *), void * pContext);

/////////////////////////////////////////////////////////////////////////////
// Automatic debug primitive::memory diagnostics

CLASS_DECL_ca BOOL AfxDumpMemoryLeaks();

#endif // _AFX_NO_DEBUG_CRT
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// Non-diagnostic primitive::memory routines

CLASS_DECL_ca int AFX_CDECL AfxNewHandler(size_t /* nSize */);

#undef new
#undef delete

void * __cdecl operator new(size_t nSize);

void __cdecl operator delete(void * p);
void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);


#define DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION \
   public: \
      void * operator new(size_t i, const char * lpszFileName, int iLine) \
      { \
         return ::operator new(i, lpszFileName, iLine); \
      } \
      void * operator new(size_t i) \
      { \
         return ::operator new(i); \
      } \
      void operator delete(void * p, const char * lpszFileName, int iLine) \
      { \
         ::operator delete(p, lpszFileName, iLine); \
      } \
      void operator delete(void * p) \
      { \
         ::operator delete(p); \
      } \






//void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine);
//void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine);


inline void PASCAL ::radix::object::operator delete(void * p)
{
   ca2_free_dbg(p, _AFX_CLIENT_BLOCK);
}

inline void PASCAL ::radix::object::operator delete(void * p, void *)
{
   ca2_free_dbg(p, _AFX_CLIENT_BLOCK);
}

inline void PASCAL ::radix::object::operator delete(void *pObject, const char *, int)
{
   ca2_free_dbg(pObject, _AFX_CLIENT_BLOCK); 
}

