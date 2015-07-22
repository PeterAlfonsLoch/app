//#include "framework.h"

CLASS_DECL_AURA int32_t __cdecl _CrtReportBlockType(const void * p);

CLASS_DECL_AURA int32_t __cdecl _CrtSetReportMode(int32_t, int32_t);

CLASS_DECL_AURA int32_t __cdecl _CrtSetReportHook2(int32_t, int32_t(__cdecl*)(int32_t, char *, int32_t *));

CLASS_DECL_AURA _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient(_CRT_DUMP_CLIENT _PFnNewDump);

CLASS_DECL_AURA int32_t __cdecl _CrtSetDbgFlag(int32_t);

CLASS_DECL_AURA int32_t __cdecl _CrtDumpMemoryLeaks();

CLASS_DECL_AURA int32_t DECL_C _CrtCheckMemory();


/*
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

*/

CLASS_DECL_AURA int32_t DECL_C _CrtDbgReportW(
   int32_t _ReportType,
   const char16_t * _Filename,
   int32_t _LineNumber,
   const char16_t * _ModuleName,
   const char16_t * _Format,
   ...)
{
   return 0;
}


CLASS_DECL_AURA int32_t __cdecl _CrtReportBlockType(const void * p)
{
   return ___CLIENT_BLOCK;
}

CLASS_DECL_AURA int32_t __cdecl _CrtSetReportMode(int32_t, int32_t)
{
   return TRUE;
}

CLASS_DECL_AURA int32_t __cdecl _CrtSetReportHook2(int32_t, int32_t(__cdecl*)(int32_t, char *, int32_t *))
{
   return TRUE;
}

CLASS_DECL_AURA _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient(_CRT_DUMP_CLIENT _PFnNewDump)
{
   return NULL;
}

CLASS_DECL_AURA int32_t __cdecl _CrtSetDbgFlag(int32_t)
{
   return TRUE;
}

CLASS_DECL_AURA int32_t __cdecl _CrtDumpMemoryLeaks()
{
   return TRUE;
}

CLASS_DECL_AURA int32_t DECL_C _CrtCheckMemory()
{
   return 1;
}
