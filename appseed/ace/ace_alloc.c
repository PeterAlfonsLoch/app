#include <stdlib.h>
#include "ace.h"


PFN_MEMORY_ALLOC g_pfnAceAlloc = &malloc;
PFN_MEMORY_REALLOC g_pfnAceRealloc = &realloc;
PFN_MEMORY_FREE g_pfnAceFree = &free;
PFN_MEMORY_SIZE g_pfnAceSize = NULL;


void * ace_memory_alloc(size_t s)
{

   return g_pfnAceAlloc(s);

}


void * ace_memory_realloc(void * p, size_t s)
{

   return g_pfnAceRealloc(p, s);

}


void ace_memory_free(void * p)
{

   g_pfnAceFree(p);

}


size_t ace_memory_size(void * p)
{

   return g_pfnAceSize(p);

}

void ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize)
{

   g_pfnAceAlloc = palloc;

   g_pfnAceRealloc = prealloc;

   g_pfnAceFree = pfree;

   g_pfnAceSize = psize;

}

const char * g_pszCacheDir;

void android_set_cache_dir(const char * pszDir)
{

   g_pszCacheDir = pszDir;

}

const char * android_get_cache_dir()
{
   return g_pszCacheDir;
}


const char * g_pszIosHome;

void ios_set_home(const char * pszDir)
{
   
   g_pszIosHome = pszDir;
   
}

const char * ios_get_home()
{
   return g_pszIosHome;
}

const char * g_pszIosTemp;


void ios_set_temp(const char * pszDir)
{
   
   g_pszIosTemp = pszDir;
   
}

const char * ios_get_temp()
{
   return g_pszIosTemp;
}
