#pragma once


#define ZEROED_ALLOC 1


BEGIN_EXTERN_C


   /*
   CLASS_DECL_c void * c_alloc(size_t size);
   CLASS_DECL_c void * c_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void * c_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * c_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void   memory_free(void * pvoid);
   CLASS_DECL_c void   c_free_dbg(void * pvoid, int32_t iBlockType);
   CLASS_DECL_c size_t c_msize(void * p);
   CLASS_DECL_c size_t c_msize_dbg(void * p, int32_t iBlockType);


   */


   CLASS_DECL_c void * memory_alloc(size_t size);
   CLASS_DECL_c void * memory_calloc(size_t size, size_t bytes);
   CLASS_DECL_c void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void * memory_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_c void   memory_free(void * pvoid);
   CLASS_DECL_c void   memory_free_dbg(void * pvoid, int32_t iBlockType);
   CLASS_DECL_c size_t memory_size(void * p);
   CLASS_DECL_c size_t memory_size_dbg(void * p, int32_t iBlockType);



END_EXTERN_C



extern HANDLE g_hmutexCa2Alloc;


/*CLASS_DECL_c extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL_c extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c extern void   (*g_pfnca2_free)(void * pvoid, int32_t iBlockType);
CLASS_DECL_c extern size_t (*g_pfnca2_msize)(void * pvoid, int32_t iBlockType);
*/

/*CLASS_DECL_c void * memory_alloc(size_t size);
CLASS_DECL_c void * _ca_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c void * memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
CLASS_DECL_c void   memory_free_dbg(void * pvoid, int32_t iBlockType);
CLASS_DECL_c size_t _ca_msize(void * pvoid, int32_t iBlockType);
*/

#ifdef __cplusplus

void * __cdecl operator new(size_t nSize, void * p);
void __cdecl operator delete(void * p, void * palloc);

void * __cdecl operator new(size_t nSize) throw (std::bad_alloc);
void __cdecl operator delete(void * p) throw();

void * __cdecl operator new[](size_t nSize) throw (std::bad_alloc);
void __cdecl operator delete[](void * p) throw();

#define __NORMAL_BLOCK    1






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



