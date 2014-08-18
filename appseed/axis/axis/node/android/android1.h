#pragma once


namespace android
{


   class thread;

   class android
   {

      int32_t function();

   };



} // namespace android



struct CLASS_DECL_AXIS __exception_link
{


   __exception_link * m_pLinkPrev;

   __exception_link();

   ~__exception_link() 
   {

   }


};

struct CLASS_DECL_AXIS __EXCEPTION_CONTEXT
{

   __exception_link* m_pLinkTop;

};

void CLASS_DECL_AXIS __abort();


CLASS_DECL_AXIS LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

CLASS_DECL_AXIS MESSAGE * __get_current_message();

CLASS_DECL_AXIS void __android_term();

CLASS_DECL_AXIS sp(::axis::application)  __get_app();
CLASS_DECL_AXIS sp(::user::interaction) __get_main_window();
CLASS_DECL_AXIS const char * __get_app_name();


