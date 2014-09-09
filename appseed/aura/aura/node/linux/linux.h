#pragma once


string get_error_message(DWORD dwError);

sp(::aura::application)     linux_instantiate_application(sp(::aura::application) pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_AURA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_AURA void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_AURA bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_AURA WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
   LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_AURA void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_AURA void AfxTryCleanup();



#include "linux1.h"
#include "implementation.h"
#include "linux_factory_exchange.h"
#include "linux_thread.h"
#include "linux_os.h"

#define NULL_REF(class) (*((class *) NULL))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))

#include "linux_shell.h"




CLASS_DECL_AURA void AfxProcessWndProcException(::exception::base*, ::signal_details * pobj);
CLASS_DECL_AURA void __cdecl __pre_translate_message(::signal_details * pobj);


#include "linux_application.h"



WINBOOL PeekMessage(
    LPMESSAGE lpMsg,
    oswindow hWnd,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax,
    UINT wRemoveMsg);

WINBOOL GetMessage(
    LPMESSAGE lpMsg,
    oswindow hWnd,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax);



int32_t CLASS_DECL_AURA __linux_main(int32_t argc, char * argv[]);


CLASS_DECL_AURA void vfxThrowFileException(sp(::aura::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);


#include "linux_internal.h"
