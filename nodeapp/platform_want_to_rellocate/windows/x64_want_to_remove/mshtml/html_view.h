#pragma once

namespace mshtml
{

class CLASS_DECL_CAFX html_view : public CFormView
{
protected: // create from serialization only
	html_view();
	DECLARE_DYNCREATE(html_view)
	DECLARE_EVENTSINK_MAP()

// Attributes
public:
	string GetType() const;
	long GetLeft() const;
	void SetLeft(long nNewValue);
	long GetTop() const;
	void SetTop(long nNewValue);
	long GetHeight() const;
	void SetHeight(long nNewValue);
	long GetWidth() const;
	void SetWidth(long nNewValue);
	void SetVisible(BOOL bNewValue);
	BOOL GetVisible() const;
	string GetLocationName() const;
	READYSTATE GetReadyState() const;
	BOOL GetOffline() const;
	void SetOffline(BOOL bNewValue);
	BOOL GetSilent() const;
	void SetSilent(BOOL bNewValue);
	BOOL GetTopLevelContainer() const;
	string GetLocationURL() const;
	BOOL GetBusy() const;
	LPDISPATCH GetApplication() const;
	LPDISPATCH GetParentBrowser() const;
	LPDISPATCH GetContainer() const;
	LPDISPATCH GetHtmlDocument() const;
	string GetFullName() const;
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
		LPCTSTR lpszTargetFrameName = NULL,	LPCTSTR lpszHeaders = NULL,
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
	BOOL GetProperty(LPCTSTR lpszProperty, string& strValue);
	COleVariant GetProperty(LPCTSTR lpszProperty);
	void ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt, VARIANT* pvaIn,
		VARIANT* pvaOut);
	BOOL GetSource(string& strRef);
	BOOL LoadFromResource(LPCTSTR lpszResource);
	BOOL LoadFromResource(UINT nRes);

	HRESULT QueryFormsCommand(DWORD dwCommandID, BOOL* pbSupported,
								BOOL* pbEnabled, BOOL* pbChecked);
	HRESULT ExecFormsCommand(DWORD dwCommandID, VARIANT* pVarIn,
								VARIANT* pVarOut);

// Overrides
public:
	virtual BOOL CreateControlSite(COleControlContainer* pContainer, 
	   COleControlSite** ppSite, UINT nID, REFCLSID clsid);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, const RECT& rect, base_wnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//{{AFX_MSG(html_view)
	afx_msg void OnFilePrint();
	//}}AFX_MSG

	// DocHostUIHandler overrideables
	virtual HRESULT OnShowContextMenu(DWORD dwID, LPPOINT ppt,
		LPUNKNOWN pcmdtReserved, LPDISPATCH pdispReserved);
	virtual HRESULT OnGetExternal(LPDISPATCH *lppDispatch);
	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO *pInfo);
	virtual HRESULT OnShowUI(DWORD dwID,
		LPOLEINPLACEACTIVEOBJECT pActiveObject,
		LPOLECOMMANDTARGET pCommandTarget, LPOLEINPLACEFRAME pFrame,
		LPOLEINPLACEUIWINDOW pDoc);
	virtual HRESULT OnHideUI();
	virtual HRESULT OnUpdateUI();
	virtual HRESULT OnEnableModeless(BOOL fEnable);
	virtual HRESULT OnDocWindowActivate(BOOL fActivate);
	virtual HRESULT OnFrameWindowActivate(BOOL fActivate);
	virtual HRESULT OnResizeBorder(LPCRECT prcBorder,
		LPOLEINPLACEUIWINDOW pUIWindow, BOOL fFrameWindow);
	virtual HRESULT OnTranslateAccelerator(LPMSG lpMsg,
		const GUID* pguidCmdGroup, DWORD nCmdID);
	virtual HRESULT OnGetOptionKeyPath(LPOLESTR* pchKey, DWORD dwReserved);
	virtual HRESULT OnFilterDataObject(LPDATAOBJECT pDataObject,
		LPDATAOBJECT* ppDataObject);
	virtual HRESULT OnTranslateUrl(DWORD dwTranslate,
		OLECHAR* pchURLIn, OLECHAR** ppchURLOut);
	virtual HRESULT OnGetDropTarget(LPDROPTARGET pDropTarget,
		LPDROPTARGET* ppDropTarget);

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
	virtual void OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel);

// Implementation
public:
	virtual ~html_view();
	virtual void OnDraw(CDC* pDC);
	base_wnd m_wndBrowser;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	::ATL::CComPtr<IWebBrowser2> m_pBrowserApp;

// Event reflectors (not normally overridden)
protected:
	virtual void NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
	virtual void BeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL,
		VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData,
		VARIANT* Headers, VARIANT_BOOL* Cancel);
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	virtual void NavigateError(LPDISPATCH pDisp, VARIANT* pvURL,
		VARIANT* pvFrame, VARIANT* pvStatusCode, VARIANT_BOOL* pvbCancel);

// Generated message map functions
protected:
	//{{AFX_MSG(html_view)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};






