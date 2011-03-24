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

IMPLEMENT_DYNAMIC(html_edit_doc, CDocument)


html_edit_doc::html_edit_doc()
{
}

html_edit_doc::~html_edit_doc()
{
}

CHtmlEditView* html_edit_doc::GetView() const
{
	CHtmlEditView* pHtmlView = NULL;

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		pHtmlView = DYNAMIC_DOWNCAST(CHtmlEditView, pView);
		if (pHtmlView != NULL)
			break;
	}

	return pHtmlView;
}

void html_edit_doc::DeleteContents()
{
	CHtmlEditView* pView = GetView();
	if (pView)
	{
		pView->NewDocument();
		pView->Navigate(pView->GetStartDocument());
	}
}

BOOL html_edit_doc::IsModified()
{
	CHtmlEditView* pView = GetView();

	if (pView)
	{
		return (pView->GetIsDirty() != S_FALSE);
	}

	return FALSE;
}

BOOL html_edit_doc::OpenURL(LPCTSTR lpszURL)
{
	BOOL bRet = FALSE;
	CHtmlEditView* pView = GetView();
	if (pView != NULL && lpszURL != NULL && *lpszURL != '\0')
	{
		pView->Navigate(lpszURL);
		bRet = TRUE;
	}

	return bRet;
}

BOOL html_edit_doc::OnOpenDocument(LPCTSTR lpszFileName)
{
	BOOL bRet = FALSE;
	CHtmlEditView* pView = GetView();
	if (pView != NULL)
	{
		pView->Navigate(lpszFileName);
		SetTitle(lpszFileName);
		bRet = TRUE;
	}

	return bRet;
}

BOOL html_edit_doc::OnSaveDocument(LPCTSTR lpszFileName)
{
	BOOL bRet = FALSE;
	CHtmlEditView *pView = GetView();
	if (pView != NULL)
	{
		CFile file;
		if (file.Open(lpszFileName, CFile::modeCreate|CFile::modeWrite))
		{
			CArchive ar(&file, CArchive::store);
			CArchiveStream as(&ar);
			CComPtr<IHTMLDocument2> spHTMLDocument;
			CComQIPtr<IPersistStreamInit> spPSI;
			pView->GetDHtmlDocument(&spHTMLDocument);
			if (spHTMLDocument)
			{
				spPSI = spHTMLDocument;
				if (spPSI)
				{
					if (S_OK == spPSI->Save((IStream*)&as, TRUE))
					{
						SetModifiedFlag(FALSE);
						bRet = TRUE;
					}
				}
			}
		}
	}
	return bRet;
}

BOOL html_edit_doc::OnNewDocument()
{
#ifdef _DEBUG
	if(IsModified())
		TRACE(traceAppMsg, 0, "Warning: OnNewDocument replaces an unsaved document.\n");
#endif

	DeleteContents(); // we want html_edit_doc's DeleteContents to be called here
	m_strPathName.Empty();      // no path name yet
	SetModifiedFlag(FALSE);     // make clean

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// html_edit_doc diagnostics

#ifdef _DEBUG
void html_edit_doc::AssertValid() const
{
	CDocument::AssertValid();
}

void html_edit_doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif _DEBUG




} // namespace mshtml