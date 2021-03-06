#pragma once


namespace command
{


   class CLASS_DECL_SPHERE frame : 
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:

      ::user::message_queue_sp   m_spqueue;
      
      bool                       m_bAutoHideOnOutClick;
      int32_t                 m_iAnimateStep;
      sp(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      e_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

	   frame(::aura::application * papp);
      virtual ~frame();

      virtual void install_message_handling(::message::dispatch * pinterface);

	   void ShowControlBars(bool bShow);
	  
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
	   void _001OnTimer(::timer * ptimer);

      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnApp2000);


      virtual void message_queue_message_handler(signal_details * pobj);
   };


} // namespace command


