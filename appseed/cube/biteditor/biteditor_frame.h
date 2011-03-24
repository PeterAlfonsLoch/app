#pragma once

class _declspec(dllexport) biteditor_frame : public simple_frame_window
{
public:

   
   string                     m_strAnimatedStatusBarText;
   int                        m_iAnimateStep;
   image_list                 m_imagelist;


   biteditor_frame(::ca::application * papp);
   virtual ~biteditor_frame();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   void ShowControlBars(bool bShow);
   void AnimateStatusBar();
   void SetAnimatedStatusBarText(const char * lpcsz);
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

//   simple_menu_bar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx   SimpleReBar       m_wndReBar;
//   simple_status_bar   m_statusbar;
//   simple_toolbar     m_toolbar;
//   simple_toolbar     m_toolbarView;

   DECL_GEN_SIGNAL(_001OnCreate)
   afx_msg void OnTimer(UINT nIDEvent);
};

