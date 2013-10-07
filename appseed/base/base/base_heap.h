#pragma once


#define ZEROED_ALLOC 1



BEGIN_EXTERN_C


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



CLASS_DECL_c void * ca2_heap_alloc(size_t size);
CLASS_DECL_c void * ca2_heap_realloc(void * p, size_t size);
CLASS_DECL_c void   ca2_heap_free(void * p);

CLASS_DECL_c void * ca2_heap_alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_c void * ca2_heap_realloc_dbg(void * p, size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_c void   ca2_heap_free_dbg(void * p);

CLASS_DECL_c void * system_heap_alloc(size_t size);
CLASS_DECL_c void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_c void   system_heap_free(void * pvoid);



extern HANDLE g_hmutexCa2Alloc;


extern CLASS_DECL_c HANDLE g_hHeap;


#ifdef __cplusplus



class mutex;

CLASS_DECL_c void set_heap_mutex(mutex * pmutex);

CLASS_DECL_c mutex * get_heap_mutex();


#endif



