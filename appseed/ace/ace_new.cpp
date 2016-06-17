#include "framework.h"
#include "ace_new.h"
#include <stdlib.h>
#include <new>


void * MEMORY_DECL ace_memory_alloc(size_t s);


void MEMORY_DECL ace_memory_free(void * p);


void * operator new(size_t nSize) new_throw_spec
{

   return ace_memory_alloc(nSize);

}

void operator delete(void * p) del_throw_spec
{

   ace_memory_free(p);

}

void * operator new[](size_t nSize) new_throw_spec
{

   return ::operator new(nSize);

}


void operator delete[](void * p) del_throw_spec
{

   ::operator delete(p);

}


void operator delete(void * p, size_t n) del_throw_spec
{

   ::operator delete(p);

}




