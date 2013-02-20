#pragma once


namespace calculator
{


   class CLASS_DECL_sphere frame : 
      public simple_frame_window
   {
   public: 


      string                     m_strAnimatedStatusBarText;
      int32_t                        m_iAnimateStep;
      image_list *               m_pimagelist;
      bool                       m_bTimerOn;


      frame(::ca::application * papp);
      virtual ~frame();

      virtual bool pre_create_window(CREATESTRUCT& cs);

      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      int32_t OnCreate(LPCREATESTRUCT lpCreateStruct);
      void OnTimer(UINT nIDEvent);

   };

} // namespace calculator




