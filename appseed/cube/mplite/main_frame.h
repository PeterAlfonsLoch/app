#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE main_frame :
      public simple_frame_window
   {
   public:
      string                                    m_strAnimatedStatusBarText;
      int                                       m_iAnimateStep;
      image_list                                m_imagelist;
      ::mplite::pane_view *                     m_ppaneview;
      ::userbase::single_document_template *    m_ptemplateCommand;

      main_frame(::ca::application * papp);
      virtual ~main_frame();

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
      void ShowControlBars(bool bShow);
      void AnimateStatusBar();
      void SetAnimatedStatusBarText(const char * lpcsz);
      mplite::pane_view * GetPaneView();
      mplite::EPaneView GetViewId();
      void ShowView(mplite::EPaneView iPane);

      virtual void pre_translate_message(gen::signal_object * pobj);
      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool _001CanEnterScreenSaver();

      DECL_GEN_SIGNAL(_001OnKeyDown)

   //   simple_menu_bar     m_menubar;
   //   SimpleDialogBar   m_dialogbar;
   //xxx   SimpleReBar       m_wndReBar;
   //   simple_status_bar   m_statusbar;
   //   simple_toolbar     m_toolbar;
   //   simple_toolbar     m_toolbarView;
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate);
      afx_msg void OnViewKaraoke();
      afx_msg void OnUpdateViewKaraoke(cmd_ui * pcmdui);
      afx_msg void OnViewPlaylist();
      afx_msg void OnUpdateViewPlaylist(cmd_ui * pcmdui);
      afx_msg void OnViewAlbum();
      afx_msg void OnUpdateViewAlbum(cmd_ui * pcmdui);
      afx_msg void OnFileOpenEx();
      afx_msg void OnUpdateFileOpenEx(cmd_ui * pcmdui);
      afx_msg void OnTimer(UINT nIDEvent);
      afx_msg void OnViewOptions();
      afx_msg void OnUpdateViewOptions(cmd_ui * pcmdui);
      afx_msg void OnViewNextPane();
      afx_msg void OnViewMediaExplorer();
      afx_msg void OnViewAllMedia();
      afx_msg void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);
      afx_msg LRESULT OnVmSimple(WPARAM wparam, LPARAM lparam);
   };

} // namespace mplite