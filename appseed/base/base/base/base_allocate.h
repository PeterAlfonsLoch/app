/* Alloc.h -- Memory allocation functions
2009-02-07 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once


CLASS_DECL_BASE void * MyAlloc(size_t size);
CLASS_DECL_BASE void * MyRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_BASE void MyFree(void *address);

#if defined(_WIN32) && !defined(METROWIN)

void SetLargePageSize();


CLASS_DECL_BASE void * MidAlloc(size_t size);
CLASS_DECL_BASE void * MidRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_BASE void MidFree(void *address);
CLASS_DECL_BASE void * BigAlloc(size_t size);
CLASS_DECL_BASE void BigFree(void *address);

#else

#define MidAlloc(size) MyAlloc(size)
#define MidRealloc(addr, sizeOld, sizeNew) MyRealloc(addr, sizeOld, sizeNew)
#define MidFree(address) MyFree(address)
#define BigAlloc(size) MyAlloc(size)
#define BigFree(address) MyFree(address)

#endif


#define __NORMAL_BLOCK    1
#define ___CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))





#ifdef DEBUG

#ifndef ___NO_DEBUG_CRT

CLASS_DECL_BASE void * __alloc_memory_debug(size_t nSize, bool bIsObject,  const char * lpszFileName, int32_t nLine);
CLASS_DECL_BASE void __free_memory_debug(void * pbData, bool bIsObject);

CLASS_DECL_BASE bool __default_alloc_hook(size_t, bool, LONG);

// A failure hook returns whether to permit allocation
typedef bool (* __ALLOC_HOOK)(size_t nSize, bool bObject, LONG lRequestNumber);

// set new hook, return old (never NULL)
//CLASS_DECL_BASE __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnAllocHook);


CLASS_DECL_BASE int32_t __cdecl __alloc_alloc_hook(int32_t nAllocType, void * pvData, size_t nSize, int32_t nBlockUse, long lRequest, const uchar * szFilename, int32_t nLine);
CLASS_DECL_BASE __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnNewHook);

CLASS_DECL_BASE bool __enable_memory_leak_override(bool bEnable);
CLASS_DECL_BASE bool __enable_memory_tracking(bool bTrack);

/////////////////////////////////////////////////////////////////////////////
// Enumerate all objects allocated in the diagnostic primitive::memory heap

struct CLASS_DECL_BASE ___ENUM_CONTEXT
{
   void (*m_pfn)(object*,void *);
   void * m_pContext;
};

CLASS_DECL_BASE __STATIC void __do_for_all_objects_proxy(void * pObject, void * pContext);
CLASS_DECL_BASE void __do_for_all_objects(void (c_cdecl *pfn)(object*, void *), void * pContext);

/////////////////////////////////////////////////////////////////////////////
// Automatic debug primitive::memory diagnostics

CLASS_DECL_BASE bool __dump_memory_leaks();

#endif // ___NO_DEBUG_CRT
#endif // DEBUG

/////////////////////////////////////////////////////////////////////////////
// Non-diagnostic primitive::memory routines

CLASS_DECL_BASE int32_t c_cdecl __new_handler(size_t /* nSize */);






