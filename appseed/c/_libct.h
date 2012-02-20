// libct.h

#pragma once




#ifdef WIN32


#include <tchar.h>




BEGIN_EXTERN_C

extern TCHAR *_argv[];
int _init_args();
void _term_args();

typedef void (__cdecl *_PVFV)();
extern _PVFV __xc_a[], __xc_z[];    /* C++ initializers */

void _initterm(_PVFV *pfbegin, _PVFV *pfend);
void _init_atexit();
void _doexit();

END_EXTERN_C

void _init_file();

#include "c_heap.h"

#endif
