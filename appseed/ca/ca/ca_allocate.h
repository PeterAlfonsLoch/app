/* Alloc.h -- Memory allocation functions
2009-02-07 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once


#include "ca_heap.h"


//#ifdef DEBUG
// Special _CLIENT_BLOCK type to identifiy CObjects.
#define ___CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))
//#endif

CLASS_DECL_ca void * MyAlloc(size_t size);
CLASS_DECL_ca void * MyRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_ca void MyFree(void *address);

#if defined(_WIN32) && !defined(METROWIN)

void SetLargePageSize();


CLASS_DECL_ca void * MidAlloc(size_t size);
CLASS_DECL_ca void * MidRealloc(void * address, size_t sizeOld, size_t sizeNew);
CLASS_DECL_ca void MidFree(void *address);
CLASS_DECL_ca void * BigAlloc(size_t size);
CLASS_DECL_ca void BigFree(void *address);

#else

#define MidAlloc(size) MyAlloc(size)
#define MidRealloc(addr, sizeOld, sizeNew) MyRealloc(addr, sizeOld, sizeNew)
#define MidFree(address) MyFree(address)
#define BigAlloc(size) MyAlloc(size)
#define BigFree(address) MyFree(address)

#endif

CLASS_DECL_ca void   use_base_ca2_allocator();


// Memory tracking allocation
#undef new
CLASS_DECL_ca void * __cdecl operator new(size_t nSize, const char * lpszFileName, int32_t nLine);
#define new DEBUG_NEW
CLASS_DECL_ca void __cdecl operator delete(void * p, const char * lpszFileName, int32_t nLine);

#undef new
void * __cdecl operator new[](size_t);
CLASS_DECL_ca void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int32_t nLine);
#define new DEBUG_NEW
CLASS_DECL_ca void __cdecl operator delete[](void * p, const char * lpszFileName, int32_t nLine);
void __cdecl operator delete[](void *);



/*CLASS_DECL_ca extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL_ca extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca extern void   (*g_pfnca2_free)(void * pvoid, int32_t iBlockType);*/

/*CLASS_DECL_ca void * ca2_alloc(size_t size);
CLASS_DECL_ca void * ca2_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca void * ca2_realloc(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca void   ca2_free(void * pvoid, int32_t iBlockType);*/


/*CLASS_DECL_ca void * _ca2_alloc(size_t size);
CLASS_DECL_ca void * _ca2_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca void * _ca2_realloc(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_ca void   _ca2_free(void * pvoid, int32_t iBlockType);
CLASS_DECL_ca size_t _ca2_msize(void * pvoid, int32_t iBlockType);

CLASS_DECL_ca void use_ca2_allocator();
*/

#ifdef new
#undef new
#endif

void * __cdecl operator new(size_t nSize);

void __cdecl operator delete(void * p);
void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);



#define DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION \
   public: \
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine) \
      { \
         return ::operator new(i, lpszFileName, iLine); \
      } \
      void * operator new(size_t i) \
      { \
         return ::operator new(i); \
      } \
      void operator delete(void * p, const char * lpszFileName, int32_t iLine) \
      { \
         ::operator delete(p, lpszFileName, iLine); \
      } \
      void operator delete(void * p) \
      { \
         ::operator delete(p); \
      } \





void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);

/////////////////////////////////////////////////////////////////////////////
// Debug primitive::memory globals and implementation helpers

#undef new
#undef delete

void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
void __cdecl operator delete(void * p, int32_t nType, const char * /* lpszFileName */, int32_t nLine);
void __cdecl operator delete[](void * p, int32_t nType, const char * lpszFileName, int32_t nLine);



inline void * __cdecl operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
{
   return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int32_t nLine)
{
   return ::operator new[](nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * pData, const char * /* lpszFileName */,  int32_t /* nLine */)
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}

inline void __cdecl operator delete[](void * pData, const char * /* lpszFileName */,  int32_t /* nLine */)
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}



inline void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   return ca2_alloc_dbg(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * p, int32_t nType, const char * /* lpszFileName */, int32_t /* nLine */)
{
    ca2_free_dbg(p, nType);
}

inline void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   return ::operator new(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete[](void * p, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   ::operator delete(p, nType, lpszFileName, nLine);
}







/////////////////////////////////////////////////////////////////////////////
// Debug primitive::memory globals and implementation helpers




#ifdef DEBUG       // most of this file is for debugging

#undef new

/////////////////////////////////////////////////////////////////////////////
// test allocation routines


#ifndef ___NO_DEBUG_CRT

CLASS_DECL_ca void * __alloc_memory_debug(size_t nSize, bool bIsObject,  const char * lpszFileName, int32_t nLine);
CLASS_DECL_ca void __free_memory_debug(void * pbData, bool bIsObject);

/////////////////////////////////////////////////////////////////////////////
// allocation failure hook, tracking turn on

CLASS_DECL_ca bool __default_alloc_hook(size_t, bool, LONG);

CLASS_DECL_ca int32_t __cdecl __alloc_alloc_hook(int32_t nAllocType, void * pvData, size_t nSize, int32_t nBlockUse, long lRequest, const uchar * szFilename, int32_t nLine);
CLASS_DECL_ca __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnNewHook);

CLASS_DECL_ca bool __enable_memory_leak_override(bool bEnable);
CLASS_DECL_ca bool __enable_memory_tracking(bool bTrack);

/////////////////////////////////////////////////////////////////////////////
// Enumerate all objects allocated in the diagnostic primitive::memory heap

struct CLASS_DECL_ca ___ENUM_CONTEXT
{
   void (*m_pfn)(::ca::object*,void *);
   void * m_pContext;
};

CLASS_DECL_ca __STATIC void __do_for_all_objects_proxy(void * pObject, void * pContext);
CLASS_DECL_ca void __do_for_all_objects(void (c_cdecl *pfn)(::ca::object*, void *), void * pContext);

/////////////////////////////////////////////////////////////////////////////
// Automatic debug primitive::memory diagnostics

CLASS_DECL_ca bool __dump_memory_leaks();

#endif // ___NO_DEBUG_CRT
#endif // DEBUG

/////////////////////////////////////////////////////////////////////////////
// Non-diagnostic primitive::memory routines

CLASS_DECL_ca int32_t c_cdecl __new_handler(size_t /* nSize */);

#undef new
#undef delete

void * __cdecl operator new(size_t nSize);

void __cdecl operator delete(void * p);
void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);


#define DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION \
   public: \
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine) \
      { \
         return ::operator new(i, lpszFileName, iLine); \
      } \
      void * operator new(size_t i) \
      { \
         return ::operator new(i); \
      } \
      void operator delete(void * p, const char * lpszFileName, int32_t iLine) \
      { \
         ::operator delete(p, lpszFileName, iLine); \
      } \
      void operator delete(void * p) \
      { \
         ::operator delete(p); \
      } \






//void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
//void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);


inline void ::ca::object::operator delete(void * p)
{
   ca2_free_dbg(p, ___CLIENT_BLOCK);
}

inline void ::ca::object::operator delete(void * p, void *)
{
   ca2_free_dbg(p, ___CLIENT_BLOCK);
}

#ifdef DEBUG

inline void ::ca::object::operator delete(void *pObject, const char *, int32_t)
{
   ca2_free_dbg(pObject, ___CLIENT_BLOCK);
}

#endif







