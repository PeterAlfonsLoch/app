#pragma once

namespace nature
{

   class CLASS_DECL_CORE frame : 
      virtual public simple_frame_window
   {
      
   public:
      
      
      string                     m_strAnimatedStatusBarText;
      int32_t                        m_iAnimateStep;
      sp(image_list)               m_pimagelist;
      bool                       m_bTimerOn;
      bool                       m_bHoverMouse;
      uint32_t                      m_dwLastHover;


      frame(sp(::base::application) papp);
      virtual ~frame();

      virtual bool pre_create_window(::user::create_struct& cs);

      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif



      void OnHoverAction();


      DECL_GEN_SIGNAL(_001OnCreate);
      void OnTimer(UINT nIDEvent);

   };

} // namespace nature