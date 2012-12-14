#pragma once

DWORD GetTickCount();




#define WINAPI



void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ulong_ptr *lpArguments);


namespace ex1
{


   class file;


} // namespace ex1


typedef ::ex1::file * HFILE;



#include "os_allocate_debug.h"
#include "os_debug.h"


CLASS_DECL_ca errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode);

#include "os_multithreading.h"
