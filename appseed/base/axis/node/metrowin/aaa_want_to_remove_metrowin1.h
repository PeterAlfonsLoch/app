#pragma once


namespace metrowin
{


   class thread;

   class metrowin
   {
      int function();
   };

   CLASS_DECL_AURA HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_AURA bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_AURA DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_AURA bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_AURA DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_AURA DWORD       GetTempPath(string & str);
   CLASS_DECL_AURA LONG        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_AURA HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex);
   CLASS_DECL_AURA bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_AURA int         GetMenuStringW(HMENU hMenu, UINT uIDItem, string & str, UINT flags);
   CLASS_DECL_AURA void        TimeToFileTime(::aura::application * papp, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace metrowin



// Placed on frame for EXCEPTION linkage, or ::exception::aura cleanup
struct CLASS_DECL_AURA __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base* m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
      { __try_cleanup(); };
};

// Exception global state - never access directly
struct CLASS_DECL_AURA __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};

#ifndef _PNH_DEFINED
typedef int (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_AURA __get_new_handler();
_PNH CLASS_DECL_AURA __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_AURA int c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_AURA __abort();


// helpers for registering your own WNDCLASSes
#ifndef METROWIN
CLASS_DECL_AURA const char * __register_window_class(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
CLASS_DECL_AURA bool __register_class(WNDCLASS* lpWndClass);

CLASS_DECL_AURA LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_AURA WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_AURA LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);



CLASS_DECL_AURA ::metrowin::thread * __get_thread();
CLASS_DECL_AURA void __set_thread(::thread * pthread);
CLASS_DECL_AURA MSG* __get_current_message();

CLASS_DECL_AURA void __end_thread(::aura::application * papp, UINT nExitCode, bool bDelete = TRUE);

CLASS_DECL_AURA void __init_thread();
CLASS_DECL_AURA void __term_thread(::aura::application * papp, HINSTANCE hInstTerm = NULL);


CLASS_DECL_AURA void __win_term();

CLASS_DECL_AURA sp(::user::interaction) __get_main_window();


CLASS_DECL_AURA void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_AURA __global_free(HGLOBAL hGlobal);
