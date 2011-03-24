#if !defined(AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_)
#define AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MPLightView.h : header file
//



class PaneView;
class MusicalPlayerLightDoc;
class CVirtualBaseCtrlInterface;
/////////////////////////////////////////////////////////////////////////////
// DesktopView view

class DesktopView :
   public BaseView,
   virtual public igui::win::message::Dispatch,
   public VmsDataClientInterface,
   public Ex1TabCallback
{
protected:
	DesktopView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(DesktopView)

// Attributes
protected:
   MusicalPlayerLightPlaylistCallback * m_pplaylistcallback;


   virtual void OnDraw(CDC * pdc);

   virtual base_wnd * BackViewGetWnd();

   bool           m_bWaitingToPlay;
   bool           m_bDestroy;
   DWORD          m_dwFileOverrideKaraokeCodePage;
   bool           m_bFileOverrideKaraokeCodePage;
   bool           m_bOverrideKaraokeCodePage;
   DWORD          m_dw100Timer;
   CSimpleWndRender                    m_wndrender;
   WString          m_wstrCurrentLink;
   int            m_iDelay;

   CPen           m_penActive;

   int m_iHoverDesktopButton;

   class Desktop
   {
   public:
      COLORREF    m_cr;
      COLORREF    m_crDisable;
      COLORREF    m_crHover;
      BaseRect    m_rectButton;
   };

   class DesktopArray : public BaseArray < Desktop, Desktop & >
   {
   };

   class DesktopWindow
   {
   public:
      HWND     m_hwnd;
      HICON    m_hicon;
   };

   class DesktopWindowInfo : public BaseArray < DesktopWindow, DesktopWindow & >
   {
   };

   class DesktopWindowInfoArray : public BaseArray < DesktopWindowInfo, DesktopWindowInfo & >
   {
   };

   DesktopWindowInfoArray     m_infoa;
   DesktopArray               m_desktopa;

   int m_iDesktop;

   int m_iClickDesktop;
   int m_iClickWindow;

   int m_iListTop;
   int m_iListItemHeight;


   int m_iActiveItemDesktop;
   int m_iActiveItemWindow;


public:
   BaseVirtualTab            m_tab;
   MusicalPlayerLightDoc* GetDocument(); // non-debug version is inline

// Operations
public:

   virtual void ChangeDesktop(int iDesktop);
   DECL_GEN_SIGNAL(_001OnAppMessage);


   virtual void GetDesktopWindowInfo(int iDesktop, DesktopWindowInfo & hwnda);
   virtual void GetDesktopWindowInfo(DesktopWindowInfo & hwnda);
   virtual void FilterDesktopWindowInfo(DesktopWindowInfo & hwnda);
   virtual void ShowDesktopWindowInfo(DesktopWindowInfo & hwnda, bool bShow);
   virtual void ShowDesktopWindowInfo(bool bShow);

   void HitTest(CPoint pt, int & iDesktop, int & iWindow);
   bool HitTest(CPoint pt, int & iDesktop);
   void GetRect(LPRECT lprect, int iDesktop, int iWindow);

   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)

   virtual void _001OnDraw(CDC * pdc);

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

	PaneView * GetParentPane();
	Ex1VirtualGuieContainer * Create(int i);
	int KaraokeGetLyricsDelay();
	virtual HCURSOR KaraokeGetHandCursor();
	virtual void OnLinkClick(WString & wstr);

   DWORD CommandToCodePage(UINT ui);


   virtual void _001OnTabClick(int iTab);

	int InitGL();
// Overrides
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

	protected:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/);
   virtual void OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/);
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	//}}AFX_VIRTUAL

// Implementation

protected:
	virtual ~DesktopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//virtual void _001OnDraw(CDC * pdc);
	//{{AFX_MSG(DesktopView)
   DECL_GEN_SIGNAL(_001OnCancelEditSrvr)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnOpenLinkInNewWindow)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnCopyLinkLocation)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   int m_iTempo;
   int m_iPos;
   int m_iKeyShift;
   virtual void OnSetScalar(int i, double d);
   virtual double GetMinScalar(int i);
   virtual double GetScalar(int i);
   virtual double GetMaxScalar(int i);
   virtual void OnSetScalar(int i, int iValue);
   virtual void GetMinScalar(int i, int & iValue);
   virtual void GetScalar(int i, int & iValue);
   virtual void GetMaxScalar(int i, int & iValue);
};

#ifndef _DEBUG
inline MusicalPlayerLightDoc* DesktopView::GetDocument() // non-debug version is inline
{
	return (MusicalPlayerLightDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_)
