#pragma once


class mutex;


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


CLASS_DECL_c void set_heap_mutex(mutex * pmutex);
CLASS_DECL_c mutex * get_heap_mutex();