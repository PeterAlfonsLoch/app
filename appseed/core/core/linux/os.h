#pragma once

DWORD get_tick_count();




#define WINAPI



void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ulong_ptr *lpArguments);


namespace file
{


   class stream_buffer;


} // namespace file


typedef ::file::stream_buffer * HFILE;



#include "os_allocate_debug.h"
#include "os_debug.h"


CLASS_DECL_CORE errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode);

//#include "os_multithreading.h"
