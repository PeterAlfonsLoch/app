#pragma once

namespace nature
{

   class CLASS_DECL_ca frame : 
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

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif



      void OnHoverAction();


      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnTimer(UINT nIDEvent);

   };

} // namespace nature