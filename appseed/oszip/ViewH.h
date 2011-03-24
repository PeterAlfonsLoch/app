#if !defined(AFX_VIEWH_H__41A045FC_9F41_11D1_8BB8_0000B43382FE__INCLUDED_)
#define AFX_VIEWH_H__41A045FC_9F41_11D1_8BB8_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewH.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHView view

#include <docobj.h>
#include <shlobj.h>
#include "fromTechno\\gfxexdisp.h"

#include "cafx/cAFXCONV.H"

#ifndef _DEBUG
// generate smaller code in release build
#define RELEASE(lpUnk) _AfxRelease((LPUNKNOWN*)&lpUnk)
#else
// generate larger but typesafe code in debug build
#define RELEASE(lpUnk) do \
	{ if ((lpUnk) != NULL) { (lpUnk)->Release(); (lpUnk) = NULL; } } while (0)
#endif

class CLASS_DECL_OSZIP CHView : public CView
{
protected: // create from serialization only
	CHView();
	DECLARE_DYNCREATE(CHView);
	DECLARE_EVENTSINK_MAP();

// Attributes
public:
	String GetType() const;
	long GetLeft() const;
	void SetLeft(long nNewValue);
	long GetTop() const;
	void SetTop(long nNewValue);
	long GetHeight() const;
	void SetHeight(long nNewValue);
	void SetVisible(BOOL bNewValue);
	BOOL GetVisible() const;
	String GetLocationName() const;
	READYSTATE GetReadyState() const;
	BOOL GetOffline() const;
	void SetOffline(BOOL bNewValue);
	BOOL GetSilent() const;
	void SetSilent(BOOL bNewValue);
	BOOL GetTopLevelContainer() const;
	String GetLocationURL() const;
	BOOL GetBusy() const;
	LPDISPATCH GetApplication() const;
	LPDISPATCH GetParentBrowser() const;
	LPDISPATCH GetContainer() const;
	LPDISPATCH GetHtmlDocument() const;
	String GetFullName() const;
	int GetToolBar() const;
	void SetToolBar(int nNewValue);
	BOOL GetMenuBar() const;
	void SetMenuBar(BOOL bNewValue);
	BOOL GetFullScreen() const;
	void SetFullScreen(BOOL bNewValue);
	OLECMDF QueryStatusWB(OLECMDID cmdID) const;
	BOOL GetRegisterAsBrowser() const;
	void SetRegisterAsBrowser(BOOL bNewValue);
	BOOL GetRegisterAsDropTarget() const;
	void SetRegisterAsDropTarget(BOOL bNewValue);
	BOOL GetTheaterMode() const;
	void SetTheaterMode(BOOL bNewValue);
	BOOL GetAddressBar() const;
	void SetAddressBar(BOOL bNewValue);
	BOOL GetStatusBar() const;
	void SetStatusBar(BOOL bNewValue);

// Operations
public:
	void GoBack();
	void GoForward();
	void GoHome();
	void GoSearch();
	void Navigate(LPCTSTR URL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL,
		LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL,
		DWORD dwPostDataLen = 0);
	void Navigate2(LPITEMIDLIST pIDL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL);
	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeaders = NULL,
		LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0);
	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags,
		CByteArray& baPostedData,
		LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeader = NULL);
	void Refresh();
	void Refresh2(int nLevel);
	void Stop();
	void PutProperty(LPCTSTR lpszProperty, const VARIANT& vtValue);
	void PutProperty(LPCTSTR lpszPropertyName, double dValue);
	void PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue);
	void PutProperty(LPCTSTR lpszPropertyName, long lValue);
	void PutProperty(LPCTSTR lpszPropertyName, short nValue);
	BOOL GetProperty(LPCTSTR lpszProperty, String& strValue);
	COleVariant GetProperty(LPCTSTR lpszProperty);
	void ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt, VARIANT* pvaIn,
		VARIANT* pvaOut);
	BOOL LoadFromResource(LPCTSTR lpszResource);
	BOOL LoadFromResource(UINT nRes);

// Operations
public:
	String csHomePage;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, base_wnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	// Events
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
		LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
		LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnStatusTextChange(LPCTSTR lpszText);
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
	virtual void OnDownloadBegin();
	virtual void OnDownloadComplete();
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnPropertyChange(LPCTSTR lpszProperty);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnQuit();
	virtual void OnVisible(BOOL bVisible);
	virtual void OnToolBar(BOOL bToolBar);
	virtual void OnMenuBar(BOOL bMenuBar);
	virtual void OnStatusBar(BOOL bStatusBar);
	virtual void OnFullScreen(BOOL bFullScreen);
	virtual void OnTheaterMode(BOOL bTheaterMode);

// Implementation
public:
	virtual ~CHView();
	base_wnd m_wndBrowser;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	IWebBrowser2* m_pBrowserApp;

// Event reflectors (not normally overridden)
protected:
	virtual void NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
	virtual void BeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL,
		VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData,
		VARIANT* Headers,   BOOL* Cancel);
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);

// Generated message map functions
protected:
	//{{AFX_MSG(CHView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnWebback();
	afx_msg void OnUpdateWebback(CCmdUI* pCmdUI);
	afx_msg void OnWebforward();
	afx_msg void OnUpdateWebforward(CCmdUI* pCmdUI);
	afx_msg void OnWebhome();
	afx_msg void OnUpdateWebhome(CCmdUI* pCmdUI);
	afx_msg void OnWebrefresh();
	afx_msg void OnUpdateWebrefresh(CCmdUI* pCmdUI);
	afx_msg void OnWebstop();
	afx_msg void OnUpdateWebstop(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline void CHView::SetRegisterAsBrowser(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_RegisterAsBrowser((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetRegisterAsDropTarget(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_RegisterAsDropTarget((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetTheaterMode(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_TheaterMode((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetVisible(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Visible((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetMenuBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_MenuBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetToolBar(int nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_ToolBar(nNewValue); }

inline void CHView::SetOffline(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Offline((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetSilent(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Silent((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::GoBack()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoBack(); }

inline void CHView::GoForward()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoForward(); }

inline void CHView::GoHome()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoHome(); }

inline void CHView::GoSearch()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoSearch(); }

inline void CHView::Refresh()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Refresh(); }

inline void CHView::Refresh2(int nLevel)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Refresh2(COleVariant((long) nLevel, VT_I4)); }

inline void CHView::Stop()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Stop(); }

inline void CHView::SetFullScreen(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_FullScreen((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetAddressBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_AddressBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }

inline void CHView::SetHeight(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Height(nNewValue); }

inline void CHView::PutProperty(LPCTSTR lpszPropertyName, long lValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(lValue, VT_UI4)); }

inline void CHView::PutProperty(LPCTSTR lpszPropertyName, short nValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(nValue, VT_UI2)); }

inline void CHView::PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(lpszValue, VT_BSTR)); }

inline void CHView::PutProperty(LPCTSTR lpszPropertyName, double dValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(dValue)); }

inline void CHView::SetTop(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Top(nNewValue); }

inline void CHView::SetLeft(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Left(nNewValue); }

inline void CHView::SetStatusBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_StatusBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWH_H__41A045FC_9F41_11D1_8BB8_0000B43382FE__INCLUDED_)
