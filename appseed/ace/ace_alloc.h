#pragma once


#if defined(__cplusplus)
extern "C" {
#endif



typedef void * MEMORY_ALLOC(size_t s);

typedef MEMORY_ALLOC * PFN_MEMORY_ALLOC;



typedef void * MEMORY_REALLOC(void * p, size_t s);

typedef MEMORY_REALLOC * PFN_MEMORY_REALLOC;



typedef void MEMORY_FREE(void * p);

typedef MEMORY_FREE * PFN_MEMORY_FREE;



typedef size_t MEMORY_SIZE(void *);

typedef MEMORY_SIZE * PFN_MEMORY_SIZE;





void *  ace_memory_alloc(size_t s);
void *  ace_memory_realloc(void * p, size_t s);
void    ace_memory_free(void * p);
size_t  ace_memory_size(void * p);



void  ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize);



void android_set_cache_dir(const char * pszDir);

const char * android_get_cache_dir();

void ios_set_home(const char * pszDir);

const char * ios_get_home();

void ios_set_temp(const char * pszDir);

const char * ios_get_temp();
   




#if defined(__cplusplus)
} // extern "C"
#endif



