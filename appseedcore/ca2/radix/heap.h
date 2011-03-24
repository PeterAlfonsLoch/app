#pragma once

extern CLASS_DECL_ca HANDLE g_hHeap;
extern CLASS_DECL_ca fixed_alloc_array g_fixedalloca;

CLASS_DECL_ca void * ca2_heap_alloc(size_t size);
CLASS_DECL_ca void * ca2_heap_realloc(void * p, size_t size);
CLASS_DECL_ca void   ca2_heap_free(void * p);

CLASS_DECL_ca void * system_heap_alloc(size_t size);
CLASS_DECL_ca void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_ca void   system_heap_free(void * pvoid);
