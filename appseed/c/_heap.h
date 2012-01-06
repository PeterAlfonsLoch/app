#pragma once


#define ZEROED_ALLOC 1


BEGIN_EXTERN_C

   CLASS_DECL_c void * c_alloc(size_t size);
   CLASS_DECL_c void * c_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
   CLASS_DECL_c void * c_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_c void * c_realloc_dbg(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
   CLASS_DECL_c void   c_free(void * pvoid);
   CLASS_DECL_c void   c_free_dbg(void * pvoid, int iBlockType);
   CLASS_DECL_c size_t c_msize(void * p);
   CLASS_DECL_c size_t c_msize_dbg(void * p, int iBlockType);

END_EXTERN_C
