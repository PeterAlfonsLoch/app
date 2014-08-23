// libct.h

#pragma once




#ifdef WIN32


#include <tchar.h>


BEGIN_EXTERN_C


#ifdef WINDOWSEX


CLASS_DECL_AXIS extern TCHAR *_argv[];
CLASS_DECL_AXIS int32_t _init_args();
CLASS_DECL_AXIS void _term_args();

#endif

typedef void (__cdecl *_PVFV)();
extern _PVFV __xc_a[], __xc_z[];    /* C++ initializers */

CLASS_DECL_AXIS void _initterm(_PVFV *pfbegin, _PVFV *pfend);
CLASS_DECL_AXIS void _init_atexit();
CLASS_DECL_AXIS void _doexit();

END_EXTERN_C



#endif
