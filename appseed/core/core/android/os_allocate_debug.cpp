#include "framework.h"


void * DECL_C _malloc_dbg(size_t _Size, int32_t _BlockType, const char * _Filename, int32_t _LineNumber)
{
   return malloc(_Size);
}

void * DECL_C _calloc_dbg(size_t _Count, size_t _Size, int32_t _BlockType, const char * _Filename, int32_t _LineNumber)
{
   return malloc(_Count * _Size);
}

void * DECL_C _realloc_dbg(void * _Memory, size_t _NewSize, int32_t _BlockType, const char * _Filename, int32_t _LineNumber)
{
   return realloc(_Memory, _NewSize);
}

void * DECL_C _recalloc_dbg(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, int32_t _BlockType, const char * _Filename, int32_t _LineNumber)
{
   return realloc(_Memory, _NumOfElements * _SizeOfElements);
}

void * DECL_C _expand_dbg(void * _Memory, size_t _NewSize, int32_t _BlockType, const char * _Filename, int32_t _LineNumber)
{
   return realloc(_Memory, _NewSize);
}

void DECL_C _free_dbg(void * _Memory, int32_t _BlockType)
{
   free(_Memory);
}



