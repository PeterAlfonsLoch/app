#pragma once

namespace nature
{

   class CLASS_DECL_ca2 frame : 
      virtual public simple_frame_window
   {
      
   public:
      
      
      string                     m_strAnimatedStatusBarText;
      int                        m_iAnimateStep;
      image_list *               m_pimagelist;
      bool                       m_bTimerOn;
      bool                       m_bHoverMouse;
      DWORD                      m_dwLastHover;


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



      void OnHoverAction();


      int OnCreate(LPCREATESTRUCT lpCreateStruct);
      void OnTimer(UINT nIDEvent);

   };

} // namespace nature