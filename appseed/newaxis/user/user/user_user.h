#pragma once


class keyboard;
class front_end_schema;


namespace user
{


   class CLASS_DECL_AXIS user :
      virtual public ::aura::departament
   {
   public:



      ::user::elemental *                    m_pkeyboardfocus;
      ::user::elemental *                    m_pmousefocusLButtonDown;
      ::user::elemental *                    m_pmousefocusRButtonDown;
      sp(::user::window_map)                 m_pwindowmap;
      ::user::keyboard *                     m_pkeyboard;
      stringa                                m_straEscape;



      user(::aura::application * papp);
      virtual ~user();

      virtual bool set_keyboard_layout(const char * pszPath, ::action::context actioncontext);

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize();


      class window_map & window_map();


      virtual ::user::elemental * get_keyboard_focus();
      virtual void set_keyboard_focus(sp(::user::elemental) pkeyboardfocus);
      virtual ::user::elemental * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::elemental * pmousefocus);
      virtual ::user::elemental * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::elemental * pmousefocus);



      class keyboard & keyboard();


      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool finalize();


      #ifdef LINUX

      virtual sp(::message::base) get_base(XEvent * pevent,::user::interaction * pwnd = NULL);

      #endif



   };


} // namespace user



