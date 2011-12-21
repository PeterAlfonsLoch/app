#pragma once


#include "_heap.h"



extern HANDLE g_hmutexCa2Alloc;

BEGIN_EXTERN_C

   CLASS_DECL_c void * ca2_alloc(size_t size);
   CLASS_DECL_c void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
   CLASS_DECL_c void * ca2_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * ca2_realloc_dbg(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
   CLASS_DECL_c void   ca2_free(void * pvoid);
   CLASS_DECL_c void   ca2_free_dbg(void * pvoid, int iBlockType);
   CLASS_DECL_c size_t ca2_msize(void * p);
   CLASS_DECL_c size_t ca2_msize_dbg(void * p, int iBlockType);

END_EXTERN_C

CLASS_DECL_c extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL_c extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_c extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_c extern void   (*g_pfnca2_free)(void * pvoid, int iBlockType);
CLASS_DECL_c extern size_t (*g_pfnca2_msize)(void * pvoid, int iBlockType);


CLASS_DECL_c void * _ca_alloc(size_t size);
CLASS_DECL_c void * _ca_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_c void * _ca_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_c void   _ca_free(void * pvoid, int iBlockType);
CLASS_DECL_c size_t _ca_msize(void * pvoid, int iBlockType);



void * __cdecl operator new(size_t nSize, void * p);
void __cdecl operator delete(void * p, void * palloc);

void * __cdecl operator new(size_t nSize);
void __cdecl operator delete(void * p);

void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);

#define __NORMAL_BLOCK    1

inline void * __cdecl operator new(size_t nSize)
{
   return ca2_alloc(nSize);
}

inline void * __cdecl operator new(size_t nSize, void * p)
{
   UNREFERENCED_PARAMETER(nSize);
   return p;
}
#define __PLACEMENT_NEW_INLINE


inline void __cdecl operator delete(void * p, void * palloc)
{
   UNREFERENCED_PARAMETER(p);
   UNREFERENCED_PARAMETER(palloc);
}


inline void __cdecl operator delete(void * p)
{
   ca2_free(p);
}

inline void * __cdecl operator new[](size_t nSize)
{
   return ::operator new(nSize);
}

inline void __cdecl operator delete[](void * p)
{
   ::operator delete(p);
}





CLASS_DECL_c void initialize_primitive_heap();
CLASS_DECL_c void finalize_primitive_heap();
