#ifndef _VMSSKIN_INCLUDE_FILE
#define _VMSSKIN_INCLUDE_FILE

#ifdef _VMSSKIN_DLL
    #define CLASS_DECL_VMSSKIN  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSSKIN  _declspec(dllimport)
#endif

#include "_vmsdbi.h"
#include "_vmsgdi.h"
#include "_vmsguibase.h"
#include "_vmsguii.h"
#include "_vmssimpledb.h"
#include "_vmssqlite.h"



#endif // _VMSSKIN_INCLUDE_FILE