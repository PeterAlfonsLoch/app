#pragma once


class mutex;


extern CLASS_DECL_ca HANDLE g_hHeap;
extern CLASS_DECL_ca fixed_alloc_array g_fixedalloca;

CLASS_DECL_ca void * ca2_heap_alloc(size_t size);
CLASS_DECL_ca void * ca2_heap_realloc(void * p, size_t size);
CLASS_DECL_ca void   ca2_heap_free(void * p);

CLASS_DECL_ca void * ca2_heap_alloc_dbg(size_t size, int nBlockUse, const char * pszFileName, int LineNumber);
CLASS_DECL_ca void * ca2_heap_realloc_dbg(void * p, size_t size, int nBlockUse, const char * pszFileName, int LineNumber);
CLASS_DECL_ca void   ca2_heap_free_dbg(void * p);

CLASS_DECL_ca void * system_heap_alloc(size_t size);
CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_ca void   system_heap_free(void * pvoid);


CLASS_DECL_ca void set_heap_mutex(mutex * pmutex);
CLASS_DECL_ca mutex * get_heap_mutex();