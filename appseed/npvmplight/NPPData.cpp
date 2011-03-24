// NPPData.cpp: implementation of the CNPPData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "npvmpLight.h"
#include "NPPData.h"
#include "NpvmpLightFrame.h"
#include "NpvmpLightCntrItem.h"
#include "vmsp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNPPData::CNPPData()
{
	m_hwndParent = NULL;
	m_pdoctemplate = NULL;
	m_pdoc = NULL;
}

CNPPData::~CNPPData()
{

}

bool CNPPData::OpenDocumentFile(HWND hwnd, LPCTSTR lpcsz)
{
	if(m_pdoctemplate == NULL)
		if(!CreateDocTemplate())
			return false;
	if(m_pdoc == NULL)
	{
		m_pdoc = (CNpvmpDoc *) m_pdoctemplate->OpenDocumentFile(lpcsz, false);
		if(m_pdoc == NULL)
			return false;
	}
	CFrameWnd * pframe = GetFrame();
	if(pframe == NULL)
		return false;
	pframe->SetParent(base_wnd::FromHandle(hwnd));
	pframe->ModifyStyle(
		WS_CAPTION
		| WS_OVERLAPPED
		| WS_THICKFRAME,
		WS_CHILD,
		SWP_SHOWWINDOW);
	pframe->ModifyStyleEx(
		WS_EX_CLIENTEDGE,
		WS_EX_TOOLWINDOW,
		SWP_SHOWWINDOW);
	CView * pview = GetView();
	if(pview == NULL)
		return false;
	pview->ModifyStyleEx(
		WS_EX_CLIENTEDGE,
		0,
		SWP_SHOWWINDOW);
	return true;
}

bool CNPPData::CreateDocTemplate()
{
	m_pdoctemplate = new CSingleDocTemplate(
		IDR_CONTAINER,
		RUNTIME_CLASS(CNpvmpDoc),
		RUNTIME_CLASS(CNpvmpFrame),
		RUNTIME_CLASS(CNpvmpView));
	if(m_pdoctemplate == NULL)
		return false;
	else
		return true;
}

CFrameWnd * CNPPData::GetFrame()
{
	if(m_pdoc == NULL)
		return NULL;
	POSITION pos = m_pdoc->GetFirstViewPosition();
	if(pos == NULL)
		return NULL;
	CView * pview = m_pdoc->GetNextView(pos);
	if(pview == NULL)
		return NULL;
	CFrameWnd * pframe = pview->GetParentFrame();
	if(pframe == NULL)
		return NULL;
	return pframe;
}

CView * CNPPData::GetView()
{
	if(m_pdoc == NULL)
		return NULL;
	POSITION pos = m_pdoc->GetFirstViewPosition();
	if(pos == NULL)
		return NULL;
	CView * pview = m_pdoc->GetNextView(pos);
	if(pview == NULL)
		return NULL;
	return pview;
}

bool CNPPData::OpenPlayerFile()
{
	if(m_hwndParent == NULL)
		return false;
	CNpvmpView * pview = (CNpvmpView *) GetView();
	if(pview == NULL)
	{
		OpenDocumentFile(m_hwndParent, NULL);
		UpdateWindowPos();
		pview = (CNpvmpView *) GetView();
		pview->InsertObject();
	}
	if(!m_strFilePath.IsEmpty())
	{
		LPCTSTR lpcsz = m_strFilePath;
		CNpvmpCntrItem * pitem = pview->m_pSelection;
		LPDISPATCH lpDispatch = NULL;
		VERIFY(
			SUCCEEDED(
				pitem->m_lpObject->QueryInterface(
					IID_IDispatch,
					(void**) &lpDispatch)));
		IXfplayer iplayer;
		iplayer.AttachDispatch(lpDispatch);
		iplayer.OpenFile(lpcsz, false);
	}

}

void CNPPData::UpdateWindowPos()
{
	CFrameWnd * pframe = GetFrame();
	if(pframe != NULL)
	{
		pframe->SetWindowPos(
			&base_wnd::wndTop,
			0, 0,
			m_rectLast.Width(),
			m_rectLast.Height(),
			SWP_SHOWWINDOW);
	}

}
