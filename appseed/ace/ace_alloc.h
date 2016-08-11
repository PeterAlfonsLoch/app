#pragma once


#if defined(__cplusplus)
extern "C" {
#endif



typedef void * MEMORY_DECL MEMORY_ALLOC(size_t s);

typedef MEMORY_ALLOC * PFN_MEMORY_ALLOC;



typedef void * MEMORY_DECL MEMORY_REALLOC(void * p, size_t s);

typedef MEMORY_REALLOC * PFN_MEMORY_REALLOC;



typedef void MEMORY_DECL MEMORY_FREE(void * p);

typedef MEMORY_FREE * PFN_MEMORY_FREE;



typedef size_t MEMORY_DECL MEMORY_SIZE(void *);

typedef MEMORY_SIZE * PFN_MEMORY_SIZE;





CLASS_DECL_ACE void *  MEMORY_DECL ace_memory_alloc(size_t s);
CLASS_DECL_ACE void *  MEMORY_DECL ace_memory_realloc(void * p, size_t s);
CLASS_DECL_ACE void    MEMORY_DECL ace_memory_free(void * p);
CLASS_DECL_ACE size_t  MEMORY_DECL ace_memory_size(void * p);



CLASS_DECL_ACE void  MEMORY_DECL ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize);








#if defined(__cplusplus)
} // extern "C"
#endif
