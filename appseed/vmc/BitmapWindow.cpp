// BitmapWindow.cpp : implementation file
//

#include "StdAfx.h"
#include "VmcApp.h"
#include "BitmapWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapWindow

CBitmapWindow::CBitmapWindow(UINT nIDBitmapResource)
{
	if(!m_bitmap.LoadBitmap(nIDBitmapResource))
	{
		throw 1;
	}
}

CBitmapWindow::~CBitmapWindow()
{

}

/*
BEGIN_MESSAGE_MAP(CBitmapWindow, base_wnd)
	//{{AFX_MSG_MAP(CBitmapWindow)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CBitmapWindow message handlers

void CBitmapWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC dcMem;

	dcMem.CreateCompatibleDC(&dc);
	CBitmap * pOldBitmap = dcMem.SelectObject(&m_bitmap);
	// TODO: Add your message handler code here
	
	class rect rect;
	GetClientRect(&rect);

	dc.BitBlt(
		0, 0,
		rect.Width(), rect.Height(),
		&dcMem,
		0, 0,
		SRCCOPY);
	dc.SetTextAlign(TA_LEFT | TA_BOTTOM);
	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	dc.DrawText(
		m_strStatus,
		&rect,
		DT_BOTTOM | DT_RIGHT);
	
	dcMem.SelectObject(pOldBitmap);
	// Do not call base_wnd::OnPaint() for painting messages
}

BOOL CBitmapWindow::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	class size &size = m_bitmap.GetBitmapDimension();
	
	cs.cx = size.cx;
	cs.cy = size.cy;
	cs.x = (::GetSystemMetrics(SM_CXSCREEN) - size.cx) / 2;
	cs.y = (::GetSystemMetrics(SM_CYSCREEN) - size.cy) / 2;

	return base_wnd::PreCreateWindow(cs);
}

void CBitmapWindow::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	base_wnd::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		BITMAP bm;
		m_bitmap.GetBitmap(&bm);
		class size &size = m_bitmap.GetBitmapDimension();
		int x = (::GetSystemMetrics(SM_CXSCREEN) - bm.bmWidth) / 2;
		int y = (::GetSystemMetrics(SM_CYSCREEN) - bm.bmHeight) / 2;
		SetWindowPos(
			NULL,
			x, y,
			bm.bmWidth, bm.bmHeight,
			SWP_SHOWWINDOW);
		SetTimer(1, 1000, NULL);
	}
	// TODO: Add your message handler code here
	
}

void CBitmapWindow::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CVmcApp * pApp = CVmcApp::app(get_app());
	ASSERT(pApp != NULL);
	pApp->m_evWait.SetEvent();
	KillTimer(nIDEvent);
	base_wnd::OnTimer(nIDEvent);
}

void CBitmapWindow::SetStatus(string &str)
{
	m_strStatus = str;
//	CPaintDC dc(this); // device context for painting
	
	CDC * pDC = GetDC();

	class rect rect;
	GetClientRect(&rect);
	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
	pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 255));
	rect.top = rect.bottom - 20;
	pDC->DrawText(
		m_strStatus,
		&rect,
		DT_BOTTOM | DT_RIGHT);
	
	ReleaseDC(pDC);
	// Do not call base_wnd::OnPaint() for painting messages
}
