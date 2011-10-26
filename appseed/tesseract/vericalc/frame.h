#pragma once

namespace vericalc
{

   class CLASS_DECL_CA2_TESSERACT frame : public simple_frame_window
   {
   public: 

      string                     m_strAnimatedStatusBarText;
      int                        m_iAnimateStep;
      image_list *               m_pimagelist;
      bool                       m_bTimerOn;

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

   
      int OnCreate(LPCREATESTRUCT lpCreateStruct);
      void OnTimer(UINT nIDEvent);
   };

} // namespace vericalc