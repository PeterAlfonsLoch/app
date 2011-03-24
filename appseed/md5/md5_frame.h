// Alá Telmo Friesen Son God frame
// translucid click-through window
// applications:
//    non-intrusive md5
//    non-intrusive notifications

#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 frame : 
      virtual public simple_frame_window
   {
   public:


      string                     m_strAnimatedStatusBarText;
      int                        m_iAnimateStep;
      image_list                 m_imagelist;
      bool                       m_bTimerOn;
	

      frame(::ca::application * papp);
      virtual ~frame();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      void ShowControlBars(bool bShow);
	   void AnimateStatusBar();
	   void SetAnimatedStatusBarText(LPCTSTR lpcsz);
	   bool IsFullScreen();
	   void ToggleFullScreen();
	   virtual void WfiOnFullScreen(bool bFullScreen);
	   
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

      void md5_fullscreen(bool bAlatel = true);

      bool m_bHoverMouse;
      DWORD m_dwLastHover;

      void OnHoverAction();


   //   SimpleMenuBar     m_menubar;
   //   SimpleDialogBar   m_dialogbar;
   //xxx	SimpleReBar       m_wndReBar;
   //	SimpleStatusBar   m_statusbar;
   //   SimpleToolBar     m_toolbar;
   //   SimpleToolBar     m_toolbarView;


      //bool              m_bFullScreen;

	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnSysCommand)
	   DECL_GEN_SIGNAL(_001OnTimer)
   };

} // namespace md5