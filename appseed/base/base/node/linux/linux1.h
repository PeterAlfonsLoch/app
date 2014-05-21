#pragma once


namespace linux
{


   class thread;

   class linux
   {
      int32_t function();
   };



} // namespace linux



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_LINUX __exception_link
{
   __exception_link * m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base * m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
      {
          //__try_cleanup();
      };
};

// Exception global state - never Ķaccess directly
struct CLASS_DECL_LINUX __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};


void CLASS_DECL_LINUX __abort();



CLASS_DECL_LINUX LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

typedef void (__MSG_CALL ::window::*__PMSGW)();

typedef void (__MSG_CALL ::thread::*__PMSGT)();


CLASS_DECL_LINUX MESSAGE * __get_current_message();

CLASS_DECL_LINUX void __end_thread(sp(::base::application) papp, UINT nExitCode, bool bDelete = TRUE);

CLASS_DECL_LINUX void __init_thread();
CLASS_DECL_LINUX void __term_thread(sp(::base::application) papp, HINSTANCE hInstTerm = NULL);

CLASS_DECL_LINUX void __lnx_term();

CLASS_DECL_LINUX sp(::base::application)  __get_app();
CLASS_DECL_LINUX sp(::user::interaction) __get_main_window();
//CLASS_DECL_LINUX HINSTANCE CLASS_DECL_LINUX System.m_hInstance;
CLASS_DECL_LINUX HINSTANCE __get_resource_handle();
CLASS_DECL_LINUX void __set_resource_handle(HINSTANCE hInstResource);
CLASS_DECL_LINUX const char * __get_app_name();

CLASS_DECL_LINUX HINSTANCE __get_resource_handle();
CLASS_DECL_LINUX HINSTANCE __find_string_resource_handle(UINT nID);

CLASS_DECL_LINUX void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_LINUX __global_free(HGLOBAL hGlobal);
