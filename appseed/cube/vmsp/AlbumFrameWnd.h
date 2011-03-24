#pragma once


class AlbumMainView;
class AlbumOptionsDialog;

class CLASS_DECL_CA2_CUBE AlbumFrameWnd :
   public simple_frame_window
{
   // // DECLARE_DYNCREATE(AlbumFrameWnd)
public:
   AlbumFrameWnd(::ca::application * papp);

// Attributes
public:
   simple_toolbar           m_toolbar;
   simple_toolbar           m_toolbarExport;
   simple_toolbar           m_toolbarHtmlView;
   simple_toolbar           m_toolbarExplorer;
   simple_status_bar         m_statusbar;
   AlbumOptionsDialog *    m_poptionsdlg;
protected:
    ::userbase::view *                 m_pMainView;
public:
   virtual void TransparentFrameWndUpdateBars();
   AlbumMainView * GetMainView();
   AlbumMainView * GetAlbumView();
   
   
   afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);

   public:
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   protected:
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
   virtual ~AlbumFrameWnd();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnDestroy();
   afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
   afx_msg void OnClose();
   afx_msg void OnToolsOptions();
   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
   ()
};

