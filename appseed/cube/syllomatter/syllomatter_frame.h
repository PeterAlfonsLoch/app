#pragma once

class CLASS_DECL_CA2_CUBE syllomatter_frame : public form_child_frame
{
public:

   string                     m_strAnimatedStatusBarText;
   int                        m_iAnimateStep;
   image_list                 m_imagelist;
   bool                       m_bTimerOn;

   syllomatter_frame(::ca::application * papp);
   virtual ~syllomatter_frame();

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   void ShowControlBars(bool bShow);
   void AnimateStatusBar();
   void SetAnimatedStatusBarText(const char * lpcsz);
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
   void MouseMessage(int nCode, WPARAM wParam, LPARAM lParam);

   bool MouseHook();
   bool MouseUnhook();


   bool m_bHoverMouse;
   DWORD m_dwLastHover;

   void OnHoverAction();


//   simple_menu_bar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx   SimpleReBar       m_wndReBar;
//   simple_status_bar   m_statusbar;
//   simple_toolbar     m_toolbar;
//   simple_toolbar     m_toolbarView;


   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus) ;
};
