#include "ace.h"



PFN_MEMORY_ALLOC g_pfnAceAlloc = NULL;
PFN_MEMORY_REALLOC g_pfnAceRealloc = NULL;
PFN_MEMORY_FREE g_pfnAceFree = NULL;
PFN_MEMORY_SIZE g_pfnAceSize = NULL;

void * MEMORY_DECL ace_memory_alloc(size_t s)
{

   return g_pfnAceAlloc(s);

}


void * MEMORY_DECL ace_memory_realloc(void * p, size_t s)
{

   return g_pfnAceRealloc(p, s);

}


void MEMORY_DECL ace_memory_free(void * p)
{

   g_pfnAceFree(p);

}


size_t MEMORY_DECL ace_memory_size(void * p)
{

   return g_pfnAceSize(p);

}

void MEMORY_DECL ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize)
{

   g_pfnAceAlloc = palloc;

   g_pfnAceRealloc = prealloc;

   g_pfnAceFree = pfree;

   g_pfnAceSize = psize;

}

