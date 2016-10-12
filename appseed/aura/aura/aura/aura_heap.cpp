//#include "framework.h"


#define AXIS_MEMORY_MANAGEMENT TRUE


#if !AXIS_MEMORY_MANAGEMENT


#include "aura_heap_bare.cpp"


#else


#ifdef LINUX


#include <malloc.h>


#endif


#ifdef APPLEOS


#define ALIGN_BYTE_COUNT (sizeof(size_t) * 2)


#else


//#define ALIGN_BYTE_COUNT (sizeof(size_t))


#define ALIGN_BYTE_COUNT 16


#endif


plex_heap_alloc_array * g_pheap = NULL;


#ifdef MCHECK


#include "aura_heap_mcheck.cpp"


#elif defined(_VLD)


#include "aura_heap_vld.cpp"


#elif defined(__MCRTDBG)


#include "aura_heap_mcrtdbg.cpp"


#elif MEMDLEAK


#include "aura_heap_memdleak.cpp"


#else


#include "aura_heap_std.cpp"


#endif


#endif
