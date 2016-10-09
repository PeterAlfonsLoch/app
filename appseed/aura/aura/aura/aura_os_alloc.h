#pragma once


BEGIN_EXTERN_C


void * os_alloc(size_t size);
void * os_realloc(void * p, size_t size);
void os_free(void * p);


END_EXTERN_C



