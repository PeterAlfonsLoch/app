#pragma once


namespace android
{


   class thread;

   class android
   {

      int32_t function();

   };



} // namespace android



struct CLASS_DECL_AURA __exception_link
{


   __exception_link * m_pLinkPrev;

   __exception_link();

   ~__exception_link() 
   {

   }


};

struct CLASS_DECL_AURA __EXCEPTION_CONTEXT
{

   __exception_link* m_pLinkTop;

};

void CLASS_DECL_AURA __abort();


CLASS_DECL_AURA LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

CLASS_DECL_AURA MESSAGE * __get_current_message();

CLASS_DECL_AURA void __android_term();

CLASS_DECL_AURA sp(::aura::application)  __get_app();
CLASS_DECL_AURA ::user::interaction * __get_main_window();
CLASS_DECL_AURA const char * __get_app_name();


