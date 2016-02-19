#pragma once


class keyboard;
class front_end_schema;


namespace user
{


   class CLASS_DECL_BASE user :
      virtual public ::aura::department
   {
   public:



      ::user::elemental *                    m_pmousefocusLButtonDown;
      ::user::elemental *                    m_pmousefocusRButtonDown;
      sp(::user::window_map)                 m_pwindowmap;
      stringa                                m_straEscape;



      user(::aura::application * papp);
      virtual ~user();

      

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize();


      class window_map & window_map();


      virtual ::user::elemental * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::elemental * pmousefocus);
      virtual ::user::elemental * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::elemental * pmousefocus);



      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool finalize();


      #ifdef LINUX

      virtual sp(::message::base) get_base(XEvent * pevent,::user::interaction * pwnd = NULL);

      #endif



   };


} // namespace user



