#pragma once

#define SECURITY_WIN32

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>

#include "metrowin_exception.h"





string get_error_message(DWORD dwError);

CLASS_DECL_BASE bool __initialize(bool bDLL = FALSE, DWORD dwVersion = _MFC_VER);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_BASE void __set_alloc_stop(LONG lRequestNumber);



#ifdef DEBUG

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_BASE bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
//CLASS_DECL_BASE bool __is_memory_block(const void * p, UINT nBytes, LONG* plRequestNumber = NULL);

#endif

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_BASE void __throw_last_cleanup();

// other out-of-line helper functions
CLASS_DECL_BASE void __try_cleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
//CLASS_DECL_BASE void hook_window_create(::user::interaction * pWnd);
//CLASS_DECL_BASE bool unhook_window_create();
//CLASS_DECL_BASE void reset_message_cache();


#include "metrowin1.h"
#include "metrowin_implementation.h"
#include "metrowin_handle.h"
#include "metrowin_dir.h"
#include "metrowin_folder_watch.h"
#include "metrowin_factory_exchange.h"
#include "metrowin_uac_tools.h"
#include "metrowin_window_draw.h"
#include "metrowin_thread.h"
#include "metrowin_window.h"
#include "metrowin_port_forward.h"

#define NULL_REF(class) (*((class *) NULL))
//CLASS_DECL_BASE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

#define WIN_THREAD(pthread) (dynamic_cast < ::metrowin::thread * > (dynamic_cast < ::thread * >(pthread)))
#define WIN_WINDOW(pwnd) (dynamic_cast < ::metrowin::window * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))
#define METROWIN_DC(pgraphics) (dynamic_cast < ::metrowin::graphics * > (pgraphics))
#define METROWIN_BITMAP(pbitmap) (dynamic_cast < ::metrowin::bitmap * > (pbitmap))
#define METROWIN_PEN(ppen) (dynamic_cast < ::metrowin::pen * > (ppen))
#define METROWIN_BRUSH(pbrush) (dynamic_cast < ::metrowin::brush * > (pbrush))
#define METROWIN_PATH(ppath) (dynamic_cast < ::metrowin::graphics_path * > (ppath))
#define METROWIN_FONT(pfont) (dynamic_cast < ::metrowin::font * > (pfont))
#define SP_DC(pgraphics) (dynamic_cast < ::metrowin::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define WIN_DIB(pdib) (dynamic_cast < ::metrowin::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))


#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 
#pragma comment(lib, "Wtsapi32.lib") 
#pragma comment(lib, "Secur32.lib") 
#pragma comment(lib, "Msimg32.lib") 
#pragma comment(lib, "Psapi.lib") 

CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_BASE bool __cdecl __is_idle_message(signal_details * pobj);
CLASS_DECL_BASE bool __cdecl __is_idle_message(MESSAGE * pMsg);


CLASS_DECL_BASE void __process_window_procedure_exception(::exception::base*, signal_details * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(signal_details * pobj);

#include "metrowin_printer.h"

#include "metrowin_application.h"


#include "metrowin_directx.h"
#include "metrowin_directx_application.h"