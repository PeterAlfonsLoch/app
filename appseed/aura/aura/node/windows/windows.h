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







#pragma once


namespace windows
{


   class thread;

   class windows
   {
      int32_t function();
   };

   CLASS_DECL_AURA HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_AURA bool        SHGetSpecialFolderPath(oswindow oswindow,string &str,int32_t csidl,bool fCreate);
   CLASS_DECL_AURA DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_AURA bool        CreateDirectory(const char * lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_AURA DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_AURA DWORD       GetTempPath(string & str);
   CLASS_DECL_AURA LONG        RegQueryValue(HKEY hkey,const char * lpszSubKey,string & str);
   CLASS_DECL_AURA HICON       ExtractIcon(HINSTANCE hInst,const char * lpszExeFileName,UINT nIconIndex);
   CLASS_DECL_AURA bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_AURA int32_t         GetMenuStringW(HMENU hMenu,UINT uIDItem,string & str,UINT flags);
   CLASS_DECL_AURA void        TimeToFileTime(sp(::aura::application) papp,const ::datetime::time& time,LPFILETIME pFileTime);


} // namespace windows



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_AURA __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base* m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
   {
      __try_cleanup();
   };
};

// Exception global state - never access directly
struct CLASS_DECL_AURA __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};

#ifndef _PNH_DEFINED
typedef int32_t(__cdecl * _PNH)(size_t);
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_AURA __get_new_handler();
_PNH CLASS_DECL_AURA __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_AURA int32_t c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_AURA __abort();





CLASS_DECL_AURA LONG delete_registry_tree_helper(HKEY hParentKey,const string & strKeyName);


CLASS_DECL_AURA sp(::aura::application) __get_app();
CLASS_DECL_AURA HINSTANCE __get_resource_handle();
CLASS_DECL_AURA void __set_resource_handle(HINSTANCE hInstResource);

CLASS_DECL_AURA HINSTANCE __get_resource_handle();
CLASS_DECL_AURA HINSTANCE __find_string_resource_handle(UINT nID);

namespace aura
{


   template < class APP >
   static int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_aura_init())
      {
         return -1;
      }

      APP  * papp = new APP;
      ::windows::main_init_data * pmaininitdata = new ::windows::main_init_data;


      pmaininitdata->m_hInstance = hInstance;
      pmaininitdata->m_hPrevInstance = hPrevInstance;
      pmaininitdata->m_vssCommandLine = ::str::international::unicode_to_utf8(::GetCommandLineW());
      pmaininitdata->m_nCmdShow = nCmdShow;

      papp->init_main_data(pmaininitdata);

      int32_t iRet;

      iRet = papp->main();

      try
      {

         delete papp;

         papp = NULL;

      }
      catch(...)
      {
      }

      defer_aura_term();

      return iRet;

   }


} // namespace aura




