// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

namespace mshtml
{


extern "C" void _AfxHtmlEditCtrlFakeEntry()
{
	ASSERT( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlEditCtrl
CHtmlEditCtrl::CHtmlEditCtrl()
{
}

CHtmlEditCtrl::~CHtmlEditCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlEditCtrl message handlers
BEGIN_EVENTSINK_MAP(CHtmlEditCtrl, base_wnd)
	ON_EVENT_REFLECT(CHtmlEditCtrl, 252 /* NavigateComplete2 */, _OnNavigateComplete2, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

void CHtmlEditCtrl::_OnNavigateComplete2(LPDISPATCH pDisp, VARIANT FAR* URL)
{
	SetDesignMode(TRUE);
}


BOOL CHtmlEditCtrl::GetDHtmlDocument(IHTMLDocument2 **ppDocument) const
{
	if(ppDocument == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	
	*ppDocument = NULL;
	
	CHtmlEditCtrl *pThis = const_cast<CHtmlEditCtrl*>(this);
	CComQIPtr<IWebBrowser2> pBrowserApp = pThis->GetControlUnknown();
	ASSERT(pBrowserApp != NULL);
	if (pBrowserApp)
	{
		CComPtr<IDispatch> spDispDocument;
		HRESULT hr = pBrowserApp->get_Document(&spDispDocument);
		if (SUCCEEDED(hr) && spDispDocument)
		{
			return S_OK == spDispDocument->QueryInterface(ppDocument) ? TRUE : FALSE;
		}
	}
	return FALSE;
}

BOOL CHtmlEditCtrl::Create(LPCTSTR lpszWindowName, DWORD /*dwStyle*/, const RECT& rect, base_wnd* pParentWnd,
						   int nID, CCreateContext *pContext) 
{
	BOOL bRet = FALSE;
	// create the control window

	AfxEnableControlContainer();
	if (CreateControl(CLSID_WebBrowser, lpszWindowName,
				WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID))
	{
		// in order to put the webbrowser in design mode, you must
		// first load a document into it. "about:blank" seems to
		// be the safest thing to load for a good starting point.
		CComQIPtr<IWebBrowser2> pBrowserApp = GetControlUnknown();
		ASSERT(pBrowserApp);
		if (pBrowserApp)
		{
			CComVariant vEmpty;
			LPCTSTR szDoc = GetStartDocument();
			if (szDoc)
			{
				CComBSTR bstrStart(szDoc);
				if (S_OK == pBrowserApp->Navigate(bstrStart, 
													&vEmpty,
													&vEmpty,
													&vEmpty,
													&vEmpty))
				{
					bRet = TRUE;
				}
			}
			else
				bRet = TRUE;

		}
	}

	if (!bRet)
		DestroyWindow();
	return bRet;
}

LPCTSTR CHtmlEditCtrl::GetStartDocument()
{
	LPCTSTR szDefaultDoc = _T("about:blank");
	return szDefaultDoc;
}




} // namespace mshtml