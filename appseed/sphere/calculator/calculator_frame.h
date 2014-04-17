#pragma once


namespace calculator
{


   class CLASS_DECL_sphere frame : 
      public simple_frame_window
   {
   public: 


      string                     m_strAnimatedStatusBarText;
      int32_t                        m_iAnimateStep;
      sp(image_list)               m_pimagelist;
      bool                       m_bTimerOn;


      frame(sp(base_application) papp);
      virtual ~frame();

      virtual bool pre_create_window(CREATESTRUCT& cs);

      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);
      void OnTimer(UINT nIDEvent);

   };

} // namespace calculator




