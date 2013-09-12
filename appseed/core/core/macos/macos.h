//
//  macos.h
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once

DWORD get_tick_count();


//typedef unsigned long * uint_ptr;

//typedef unsigned long HRESULT;
//#define S_OK 0
//#define E_FAIL -1
//#define SUCCEEDED(hr) ((hr) >= 0)
//#define FAILED(hr) ((hr) < 0)


#define WINAPI



void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const uint_ptr *lpArguments);
//#define EXCEPTION_NONCONTINUABLE 1





namespace ca2
{


   class file;


} // namespace ca2


typedef ::ca2::file * HFILE;



CLASS_DECL_ca2 bool AmIBeingDebugged();

#include "os_multithreading.h"

