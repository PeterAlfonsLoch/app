#pragma once


#define ZEROED_ALLOC 1


BEGIN_EXTERN_C


   CLASS_DECL_c void * c_alloc(size_t size);
   CLASS_DECL_c void * c_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void * c_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * c_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void   c_free(void * pvoid);
   CLASS_DECL_c void   c_free_dbg(void * pvoid, int32_t iBlockType);
   CLASS_DECL_c size_t c_msize(void * p);
   CLASS_DECL_c size_t c_msize_dbg(void * p, int32_t iBlockType);





   CLASS_DECL_c void * ca2_alloc(size_t size);
   CLASS_DECL_c void * ca2_calloc(size_t size, size_t bytes);
   CLASS_DECL_c void * ca2_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void * ca2_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * ca2_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void   ca2_free(void * pvoid);
   CLASS_DECL_c void   ca2_free_dbg(void * pvoid, int32_t iBlockType);
   CLASS_DECL_c size_t ca2_msize(void * p);
   CLASS_DECL_c size_t ca2_msize_dbg(void * p, int32_t iBlockType);



END_EXTERN_C



extern HANDLE g_hmutexCa2Alloc;


CLASS_DECL_c extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL_c extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c extern void   (*g_pfnca2_free)(void * pvoid, int32_t iBlockType);
CLASS_DECL_c extern size_t (*g_pfnca2_msize)(void * pvoid, int32_t iBlockType);


CLASS_DECL_c void * _ca_alloc(size_t size);
CLASS_DECL_c void * _ca_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c void * _ca_realloc(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c void   _ca_free(void * pvoid, int32_t iBlockType);
CLASS_DECL_c size_t _ca_msize(void * pvoid, int32_t iBlockType);


#ifdef __cplusplus

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


class CLASS_DECL_c c_class
{
public:


   static c_class s_cclass;


   c_class();
   c_class(const c_class &);
   virtual ~c_class();


};

inline CLASS_DECL_c void * __cdecl operator new (size_t size, const c_class &)
{
   return _ca_alloc(size);
}

inline CLASS_DECL_c void * __cdecl operator new[](size_t size, const c_class &)
{
   return _ca_alloc(size);
}


#define C_NEW new(c_class::s_cclass)



#endif




extern CLASS_DECL_c HANDLE g_hHeap;

CLASS_DECL_c void * ca2_heap_alloc(size_t size);
CLASS_DECL_c void * ca2_heap_realloc(void * p, size_t size);
CLASS_DECL_c void   ca2_heap_free(void * p);

CLASS_DECL_c void * ca2_heap_alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_c void * ca2_heap_realloc_dbg(void * p, size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_c void   ca2_heap_free_dbg(void * p);

CLASS_DECL_c void * system_heap_alloc(size_t size);
CLASS_DECL_c void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_c void   system_heap_free(void * pvoid);



#ifdef __cplusplus

class mutex;


CLASS_DECL_c void set_heap_mutex(mutex * pmutex);
CLASS_DECL_c mutex * get_heap_mutex();


#endif