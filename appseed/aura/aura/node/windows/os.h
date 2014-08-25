#pragma once

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>

#include "windows_exception.h"





string get_error_message(DWORD dwError);


CLASS_DECL_AURA bool __initialize(bool bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_AURA void __set_alloc_stop(LONG lRequestNumber);
CLASS_DECL_AURA void __throw_last_cleanup();
CLASS_DECL_AURA void __try_cleanup();


namespace windows
{
   

   class interaction_impl;


} // namespace windows



// interaction_impl creation hooking
CLASS_DECL_AURA bool hook_window_create(::windows::interaction_impl * pwindow);
CLASS_DECL_AURA bool unhook_window_create();
CLASS_DECL_AURA void reset_message_cache();


#include "win1.h"
#include "windows_implementation.h"
#include "windows_folder_watch.h"
#include "windows_factory_exchange.h"
#include "windows_uac_tools.h"
#include "windows_thread.h"
#include "windows_file.h"


#define NODE_THREAD(pthread) (dynamic_cast < ::windows::thread * > (dynamic_cast < thread * >(pthread)))



CLASS_DECL_AURA void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_AURA void __trace_message(const char * lpszPrefix, LPMSG lpmsg);



#include "windows_application.h"



void CLASS_DECL_AURA __cdecl _ca2_purecall();
void CLASS_DECL_AURA __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);
bool CLASS_DECL_AURA __windows_init();
int32_t CLASS_DECL_AURA __windows_main(sp(::aura::system) psystem, ::windows::main_init_data * pmaininitdata);





#include "windows_file_find.h"
#include "windows_file.h"
#include "windows_shell.h"
#include "windows_stdio_file.h"
#include "windows_registry.h"
#include "windows_os.h"


// Sanity checks for ATOMs
CLASS_DECL_AURA bool __is_valid_atom(ATOM nAtom);
CLASS_DECL_AURA bool __is_valid_atom(const char * psz);


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


#include "windows_pipe.h"
#include "windows_process.h"




