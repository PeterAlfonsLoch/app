#pragma once


namespace windows
{


   class thread;

   class windows
   {
      int32_t function();
   };

   CLASS_DECL_BASE HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_BASE bool        SHGetSpecialFolderPath(oswindow oswindow, string &str, int32_t csidl, bool fCreate);
   CLASS_DECL_BASE DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_BASE bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_BASE DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_BASE DWORD       GetTempPath(string & str);
   CLASS_DECL_BASE LONG        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_BASE HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex);
   CLASS_DECL_BASE bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_BASE int32_t         GetMenuStringW(HMENU hMenu, UINT uIDItem, string & str, UINT flags);
   CLASS_DECL_BASE void        TimeToFileTime(sp(::axis::application) papp, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace windows



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
typedef int32_t (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_BASE __get_new_handler();
_PNH CLASS_DECL_BASE __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_BASE int32_t c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_BASE __abort();


// helpers for registering your own WNDCLASSes
CLASS_DECL_BASE const char * __register_window_class(sp(::axis::application) papp, UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

CLASS_DECL_BASE bool __register_class(WNDCLASS* lpWndClass);


CLASS_DECL_BASE LRESULT CALLBACK __window_procedure(oswindow oswindow, UINT nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_BASE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for interaction_impl derived classes only

typedef void (__MSG_CALL thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only




CLASS_DECL_BASE LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);


CLASS_DECL_BASE sp(::axis::application) __get_app();
CLASS_DECL_BASE HINSTANCE __get_resource_handle();
CLASS_DECL_BASE void __set_resource_handle(HINSTANCE hInstResource);

CLASS_DECL_BASE HINSTANCE __get_resource_handle();
CLASS_DECL_BASE HINSTANCE __find_string_resource_handle(UINT nID);



template < class APP >
static int32_t s_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
{

   if(!defer_base_init())
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

   defer_base_term();

   return iRet;

}
