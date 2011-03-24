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

IMPLEMENT_DYNCREATE(html_edit_view, html_view)

/////////////////////////////////////////////////////////////////////////////
// html_edit_view
BEGIN_MESSAGE_MAP(html_edit_view, CFormView)
	ON_COMMAND(ID_FILE_PRINT, &html_edit_view::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &html_edit_view::OnFilePrint)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// html_edit_view

void html_edit_view::OnPaint()
{
	Default();
}

html_edit_view::html_edit_view()
{
}

html_edit_view::~html_edit_view()
{
}

LPCTSTR html_edit_view::GetStartDocument()
{
	LPCTSTR szDefaultUrl = _T("about:blank");
	return szDefaultUrl;
}

BOOL html_edit_view::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
	DWORD dwStyle, const RECT& rect, base_wnd* pParentWnd, UINT nID,
	CCreateContext* pContext) 
{
	// create the view window itself
	if (!html_view::Create(lpszClassName, lpszWindowName,
				dwStyle, rect, pParentWnd,	nID, pContext))
	{
		return FALSE;
	}
	LPCTSTR szDoc = GetStartDocument();
	if (szDoc)
		Navigate(szDoc);
	return TRUE;
}

BOOL html_edit_view::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo)
{
	// if it's not something we're intersted in, let it go to the base
	if (nCode < (int)CN_UPDATE_COMMAND_UI)
		return html_view::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

	// check for command availability
	BOOL bHasExecFunc = FALSE;
	UINT uiElemType = AFX_UI_ELEMTYPE_NORMAL;
	UINT dhtmlCmdID = GetDHtmlCommandMapping(nID, bHasExecFunc, uiElemType);
	if (dhtmlCmdID == AFX_INVALID_DHTML_CMD_ID)
	{
		// No mapping for this command. Use normal routing
		return html_view::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}

	long nStatus = QueryStatus(dhtmlCmdID);

	if (nCode == CN_UPDATE_COMMAND_UI)
	{
		// just checking status
		CCmdUI *pUI = static_cast<CCmdUI*>(pExtra);
		if (pUI)
		{
			if(!(nStatus & OLECMDF_LATCHED || nStatus & OLECMDF_ENABLED))
			{
				pUI->Enable(FALSE);
				if (uiElemType & AFX_UI_ELEMTYPE_CHECBOX)
				{
					if (nStatus & OLECMDF_LATCHED)
						pUI->SetCheck(TRUE);
					else
						pUI->SetCheck(FALSE);
				}
				else if (uiElemType & AFX_UI_ELEMTYPE_RADIO)
				{
					if (nStatus & OLECMDF_LATCHED)
						pUI->SetRadio(TRUE);
					else
						pUI->SetRadio(FALSE);
				}

			}
			else
			{
				pUI->Enable(TRUE); // enable
				// check to see if we need to do any other state
				// stuff
				if (uiElemType & AFX_UI_ELEMTYPE_CHECBOX)
				{
					if (nStatus & OLECMDF_LATCHED)
						pUI->SetCheck(TRUE);
					else
						pUI->SetCheck(FALSE);
				}
				else if (uiElemType & AFX_UI_ELEMTYPE_RADIO)
				{
					if (nStatus & OLECMDF_LATCHED)
						pUI->SetRadio(TRUE);
					else
						pUI->SetRadio(FALSE);
				}
			}
			return TRUE;
		}
		return FALSE;
	}

	// querystatus for this DHTML command to make sure it is enabled
	if(!(nStatus & OLECMDF_LATCHED || nStatus & OLECMDF_ENABLED))
	{

		// trying to execute a disabled command
		TRACE(traceHtml, 0, "Not executing disabled dhtml editing command %d", dhtmlCmdID);
		return TRUE;
	}

	if (bHasExecFunc)
	{
		return ExecHandler(nID);		
	}

	return S_OK == ExecCommand(dhtmlCmdID, OLECMDEXECOPT_DODEFAULT, NULL, NULL) ? TRUE : FALSE;
}

BOOL html_edit_view::GetDHtmlDocument(IHTMLDocument2 **ppDocument) const
{
	CComPtr<IDispatch> spDispDocument;
	if (!ppDocument)
		return FALSE;
	*ppDocument = NULL;

	HRESULT hr = m_pBrowserApp->get_Document(&spDispDocument);
	if (SUCCEEDED(hr) && spDispDocument)
	{
		return S_OK == spDispDocument->QueryInterface(ppDocument) ? TRUE : FALSE;
	}

	return FALSE;
}

void html_edit_view::OnNavigateComplete2(LPCTSTR strURL)
{
	SetDesignMode(TRUE);
}

BOOL html_edit_view::OnPreparePrinting(CPrintInfo* pInfo)
{
	return TRUE;
}

UINT html_edit_view::GetDHtmlCommandMapping(UINT nIDWindowsCommand, BOOL& bHasExecFunc, UINT& uiElemType)
{
	uiElemType = AFX_UI_ELEMTYPE_NORMAL;
	bHasExecFunc = FALSE;
	return AFX_INVALID_DHTML_CMD_ID;
}

BOOL html_edit_view::ExecHandler(UINT nCmdID)
{
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// html_edit_view diagnostics

#ifdef _DEBUG
void html_edit_view::AssertValid() const
{
	CFormView::AssertValid();
}

void html_edit_view::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

} // namespace mshtml