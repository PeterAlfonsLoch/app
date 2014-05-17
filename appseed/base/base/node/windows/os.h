#pragma once

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>

#include "windows_exception.h"





//#ifdef _WINDOWS_DESKTOP_LIBRARY
  //  #define CLASS_DECL_BASE  CLASS_DECL_EXPORT
//#else
  //  #define CLASS_DECL_BASE  CLASS_DECL_IMPORT
//#endif

string get_error_message(DWORD dwError);

//sp(::base::application)     windows_instantiate_application(sp(::base::application) pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

CLASS_DECL_BASE bool __initialize(bool bDLL = FALSE, DWORD dwVersion = _MFC_VER);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_BASE void __set_alloc_stop(LONG lRequestNumber);




// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_BASE void __throw_last_cleanup();

// other out-of-line helper functions
CLASS_DECL_BASE void __try_cleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers


namespace windows
{
   

   class window;


} // namespace windows



// window creation hooking
CLASS_DECL_BASE void hook_window_create(sp(::windows::window) pwindow);
CLASS_DECL_BASE bool unhook_window_create();
CLASS_DECL_BASE void reset_message_cache();


#include "win1.h"
#include "windows_implementation.h"
#include "windows_dir.h"
#include "windows_folder_watch.h"
#include "windows_factory_exchange.h"
#include "windows_window_draw.h"
#include "windows_uac_tools.h"
#include "windows_thread.h"
#include "windows_window.h"
#include "windows_port_forward.h"
#include "windows_file.h"
//#include "windows_printer.h"

CLASS_DECL_BASE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

#define NODE_THREAD(pthread) (dynamic_cast < ::windows::thread * > (dynamic_cast < thread * >(pthread)))
#define NODE_WINDOW(pwnd) ((sp(::windows::window))(pwnd))


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
CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, LPMSG lpmsg);

CLASS_DECL_BASE bool __cdecl __is_idle_message(signal_details * pobj);
CLASS_DECL_BASE bool __cdecl __is_idle_message(MSG* pMsg);


CLASS_DECL_BASE void __process_window_procedure_exception(::exception::base*, signal_details * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(signal_details * pobj);

//#include "windows_printer.h"
#include "windows_print_job.h"

#include "windows_application.h"



void CLASS_DECL_BASE __cdecl _ca2_purecall();

void CLASS_DECL_BASE __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);

bool CLASS_DECL_BASE __windows_init();

int32_t CLASS_DECL_BASE __windows_main(sp(::base::system) psystem, ::windows::main_init_data * pmaininitdata);




#pragma once


#undef new
#include <GdiPlus.h>
#include <Gdipluseffects.h>

#define new BASE_NEW



#include "windows_dir.h"
#include "windows_file_find.h"
#include "windows_file_system.h"
#include "windows_file.h"
#include "windows_shell.h"
//#include "core/gen_resource.h"
//#include "windows_resource.h"
#include "windows_stdio_file.h"
#include "windows_file_set.h"

#include "windows_copydesk.h"
#include "windows_crypt.h"
#include "windows_ip_enum.h"
#include "windows_registry.h"

#include "windows_os.h"


// Sanity checks for ATOMs
CLASS_DECL_BASE bool __is_valid_atom(ATOM nAtom);
CLASS_DECL_BASE bool __is_valid_atom(const char * psz);


/////////////////////////////////////////////////////////////////////////////
// locale-invariant comparison helpers till CRT gets that support
inline int32_t __invariant_stricmp(const char *pszLeft,const char *pszRight)
{
#ifdef WINDOWSEX
   return ::CompareStringA(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
      NORM_IGNORECASE,
      pszLeft,
      -1,
      pszRight,
      -1) - CSTR_EQUAL;
#else
   return stricmp_dup(pszLeft,pszRight);
#endif
}

inline int32_t __invariant_stricmp(const wchar_t *pwszLeft,const wchar_t *pwszRight)
{
#ifdef WINDOWSEX
   return ::CompareStringW(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
      NORM_IGNORECASE,
      pwszLeft,
      -1,
      pwszRight,
      -1) - CSTR_EQUAL;
#else
   return wcsicmp_dup(pwszLeft,pwszRight);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Portability abstractions

#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())
