#pragma once


namespace usermail
{


   class CLASS_DECL_CORE frame : 
      public simple_frame_window
   {
   public:
      //   simple_menu_bar     m_menubar;
      //   SimpleDialogBar   m_dialogbar;
      //xxx	SimpleReBar       m_wndReBar;
      //	simple_status_bar   m_statusbar;
      //   simple_toolbar     m_toolbar;
      //   simple_toolbar     m_toolbarView;


      //bool              m_bFullScreen;

      // Generated message map functions
      string                  m_strAnimatedStatusBarText;
      int32_t                 m_iAnimateStep;
      image_list              m_imagelist;
      bool                    m_bTimerOn;


      frame(sp(base_application) papp);


      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      virtual ~mail_frame();
#ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif



      afx_msg DECL_GEN_SIGNAL(_001OnCreate);
         afx_msg void OnTimer(UINT nIDEvent);
   };



} // namespace usermail








