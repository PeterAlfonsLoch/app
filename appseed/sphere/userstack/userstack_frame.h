#pragma once


namespace userstack
{


   class view;
   class pane_view;


   class CLASS_DECL_sphere frame : 
      public simple_frame_window,
      public ::ca2::message_window_simple_callback
   {
   public:
      
      
      string                     m_strAnimatedStatusBarText;
      int32_t                        m_iAnimateStep;
      image_list  *              m_pimagelist;
      sp(::user::document)                 m_pdocument;
      bool                       m_bHoverMouse;
      uint32_t                      m_dwLastHover;
      bool                       m_bTimerOn;

      bool                       m_bMouseOver;

      sp(view)                     m_pview;
      sp(pane_view)                m_ppaneview;


      frame(sp(::ca2::application) papp);
      virtual void install_message_handling(::ca2::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnApp1);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      virtual void _000OnMouse(::ca2::message::mouse * pmouse);

      void OnHoverAction();

      virtual bool pre_create_window(CREATESTRUCT& cs);

      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      virtual ~frame();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void pre_translate_message(::ca2::signal_object * pobj);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnApp2000)

      virtual void message_handler(::ca2::signal_object * pobj);

      virtual void message_window_message_handler(::ca2::signal_object * pobj);


   };


} // namespace userstack


