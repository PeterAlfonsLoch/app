#include "_ace.h"
#include <stdlib.h>
#include <new>

#ifdef _ACID_LIBRARY
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif


extern "C"
{

   CLASS_DECL_ACE void * MEMORY_DECL ace_memory_alloc(size_t s);


   CLASS_DECL_ACE void MEMORY_DECL ace_memory_free(void * p);

}


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






struct openssl_exception
{

   char * file;
   int line;
   char * assertion;
   char * message;

};

extern "C"
void openssl_throw_exception(struct openssl_exception * pe)
{

   openssl_exception e;

   e = *pe;

   throw e;

}


