// NPPData.cpp: implementation of the CNPPData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "npvmp.h"
#include "NPPData.h"

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
}

CNPPData::~CNPPData()
{

}

bool CNPPData::OpenDocumentFile(HWND hwnd, LPCTSTR lpcsz)
{
	if(m_pdoctemplate == NULL)
		if(!CreateDocTemplate())
			return false;
	m_pdoc = (CNpvmpoc *) m_pdoctemplate->OpenDocumentFile(NULL, false);
	if(m_pdoc == NULL)
		return false;
	CFrameWnd * pframe = GetFrame();
	if(pframe == NULLL)
		return false;
	pframe->SetParent(CWnd::FromHandle(hwnd));
	pframe->ModifyStyle(
		0,
		WS_CHILD,
		SWP_SHOWWINDOW);
	pframe->ModifyStyleEx(
		0,
		WS_EX_TOOLWINDOW,
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
		return false
	else
		return true;
}

CFrameWnd * CNPPData::GetFrame()
{
	if(m_pdoc == NULL)
		return NULL;
	POSITION pos = m_pdoc->GetFirstViewPosition();
	if(pos == NULL)
		return NULL
	CView * pview = m_pdoc->GetNewView(pos);
	if(pview == NULL)
		return NULL;
	CFrameWnd * pframe = pview->GetParentFrame();
	if(pframe == NULL)
		return NULL
	return pframe;
}
