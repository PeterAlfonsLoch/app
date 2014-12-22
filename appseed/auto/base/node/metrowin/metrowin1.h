#pragma once


namespace metrowin
{


   class thread;

   class metrowin
   {
      int function();
   };

   CLASS_DECL_BASE HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_BASE bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_BASE DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_BASE bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_BASE DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_BASE DWORD       GetTempPath(string & str);
   CLASS_DECL_BASE LONG        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_BASE HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex);
   CLASS_DECL_BASE bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_BASE int         GetMenuStringW(HMENU hMenu, UINT uIDItem, string & str, UINT flags);
   CLASS_DECL_BASE void        TimeToFileTime(::axis::application * papp, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace metrowin



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_BASE __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base* m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
      { __try_cleanup(); };
};

// Exception global state - never access directly
struct CLASS_DECL_BASE __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};

#ifndef _PNH_DEFINED
typedef int (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_BASE __get_new_handler();
_PNH CLASS_DECL_BASE __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_BASE int c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_BASE __abort();


// helpers for registering your own WNDCLASSes
#ifndef METROWIN
CLASS_DECL_BASE const char * __register_window_class(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
CLASS_DECL_BASE bool __register_class(WNDCLASS* lpWndClass);

CLASS_DECL_BASE LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_BASE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_BASE LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);



CLASS_DECL_BASE ::metrowin::thread * __get_thread();
CLASS_DECL_BASE void __set_thread(::thread * pthread);
CLASS_DECL_BASE MSG* __get_current_message();

CLASS_DECL_BASE void __end_thread(::axis::application * papp, UINT nExitCode, bool bDelete = TRUE);

CLASS_DECL_BASE void __init_thread();
CLASS_DECL_BASE void __term_thread(::axis::application * papp, HINSTANCE hInstTerm = NULL);


CLASS_DECL_BASE void __win_term();

CLASS_DECL_BASE sp(::user::interaction) __get_main_window();


CLASS_DECL_BASE void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_BASE __global_free(HGLOBAL hGlobal);
