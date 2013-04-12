#pragma once


class mutex;


extern CLASS_DECL_ca2 HANDLE g_hHeap;

CLASS_DECL_ca2 void * ca2_heap_alloc(size_t size);
CLASS_DECL_ca2 void * ca2_heap_realloc(void * p, size_t size);
CLASS_DECL_ca2 void   ca2_heap_free(void * p);

CLASS_DECL_ca2 void * ca2_heap_alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_ca2 void * ca2_heap_realloc_dbg(void * p, size_t size, int32_t nBlockUse, const char * pszFileName, int32_t LineNumber);
CLASS_DECL_ca2 void   ca2_heap_free_dbg(void * p);

CLASS_DECL_ca2 void * system_heap_alloc(size_t size);
CLASS_DECL_ca2 void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_ca2 void   system_heap_free(void * pvoid);


CLASS_DECL_ca2 void set_heap_mutex(mutex * pmutex);
CLASS_DECL_ca2 mutex * get_heap_mutex();