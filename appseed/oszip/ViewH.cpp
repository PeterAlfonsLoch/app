// ViewH.cpp : implementation file
//

#include "stdafx.h"
#include "HtmlViews.h"
#include "ViewH.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHView
extern String csAppDir;


IMPLEMENT_DYNCREATE(CHView, CView)
   

BEGIN_MESSAGE_MAP(CHView, CView)
	//{{AFX_MSG_MAP(CHView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_COMMAND(ID_WEBBACK, OnWebback)
	ON_UPDATE_COMMAND_UI(ID_WEBBACK, OnUpdateWebback)
	ON_COMMAND(ID_WEBFORWARD, OnWebforward)
	ON_UPDATE_COMMAND_UI(ID_WEBFORWARD, OnUpdateWebforward)
	ON_COMMAND(ID_WEBHOME, OnWebhome)
	ON_UPDATE_COMMAND_UI(ID_WEBHOME, OnUpdateWebhome)
	ON_COMMAND(ID_WEBREFRESH, OnWebrefresh)
	ON_UPDATE_COMMAND_UI(ID_WEBREFRESH, OnUpdateWebrefresh)
	ON_COMMAND(ID_WEBSTOP, OnWebstop)
	ON_UPDATE_COMMAND_UI(ID_WEBSTOP, OnUpdateWebstop)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CHView, CView)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 102 /* StatusTextChange */, OnStatusTextChange, VTS_BSTR)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 108 /* ProgressChange */, OnProgressChange, VTS_I4 VTS_I4)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 105 /* CommandStateChange */, OnCommandStateChange, VTS_I4 VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 106 /* DownloadBegin */, OnDownloadBegin, VTS_NONE)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 104 /* DownloadComplete */, OnDownloadComplete, VTS_NONE)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 113 /* TitleChange */, OnTitleChange, VTS_BSTR)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 252 /* NavigateComplete2 */, NavigateComplete2, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 250 /* BeforeNavigate2 */, BeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 112 /* PropertyChange */, OnPropertyChange, VTS_BSTR)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 251 /* NewWindow2 */, OnNewWindow2, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 259 /* DocumentComplete */, DocumentComplete, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 253 /* OnQuit */, OnQuit, VTS_NONE)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 254 /* OnVisible */, OnVisible, VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 255 /* OnToolBar */, OnToolBar, VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 256 /* OnMenuBar */, OnMenuBar, VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 257 /* OnStatusBar */, OnStatusBar, VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 258 /* OnFullScreen */, OnFullScreen, VTS_BOOL)
	ON_EVENT(CHView, AFX_IDW_PANE_FIRST, 260 /* OnTheaterMode */, OnTheaterMode, VTS_BOOL)
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHView construction/destruction
extern String csAppDir; // defined in app cpp; it's the start directory

CHView::CHView()
{
	m_pBrowserApp = NULL;
	csHomePage.Format("%shtml\\htmlview.html", csAppDir);
}

CHView::~CHView()
{
	if (m_pBrowserApp != NULL)
		m_pBrowserApp->Release();
}

BOOL CHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHView drawing

void CHView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CHView printing

BOOL CHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHView diagnostics

#ifdef _DEBUG
void CHView::AssertValid() const
{
	CView::AssertValid();
}

void CHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHView message handlers

DWORD _GfxRelease(LPUNKNOWN* lplpUnknown)
{
	ASSERT(lplpUnknown != NULL);
	if (*lplpUnknown != NULL)
	{
		TRY 
		{
			DWORD dwRef = (*lplpUnknown)->Release();
			*lplpUnknown = NULL;
			return dwRef;
		}
		CATCH(base_exception, e) 
		{
			e->Delete();
			return 0;
		}
		END_CATCH; 
	}
	return 0;
}
/*
#ifndef _DEBUG
// generate smaller code in release build
#define RELEASE(lpUnk) _AfxRelease((LPUNKNOWN*)&lpUnk)
#else
// generate larger but typesafe code in debug build
#define RELEASE(lpUnk) do \
	{ if ((lpUnk) != NULL) { (lpUnk)->Release(); (lpUnk) = NULL; } } while (0)
#endif
*/
void CHView::OnDestroy()
{
#ifdef _DEBUG
	RELEASE(m_pBrowserApp);
#else
	if (m_pBrowserApp != NULL) 
	{ 
		do 
		{
			m_pBrowserApp->Release();
			m_pBrowserApp = NULL;
		}
		while (0);
	}
#endif
}

void CHView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd))
	{
		// need to push non-client borders out of the client area
		CRect rect;
		GetClientRect(rect);
		::AdjustWindowRectEx(rect,
			m_wndBrowser.GetStyle(), FALSE, WS_EX_CLIENTEDGE);
		m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top,
			rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CHView::OnPaint()
{
	Default();
}

/////////////////////////////////////////////////////////////////////////////
// CHView operations

BOOL CHView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
						DWORD dwStyle, const RECT& rect, base_wnd* pParentWnd,
						UINT nID, CCreateContext* pContext)
{
	// create the view window itself
	if (!CView::Create(lpszClassName, lpszWindowName,
				dwStyle, rect, pParentWnd,  nID, pContext))
	{
		return FALSE;
	}

	AfxEnableControlContainer();

	RECT rectClient;
	GetClientRect(&rectClient);

	// create the control window
	// AFX_IDW_PANE_FIRST is a safe but arbitrary ID
	if (!m_wndBrowser.CreateControl(CLSID_WebBrowser, lpszWindowName,
				WS_VISIBLE | WS_CHILD, rectClient, this, AFX_IDW_PANE_FIRST))
	{
		DestroyWindow();
		return FALSE;
	}

	LPUNKNOWN lpUnk = m_wndBrowser.GetControlUnknown();
	HRESULT hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp);
	if (!SUCCEEDED(hr))
	{
		m_pBrowserApp = NULL;
		m_wndBrowser.DestroyWindow();
		DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CHView properties

String CHView::GetType() const
{
	ASSERT(m_pBrowserApp != NULL);

	BSTR bstr;
	m_pBrowserApp->get_Type(&bstr);
	String retVal(bstr);
	return retVal;
}

long CHView::GetLeft() const
{
	ASSERT(m_pBrowserApp != NULL);

	long result;
	m_pBrowserApp->get_Left(&result);
	return result;
}


long CHView::GetTop() const
{
	ASSERT(m_pBrowserApp != NULL);
	long result;
	m_pBrowserApp->get_Top(&result);
	return result;
}

int CHView::GetToolBar() const
{
	ASSERT(m_pBrowserApp != NULL);
	int result;
	m_pBrowserApp->get_ToolBar(&result);
	return result;
}

long CHView::GetHeight() const
{
	ASSERT(m_pBrowserApp != NULL);
	long result;
	m_pBrowserApp->get_Height(&result);
	return result;
}

BOOL CHView::GetVisible() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_Visible(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

String CHView::GetLocationName() const
{
	ASSERT(m_pBrowserApp != NULL);

	BSTR bstr;
	m_pBrowserApp->get_LocationName(&bstr);
	String retVal(bstr);
	return retVal;
}

String CHView::GetLocationURL() const
{
	ASSERT(m_pBrowserApp != NULL);

	BSTR bstr;
	m_pBrowserApp->get_LocationURL(&bstr);
	String retVal(bstr);
	return retVal;
}

BOOL CHView::GetBusy() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_Busy(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

READYSTATE CHView::GetReadyState() const
{
	ASSERT(m_pBrowserApp != NULL);

	READYSTATE result;
	m_pBrowserApp->get_ReadyState(&result);
	return result;
}

BOOL CHView::GetOffline() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_Offline(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetSilent() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_Silent(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

LPDISPATCH CHView::GetApplication() const
{
	ASSERT(m_pBrowserApp != NULL);

	LPDISPATCH result;
	m_pBrowserApp->get_Application(&result);
	return result;
}


LPDISPATCH CHView::GetParentBrowser() const
{
	ASSERT(m_pBrowserApp != NULL);

	LPDISPATCH result;
	m_pBrowserApp->get_Parent(&result);
	return result;
}

LPDISPATCH CHView::GetContainer() const
{
	ASSERT(m_pBrowserApp != NULL);

	LPDISPATCH result;
	m_pBrowserApp->get_Container(&result);
	return result;
}

LPDISPATCH CHView::GetHtmlDocument() const
{
	ASSERT(m_pBrowserApp != NULL);

	LPDISPATCH result;
	m_pBrowserApp->get_Document(&result);
	return result;
}

BOOL CHView::GetTopLevelContainer() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_TopLevelContainer(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetMenuBar() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_MenuBar(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetFullScreen() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_FullScreen(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetStatusBar() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_StatusBar(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

OLECMDF CHView::QueryStatusWB(OLECMDID cmdID) const
{
	ASSERT(m_pBrowserApp != NULL);

	OLECMDF result;
	m_pBrowserApp->QueryStatusWB(cmdID, &result);
	return result;
}

void CHView::ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt,
	VARIANT* pvaIn, VARIANT* pvaOut)
{
	ASSERT(m_pBrowserApp != NULL);

	m_pBrowserApp->ExecWB(cmdID, cmdexecopt, pvaIn, pvaOut);
}

BOOL CHView::GetRegisterAsBrowser() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_RegisterAsBrowser(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetRegisterAsDropTarget() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_RegisterAsDropTarget(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetTheaterMode() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_TheaterMode(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

BOOL CHView::GetAddressBar() const
{
	ASSERT(m_pBrowserApp != NULL);

	VARIANT_BOOL result;
	m_pBrowserApp->get_AddressBar(&result);

	// avoid problems for people who compare directly
	return (result ? TRUE : FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CHView operations

BOOL CHView::LoadFromResource(LPCTSTR lpszResource)
{
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);

	String strResourceURL;
	BOOL bRetVal = TRUE;
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		strResourceURL.Format(_T("res://%s/%s"), lpszModule, lpszResource);
		Navigate(strResourceURL, 0, 0, 0);
	}
	else
		bRetVal = FALSE;

	delete [] lpszModule;
	return bRetVal;
}

BOOL CHView::LoadFromResource(UINT nRes)
{
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);

	String strResourceURL;
	BOOL bRetVal = TRUE;
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		strResourceURL.Format(_T("res://%s/%d"), lpszModule, nRes);
		Navigate(strResourceURL, 0, 0, 0);
	}
	else
		bRetVal = FALSE;

	delete [] lpszModule;
	return bRetVal;
}

void CHView::Navigate(LPCTSTR lpszURL, DWORD dwFlags /* = 0 */,
	LPCTSTR lpszTargetFrameName /* = NULL */ ,
	LPCTSTR lpszHeaders /* = NULL */, LPVOID lpvPostData /* = NULL */,
	DWORD dwPostDataLen /* = 0 */)
{
	String strURL(lpszURL);
	BSTR bstrURL = strURL.AllocSysString();

	COleSafeArray vPostData;
	if (lpvPostData != NULL)
	{
		if (dwPostDataLen == 0)
			dwPostDataLen = lstrlen((LPCTSTR) lpvPostData);

		vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
	}

	m_pBrowserApp->Navigate(bstrURL,
		COleVariant((long) dwFlags, VT_I4),
		COleVariant(lpszTargetFrameName, VT_BSTR),
		vPostData,
		COleVariant(lpszHeaders, VT_BSTR));
}



void MakeOleVariant(COleVariant &ov, LPCITEMIDLIST pidl)
{
	AfxVariantInit(&ov);

	if (pidl != NULL)
	{
		// walk through entries in the list and accumulate their size

		UINT cbTotal = 0;
		SAFEARRAY *psa = NULL;
		LPCITEMIDLIST pidlWalker = pidl;

		while (pidlWalker->mkid.cb)
		{
			cbTotal += pidlWalker->mkid.cb;
			pidlWalker = (LPCITEMIDLIST)
				(((LPBYTE)pidlWalker) + pidlWalker->mkid.cb);
		}

		// add the base structure size
		cbTotal += sizeof(ITEMIDLIST);

		// get a safe array for them
		psa = SafeArrayCreateVector(VT_UI1, 0, cbTotal);

		// copy it and set members
		if (psa != NULL)
		{
			memcpy(psa->pvData, (LPBYTE) pidl, cbTotal);
			ov.vt = VT_ARRAY | VT_UI1;
			ov.parray = psa;
		}
	}
}


void CHView::Navigate2(LPITEMIDLIST pIDL, DWORD dwFlags /* = 0 */,
	LPCTSTR lpszTargetFrameName /* = NULL */)
{
	ASSERT(m_pBrowserApp != NULL);

	
//	COleVariant vPIDL(pIDL);
	COleVariant vPIDL;
	MakeOleVariant(vPIDL, pIDL);
	COleVariant empty;

	m_pBrowserApp->Navigate2(vPIDL,
		COleVariant((long) dwFlags, VT_I4),
		COleVariant(lpszTargetFrameName, VT_BSTR),
		empty, empty);
}

void CHView::Navigate2(LPCTSTR lpszURL, DWORD dwFlags /* = 0 */,
	LPCTSTR lpszTargetFrameName /* = NULL */,
	LPCTSTR lpszHeaders /* = NULL */,
	LPVOID lpvPostData /* = NULL */, DWORD dwPostDataLen /* = 0 */)
{
	ASSERT(m_pBrowserApp != NULL);

	COleSafeArray vPostData;
	if (lpvPostData != NULL)
	{
		if (dwPostDataLen == 0)
			dwPostDataLen = lstrlen((LPCTSTR) lpvPostData);

		vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
	}

	COleVariant vURL(lpszURL, VT_BSTR);
	COleVariant vHeaders(lpszHeaders, VT_BSTR);
	COleVariant vTargetFrameName(lpszTargetFrameName, VT_BSTR);
	COleVariant vFlags((long) dwFlags, VT_I4);

	m_pBrowserApp->Navigate2(vURL,
		vFlags, vTargetFrameName, vPostData, vHeaders);
}

void CHView::Navigate2(LPCTSTR lpszURL, DWORD dwFlags,
	CByteArray& baPostData, LPCTSTR lpszTargetFrameName /* = NULL */,
	LPCTSTR lpszHeaders /* = NULL */)
{
	UNUSED_ALWAYS(lpszURL);
	UNUSED_ALWAYS(dwFlags);
	UNUSED_ALWAYS(lpszTargetFrameName);
	UNUSED_ALWAYS(baPostData);
	UNUSED_ALWAYS(lpszHeaders);

	ASSERT(m_pBrowserApp != NULL);
/*
	COleVariant vURL;

	m_pBrowserApp->Navigate2(bstrURL,
		COleVariant((long) dwFlags, VT_I4),
		COleVariant(lpszTargetFrameName, VT_BSTR),
		COleVariant(),
		COleVariant(lpszHeaders, VT_BSTR));
*/
}

void CHView::PutProperty(LPCTSTR lpszProperty, const VARIANT& vtValue)
{
	ASSERT(m_pBrowserApp != NULL);

	String strProp(lpszProperty);
	BSTR bstrProp = strProp.AllocSysString();
	m_pBrowserApp->PutProperty(bstrProp, vtValue);
	::SysFreeString(bstrProp);
}

BOOL CHView::GetProperty(LPCTSTR lpszProperty, String& strValue)
{
	ASSERT(m_pBrowserApp != NULL);

	String strProperty(lpszProperty);
	BSTR bstrProperty = strProperty.AllocSysString();

	BOOL bResult = FALSE;
	VARIANT vReturn;
	vReturn.vt = VT_BSTR;
	vReturn.bstrVal = NULL;
	HRESULT hr = m_pBrowserApp->GetProperty(bstrProperty, &vReturn);

	if (SUCCEEDED(hr))
	{
		strValue = String(vReturn.bstrVal);
		bResult = TRUE;
	}

	::SysFreeString(bstrProperty);
	return bResult;
}

COleVariant CHView::GetProperty(LPCTSTR lpszProperty)
{
	COleVariant result;

	static BYTE parms[] =
		VTS_BSTR;
	m_wndBrowser.InvokeHelper(0x12f, DISPATCH_METHOD,
		VT_VARIANT, (void*)&result, parms, lpszProperty);

	return result;
}

String CHView::GetFullName() const
{
	ASSERT(m_pBrowserApp != NULL);

	BSTR bstr;
	m_pBrowserApp->get_FullName(&bstr);
	String retVal(bstr);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
// CHView event reflectors

void CHView::NavigateComplete2(LPDISPATCH /* pDisp */, VARIANT* URL)
{
	ASSERT(V_VT(URL) == VT_BSTR);

	USES_CONVERSION;

	String str = OLE2T(V_BSTR(URL));
	OnNavigateComplete2(str);
}

void CHView::BeforeNavigate2(LPDISPATCH /* pDisp */, VARIANT* URL,
		VARIANT* Flags, VARIANT* TargetFrameName,
		VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	ASSERT(V_VT(URL) == VT_BSTR);
	ASSERT(V_VT(TargetFrameName) == VT_BSTR);
	ASSERT(V_VT(PostData) == (VT_VARIANT | VT_BYREF));
	ASSERT(V_VT(Headers) == VT_BSTR);
	ASSERT(Cancel != NULL);

	USES_CONVERSION;

	VARIANT* vtPostedData = V_VARIANTREF(PostData);
	CByteArray array;
	if (V_VT(vtPostedData) & VT_ARRAY)
	{
		// must be a vector of bytes
		ASSERT(vtPostedData->parray->cDims == 1 && vtPostedData->parray->cbElements == 1);

		vtPostedData->vt |= VT_UI1;
		COleSafeArray safe(vtPostedData);

		DWORD dwSize = safe.GetOneDimSize();
		LPVOID pVoid;
		safe.AccessData(&pVoid);

		array.SetSize(dwSize);
		LPBYTE lpByte = array.GetData();

		memcpy(lpByte, pVoid, dwSize);
		safe.UnaccessData();
	}
	// make real parameters out of the notification

	String strTargetFrameName(V_BSTR(TargetFrameName));
	String strURL = V_BSTR(URL);
	String strHeaders = V_BSTR(Headers);
	DWORD nFlags = V_I4(Flags);

	// notify the user's class
	OnBeforeNavigate2(strURL, nFlags, strTargetFrameName,
		array, strHeaders, Cancel);
}

void CHView::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	UNUSED_ALWAYS(pDisp);
	ASSERT(V_VT(URL) == VT_BSTR);

	String str(V_BSTR(URL));
	OnDocumentComplete(str);
}

/////////////////////////////////////////////////////////////////////////////
// CHView Events

void CHView::OnProgressChange(long lProgress, long lProgressMax)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(lProgress);
	UNUSED_ALWAYS(lProgressMax);
}

void CHView::OnCommandStateChange(long lCommand, BOOL bEnable)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(lCommand);
	UNUSED_ALWAYS(bEnable);
}

void CHView::OnDownloadBegin()
{
	// user will override to handle this notification
}

void CHView::OnDownloadComplete()
{
	// user will override to handle this notification
}

void CHView::OnTitleChange(LPCTSTR lpszText)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(lpszText);
}

void CHView::OnPropertyChange(LPCTSTR lpszProperty)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(lpszProperty);
}

void CHView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* bCancel)
{
	// default to continuing
	bCancel = FALSE;

	// user will override to handle this notification
	UNUSED_ALWAYS(ppDisp);
}

void CHView::OnDocumentComplete(LPCTSTR lpszURL)
{
	// user will override to handle this notification
	//REVIEW: this needs a reflector
	UNUSED_ALWAYS(lpszURL);
}

void CHView::OnQuit()
{
	// user will override to handle this notification
}

void CHView::OnVisible(BOOL bVisible)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bVisible);
}

void CHView::OnToolBar(BOOL bToolBar)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bToolBar);
}

void CHView::OnMenuBar(BOOL bMenuBar)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bMenuBar);
}

void CHView::OnStatusBar(BOOL bStatusBar)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bStatusBar);
}

void CHView::OnFullScreen(BOOL bFullScreen)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bFullScreen);
}

void CHView::OnTheaterMode(BOOL bTheaterMode)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(bTheaterMode);
}

void CHView::OnNavigateComplete2(LPCTSTR lpszURL)
{
	// user will override to handle this notification
	UNUSED_ALWAYS(lpszURL);
}

void CHView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
	LPCTSTR lpszTargetFrameName, CByteArray& baPostData,
	LPCTSTR lpszHeaders, BOOL* bCancel)
{
	// default to continuing
	bCancel = FALSE;

	// user will override to handle this notification
	UNUSED_ALWAYS(lpszURL);
	UNUSED_ALWAYS(nFlags);
	UNUSED_ALWAYS(lpszTargetFrameName);
	UNUSED_ALWAYS(baPostData);
	UNUSED_ALWAYS(lpszHeaders);
}

void CHView::OnStatusTextChange(LPCTSTR pszText)
{
	// try to set the status bar text via the frame

	base_wnd* pWnd = GetParent();
	CFrameWnd* pFrame = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);
	if (pFrame != NULL)
		pFrame->SetMessageText(pszText);
}


void CHView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	ModifyStyleEx(0,WS_EX_STATICEDGE, SWP_FRAMECHANGED);
	Navigate2(csHomePage);
}

BOOL CHView::DestroyWindow() 
{
	return CView::DestroyWindow();
}

void CHView::OnWebback() 
{
	GoBack();	
}

void CHView::OnUpdateWebback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CHView::OnWebforward() 
{
	GoForward();
	
}

void CHView::OnUpdateWebforward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CHView::OnWebhome() 
{
	Navigate2(csHomePage);
}

void CHView::OnUpdateWebhome(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CHView::OnWebrefresh() 
{
	Refresh();
	
}

void CHView::OnUpdateWebrefresh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CHView::OnWebstop() 
{
	Stop();
	
}

void CHView::OnUpdateWebstop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetBusy());
	
}

void CHView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnRButtonDown(nFlags, point);
}

void CHView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnRButtonUp(nFlags, point);
}
