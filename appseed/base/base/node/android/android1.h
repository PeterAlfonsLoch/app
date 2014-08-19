#pragma once


namespace android
{


   class thread;

   class android
   {

      int32_t function();

   };



} // namespace android



struct CLASS_DECL_BASE __exception_link
{


   __exception_link * m_pLinkPrev;

   __exception_link();

   ~__exception_link() 
   {

   }


};

struct CLASS_DECL_BASE __EXCEPTION_CONTEXT
{

   __exception_link* m_pLinkTop;

};

void CLASS_DECL_BASE __abort();


CLASS_DECL_BASE LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

CLASS_DECL_BASE MESSAGE * __get_current_message();

CLASS_DECL_BASE void __android_term();

CLASS_DECL_BASE sp(::axis::application)  __get_app();
CLASS_DECL_BASE sp(::user::interaction) __get_main_window();
CLASS_DECL_BASE const char * __get_app_name();


