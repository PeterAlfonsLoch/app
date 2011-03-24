#ifndef _VMSWIN_INCLUDE_FILE
#define _VMSWIN_INCLUDE_FILE

#include "gen/gen.h"

#include "ex1/Ex1FactoryImpl.h"

#ifdef _VMSWIN_DLL
    #define CLASS_DECL_VMSWIN  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSWIN  _declspec(dllimport)
#endif

#include "WinFactoryImpl.h"


#define NULL_REF(class) (*((class *) NULL))

#endif // _VMSWIN_INCLUDE_FILE