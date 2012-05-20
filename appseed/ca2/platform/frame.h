#pragma once

namespace platform
{

   class CLASS_DECL_ca2 frame : 
      virtual public form_frame
   {
      
   public:

      string                     m_strAnimatedStatusBarText;
      image_list *               m_pimagelist;
      bool                       m_bTimerOn;
      e_position                 m_eposition;
      bool                       m_bHover;
      bool                       m_bMouseLeaveTimer;
      bool                       m_bHideTimer;
      bool                       m_bOnDraw;
      DWORD                      m_dwLastSuperDock;

      frame(::ca::application * papp);
      virtual ~frame();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      virtual bool pre_create_window(CREATESTRUCT& cs);


      virtual void _000OnDraw(::ca::graphics * pgraphics);



      void ShowControlBars(bool bShow);
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif



      bool m_bHoverMouse;
      DWORD m_dwLastHover;

      void OnHoverAction();

      void super_dock_on_bergedge();

      virtual window_frame::FrameSchema * create_frame_schema();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnClose)

      
   };


} // namespace platform