#pragma once

#include "XfplayerFrameWndInterface.h"

class CAlbumDialog;
class CMixerDialog;

class CMenuV033;
class CWndFrameworkV033;

class CKaraokeMainChildWnd;

namespace vmsp
{
   class DocumentInterface;
}

class CMixerThread;
class XfplayerView;




class CLASS_DECL_CA2_CUBE KaraokeSDIFrame :
   public simple_frame_window,
   public XfplayerFrameWndInterface

{
    // // DECLARE_DYNCREATE(KaraokeSDIFrame)
   
public:
   
   ::ca::font *               m_pEditFont;

   simple_status_bar            m_statusbar;

   simple_menu_bar            m_menubar;

//   SimpleReBar             m_rebar;

   simple_toolbar             m_toolbarStandard;
   simple_toolbar             m_toolbarView1;
   simple_toolbar             m_toolbarView2;
   simple_toolbar             m_toolbarPlay;
   bool                        m_bToolbarVisible;
   CMixerThread *             m_pmixerthread;
    
//    CKaraokeMainFrame *     m_pMainFrame;
   //::userbase::menu *      m_pMenu;
//    CKaraokeSDIFrameInPlaceWnd * m_pIPWnd;
    //::ca::rgn   m_rgnWindow;
//    CMenuManagerV003 *     m_pMenuManager;        
    //CMenuV033 *            m_pmenuV033;
//    CComPtr<IDirect3D8>    m_spDirect3D8;
//    bool                   m_bDirectDrawPresenceChecked;
  //  bool                   m_bDirectDrawPresent;
    //bool                   m_bDirectDrawActive;

   KaraokeSDIFrame(::ca::application * papp);
   virtual ~KaraokeSDIFrame();

    
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL DestroyWindow();
   virtual void layout();
   virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);

   simple_toolbar * GetToolBar();
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);
   vmsp::DocumentInterface * GetActiveDocumentEx();
   virtual void OnCompactModeChange(bool bCompact);
   virtual void WfiOnAfterFullScreen(bool bFullScreen);
   CMDIFrameWnd * TransparentMDIChildWndGetMDIFrameEx();
   virtual bool TransparentFrameWndIsCompactMode();
   virtual bool OnWndMsgPosCreate();
   void OnUpdateLyricsCodePage();


   window_frame::FrameSchema * create_frame_schema();

   //XfplayerView * GetLyricView();


   void LoadBarState();
   void SaveBarState();
   virtual bool TransparentFrameWndShowBars(int nCmdShow);
   //void UpdateToolBarText(simple_toolbar &toolbar);
   //void UpdateToolBarText(CToolBarCtrlV017 &toolbar);
   virtual void TransparentFrameWndUpdateBars();
   //void UpdateToolBarStyle(simple_toolbar &toolbar);
   //void UpdateToolBarStyle(CToolBarCtrlV017 &toolbar);
   //bool GetToolButtonText(string &str, UINT uiCmd);
   //virtual void TwiOnDraw(::ca::graphics * pdc);
   //virtual void TransparentFrameWndFullScreen(bool bFullScreen);
   
   afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);
   
   //bool IsCompactMode();

   void TwcRenderBackground(::ca::graphics *pdc, LPCRECT lpcrect);
//   inline CAlbumDialog * GetAlbumDialog();
   void UpdateReserveList();
//   CAlbumDialog *      m_pAlbumDialog;
   comparable_array < CMixerDialog * > m_ptraMixerDialogs;
//   XfplayerReserveList m_ReserveList;

    
   virtual void WfiOnNotifyIcon();
   virtual void WfiOnNotiyIcon();
   //{{AFX_MSG(KaraokeSDIFrame)
   DECL_GEN_SIGNAL(_001OnCreate)
   afx_msg void OnDestroy();
   afx_msg void OnExitFullScreen();
   afx_msg void OnUpdateExitFullScreen(cmd_ui * pcmdui);
   afx_msg void OnToolsOptions();
   afx_msg void OnUpdateToolsOptions(cmd_ui * pcmdui);
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
   afx_msg void OnToolsMixer();
   afx_msg void OnUpdateToolsMixer(cmd_ui * pcmdui);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnToolsCompactdatabase();
   afx_msg void OnUpdateToolsCompactdatabase(cmd_ui * pcmdui);
   afx_msg void OnPlayer();
   afx_msg void OnUpdatePlayer(cmd_ui * pcmdui);
   afx_msg void OnWindowCascade();
   afx_msg void OnToolsSaveMemory();
   afx_msg void OnUpdateToolsSaveMemory(cmd_ui * pcmdui);
   afx_msg void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);
   afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
   afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnViewCompactSize();
   afx_msg void OnUpdateViewCompactSize(cmd_ui * pcmdui);
   afx_msg void OnUpdateVmsguiClose(cmd_ui * pcmdui);
   afx_msg void OnUpdateVmsguiWindowMinimize(cmd_ui * pcmdui);
   afx_msg void OnHelpFinder();
   //}}AFX_MSG
   //afx_msg LRESULT OnFrameworkV033Command(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnAppNotify(WPARAM wParam, LPARAM lParam);
};

