#pragma once


namespace linux
{


   class thread;

   class linux
   {
      int32_t function();
   };



} // namespace linux



// Placed on frame for EXCEPTION linkage, or ::exception::axis cleanup
struct CLASS_DECL_LINUX __exception_link
{
   __exception_link * m_pLinkPrev;    // previous top, next in handler chain
   ::exception::axis * m_pException;   // current exception (NULL in try block)

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


CLASS_DECL_LINUX MESSAGE * __get_current_message();


CLASS_DECL_LINUX sp(::axis::application)  __get_app();
CLASS_DECL_LINUX sp(::user::interaction) __get_main_window();
//CLASS_DECL_LINUX HINSTANCE CLASS_DECL_LINUX System.m_hInstance;
CLASS_DECL_LINUX const char * __get_app_name();


