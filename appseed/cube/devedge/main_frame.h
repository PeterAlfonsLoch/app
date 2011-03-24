#pragma once

namespace devedge
{

   class CLASS_DECL_CA2_CUBE main_frame : public simple_frame_window
   {
   public:
      
      
      string                     m_strAnimatedStatusBarText;
      int                        m_iAnimateStep;
      image_list *                m_pimagelist;


      main_frame(::ca::application * papp);
      virtual ~main_frame();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);

      virtual bool is_application_main_window();


#ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   // simple_menu_bar     m_menubar;
   // SimpleDialogBar   m_dialogbar;
   // SimpleReBar       m_wndReBar;
   //   simple_status_bar   m_statusbar;
   // simple_toolbar     m_toolbar;
   // simple_toolbar     m_toolbarView;


      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnTimer(UINT nIDEvent);
   };

} // namespace devedge