#pragma once


namespace console
{


   class CLASS_DECL_sphere prompt_frame : 
      virtual public simple_frame_window,
      virtual public ::aura::message_queue_listener
   {
   public:

      string                     m_strAnimatedStatusBarText;
      bool                       m_bAutoHideOnOutClick;
      int32_t                 m_iAnimateStep;
      sp(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      e_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

      prompt_frame(::aura::application * papp);
      virtual ~prompt_frame();

      virtual void install_message_handling(::message::dispatch * pinterface);

	   void ShowControlBars(bool bShow);
	   void AnimateStatusBar();
	   void SetAnimatedStatusBarText(const char * lpcsz);

      bool show_mini();
	
   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool m_bHoverMouse;
      uint32_t m_dwLastHover;

      void OnHoverAction(bool bShowWinActionArea);
   
      void ToFront();

      virtual bool on_simple_action(id id);
      virtual bool on_simple_update(cmd_ui * pcmdui);



	   DECL_GEN_SIGNAL(_001OnCreate);
	   DECL_GEN_SIGNAL(_001OnTimer);

      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnApp2000);


      virtual void message_queue_message_handler(signal_details * pobj);

      sp(::user::wndfrm::frame::frame) create_frame_schema();
   };


} // namespace command


