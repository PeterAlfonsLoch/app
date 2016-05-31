#pragma once

#define SECURITY_WIN32

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>

#include "metrowin_exception.h"





string get_error_message(DWORD dwError);

CLASS_DECL_ACE bool __initialize(bool bDLL = FALSE, DWORD dwVersion = _MFC_VER);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_ACE void __set_alloc_stop(LONG lRequestNumber);



#ifdef DEBUG

// Return TRUE if memory is sane or print out what is wrong
CLASS_DECL_ACE bool __check_memory();

// Return TRUE if valid memory block of nBytes
//CLASS_DECL_ACE bool __is_memory_block(const void * p, UINT nBytes, LONG* plRequestNumber = NULL);

#endif

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_ACE void __throw_last_cleanup();

// other out-of-line helper functions
CLASS_DECL_ACE void __try_cleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
//CLASS_DECL_ACE void hook_window_create(::user::interaction * pWnd);
//CLASS_DECL_ACE bool unhook_window_create();
//CLASS_DECL_ACE void reset_message_cache();


#include "metrowin1.h"
#include "metrowin_implementation.h"
#include "metrowin_folder_watch.h"
#include "metrowin_factory_exchange.h"
#include "metrowin_uac_tools.h"
#include "metrowin_thread.h"
#include "metrowin_file.h"
#include "metrowin_native_buffer.h" // soon, from axis library 2015-07-17 20:06 Livecoding(.tv)
#include "metrowin_stdio_file.h"
#include "metrowin_os.h"

#include "metrowin_dir.h"
#include "metrowin_file_system.h"

#define NULL_REF(class) (*((class *) NULL))

#define WIN_THREAD(pthread) (dynamic_cast < ::metrowin::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACE void __trace_message(const char * lpszPrefix, signal_details * pobj);
//CLASS_DECL_ACE void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

//CLASS_DECL_ACE void __cdecl __pre_translate_message(signal_details * pobj);


#include "metrowin_application.h"


