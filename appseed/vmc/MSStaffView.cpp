// MSStaffView.cpp : implementation file
//

#include "StdAfx.h"
#include "../vmsp/resource.h"
#include "VmcApp.h"
#include "../vms/Vms.h"
#include "MSStaffView.h"

#include "MSDoc.h"
#include "MSTrack.h"
#include "MSEventSymbol.h"
#include "MSEvents.h"

#include "MainFrame.h"
#include "MSDoc.h"


CMSStaffView::CMSStaffView(::ca::application * papp) :
   ::ca::ca(papp),
   Ex1VirtualGuieInterface(papp),
   BaseVirtualGuie(papp),
   Ex1ScrollViewInterface(papp),
   BaseScrollView(papp)
{
    m_bOnSizeEnabled = false;
    TRACE(_T("MSStaffView this = %x \n"), this);
}

CMSStaffView::~CMSStaffView()
{
}

/*

BEGIN_MESSAGE_MAP(CMSStaffView, BaseScrollView)
	//{{AFX_MSG_MAP(CMSStaffView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()*/

/////////////////////////////////////////////////////////////////////////////
// CMSStaffView drawing

void CMSStaffView::OnInitialUpdate()
{
    
	BaseScrollView::OnInitialUpdate();

    m_fontSymbols.DeleteObject();
    m_fontSymbols.CreatePointFont(120, _T("Anastasia Regular"), &m_dcScreen);
//	class size sizeTotal;
	// TODO: calculate the total size of this view
//	sizeTotal.cx = sizeTotal.cy = 100;
//	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMSStaffView::OnDraw(CDC* pDC)
{
	CSingleLock slGdi(&m_csGdi, TRUE);
	class rect rectClipBox;
	m_dcScreen.GetClipBox(&rectClipBox);
    class rect rectBuffer = rectClipBox;
    class point ptScrollPosition = GetScrollPosition();
    rectBuffer -= ptScrollPosition;
    TRACE(_T("CMSStaffView::OnDraw right %d, top %d, left %d, bottom %d\n"), rectClipBox.right, rectClipBox.top, rectClipBox.left, rectClipBox.bottom);
	if(!m_dcScreen.BitBlt(
		rectClipBox.left,
		rectClipBox.top,
		rectClipBox.Width(),
		rectClipBox.Height(), 
		&m_dcBuffer,
		rectBuffer.left,
		rectBuffer.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 
	else
	{
//		TRACE(_T("OnDraw:\n"));
//		TRACE(_T("rect.left  : %d\n"), rect.left);
//		TRACE(_T("rect.top   : %d\n"), rect.top);
//		TRACE(_T("rect.right : %d\n"), rect.right);
//		TRACE(_T("rect.bottom: %d\n"), rect.bottom);


	} 
	GdiFlush();

}

/////////////////////////////////////////////////////////////////////////////
// CMSStaffView diagnostics

#ifdef _DEBUG
void CMSStaffView::AssertValid() const
{
	BaseScrollView::AssertValid();
}

void CMSStaffView::Dump(CDumpContext& dc) const
{
	BaseScrollView::Dump(dc);
}

CMSDoc * CMSStaffView::GetDocument() // non-debug version is inline
{
   ASSERT(base < CMSDoc >::bases(m_pDocument));
	return dynamic_cast < CMSDoc * > (m_pDocument);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSStaffView message handlers

void CMSStaffView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint) 
{
   CMSDoc * pDoc = GetDocument();

   class size sizeTotal;
   // TODO: calculate the total size of this view
   sizeTotal.cx = pDoc->GetMaxTracksPixelsSizeX();
   sizeTotal.cy = 100;
   SetScrollSizes(MM_TEXT, sizeTotal);
   m_bOnSizeEnabled = true;
   class rect rect;
   base_wnd::GetClientRect(rect);
   UpdateBufferImage(rect.right, rect.bottom);
   UpdateBuffer();
}

BOOL CMSStaffView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
    CVmcApp * pApp = CVmcApp::app(get_app());
	ASSERT(pApp != NULL);
	cs.lpszClass = pApp->m_XFViewClassName;
	return BaseScrollView::PreCreateWindow(cs);
}

int CMSStaffView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CVmcApp * pApp = CVmcApp::app(get_app());
	ASSERT(pApp != NULL);
	
   m_dcScreen.Attach(base_wnd::GetDC()->GetSafeHdc());
	if(!m_dcBuffer.CreateCompatibleDC(&m_dcScreen))
	{
		pApp->Exit();
	}
	m_bmpBufferOld.Attach(m_dcBuffer.GetCurrentBitmap());
/*	if(!m_dcBack.CreateCompatibleDC(&m_dcScreen))
	{
		pApp->Exit();
	}
	m_bmpBackOld.Attach(m_dcBack.GetCurrentBitmap());
	if(!m_dcScaled.CreateCompatibleDC(&m_dcScreen))
	{
		pApp->Exit();
	}
	m_bmpScaledOld.Attach(m_dcScaled.GetCurrentBitmap());

	TRACE(_T("GdiGetBatchLimit %d"), GdiGetBatchLimit());
	GdiSetBatchLimit(1);
	// TODO: Add your specialized creation code here

	// TODO: Add your specialized creation code here */
	
	return 0;
}

void CMSStaffView::UpdateBufferImage(int cx, int cy)
{
    DWORD timeIn = timeGetTime();
    TRACE(_T("CMSStaffView::UpdateBackgroundImage timeIn %d\n"), timeIn);
	CVmcApp * pApp = CVmcApp::app(get_app());
    if(pApp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return;
    }
    ASSERT(pApp != NULL);
	CMainFrame * pFrame = dynamic_cast < CMainFrame *> (pApp->m_pMainWnd);
    if(pFrame == NULL)
    {
        // if main frame is null, there's no reason
        // for painting anything...
        return;
    }
    if(cx <= 0 || cy <= 0)
        return;
    ASSERT(pFrame != NULL);
	CMSDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL); // if document is null, there's something wrong
//	CDBCentral * pDataCentral = DB();
//	CMainFrame *pFrame;
//	pFrame = (CMainFrame *) pApp->m_pMainWnd;
	if(!::IsWindow(get_handle()))
		return;
	m_csGdi.Lock();
	const int ciBufferBitmapNotCreated = 1;
	const int ciBackBitmapNotCreated = 2;
	const int ciBufferBitmapNotSelected = 3;
	const int ciBackBitmapNotSelected = 4;
	const int ciBufferBitmapInfoNotAvailable = 5;
	const int ciScaledBitmapInfoNotAvailable = 6;
try
{	
    BITMAP bmDbl;
    if(m_bmpBuffer.get_handle() != NULL)
    {
	    if(!m_bmpBuffer.GetBitmap(&bmDbl))
	    {
		    TRACE0("Buffer Bitmap info not got.\n");
		    throw ciBufferBitmapInfoNotAvailable;
	    }
    }
    if(m_bmpBuffer.get_handle() == NULL ||
        bmDbl.bmWidth < cx ||
        bmDbl.bmHeight < cy)
    {
	    m_dcBuffer.SelectObject(&m_bmpBufferOld);
	    m_bmpBuffer.DeleteObject();
	    if(!m_bmpBuffer.CreateCompatibleBitmap(&m_dcScreen, cx, cy))
	    {
		    TRACE(_T("GetLastError%d"), GetLastError());
		    TRACE(_T("CreateCompatibleBitmap Error\n"));
		    //TRACELASTERROR();
		    throw ciBufferBitmapNotCreated;
	    }

		    if(!(m_dcBuffer.SelectObject(&m_bmpBuffer)))
		    {
			    
			    TRACE(_T("GetLastError%d"), GetLastError());
			    TRACE0("Buffer Bitmap not selected.\n");
			    //TRACELASTERROR();
			    throw ciBufferBitmapNotSelected;
		    }
    }
}
catch(int iError)
{
	TRACE(_T("CMSStaffView::UpdateBackgroundImage Exception %d\n"), iError);
}
	Render(true);
	m_csGdi.Unlock();
	//RECT rect;
	//CDC *pDC = GetDC();
	//GetActiveWindow()->GetClientRect(&rect);
//	pDC->SetMapMode(
//	pDC->DPtoLP(&rect);
	// TODO: Add your message handler code here

    DWORD timeOut = timeGetTime();
    TRACE(_T("CMSStaffView::UpdateBackgroundImage timeOut %d\n"), timeOut);
    TRACE(_T("CMSStatXfplayerView::UpdateBackgroundImage timeTotal %d\n"), timeOut - timeIn);


}

void CMSStaffView::UpdateBuffer()
{
    const int ciBufferBitmapInfoNotAvailable = 5;
	m_csGdi.Lock();
	BITMAP bmDbl;
	if(!m_bmpBuffer.GetBitmap(&bmDbl))
	{
		TRACE0("Buffer Bitmap info not got.\n");
		throw ciBufferBitmapInfoNotAvailable;
	}
    m_dcBuffer.FillSolidRect(0, 0, bmDbl.bmWidth, bmDbl.bmHeight, GetSysColor(COLOR_WINDOW));
    CMSDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
    CMSTrack * lpTrack;
    BaseArray<CMSTrack *,
        CMSTrack *> * lpTracks = pDoc->GetTracks();
    VMSRESULT vmsr;
    for(int iTrack = 0; iTrack < lpTracks->GetSize(); iTrack++)
    {
        class rect rect;
        m_dcBuffer.GetClipBox(rect);
        class point ptScrollPosition = GetScrollPosition();
        class size sizeTotal, sizePage, sizeLine;
        int nMapMode;
        GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
        ASSERT(nMapMode == MM_TEXT);
        lpTrack = lpTracks->ElementAt(iTrack);
        CMSEvents * lpEvents = lpTrack->GetEvents();
        CMSEventSymbol eventSymbol;
        CMSEvent * lpEventSymbol;
        int iPosition = 0;
        int iIndex;
        iIndex = 0;
        m_dcBuffer.SelectObject(&m_fontSymbols);
        if(VMS_SUCCEEDED(vmsr = lpEvents->GetPositionEventSymbol(
            &lpEventSymbol, 
            ptScrollPosition.x,
            &iIndex,
            &iPosition)) &&
            vmsr != VMSR_S_NOTFOUND)
        {
            eventSymbol = *lpEventSymbol;
            string str;
            while(iPosition - ptScrollPosition.x <  sizePage.cx)
            {
                str = "";
                int iOffsetY = eventSymbol.GetPositionY();
                iOffsetY = MulDiv(iOffsetY, m_dcBuffer.GetDeviceCaps(LOGPIXELSY), 72);
                if(eventSymbol.GetSymbol() == CMSEventSymbol::cushSymbolQuarterNoteUp)
                {
                    str += (TCHAR) 113;
                    m_dcBuffer.TextOut(iPosition - ptScrollPosition.x, (iTrack + 1) * 50 + iOffsetY, str);
                }
                else if(eventSymbol.GetSymbol() == CMSEventSymbol::cushSymbolEighthNoteUp)
                {
                    str += (TCHAR) 101;
                    m_dcBuffer.TextOut(iPosition - ptScrollPosition.x, (iTrack + 1) * 50 + iOffsetY, str);
                }
                if(VMS_FAILED(vmsr = lpEvents->GetNextEventSymbol(&lpEventSymbol, iIndex, &iIndex))
                    || (vmsr == VMSR_S_NOTFOUND))
                    break;
                eventSymbol = *lpEventSymbol;
                iPosition += eventSymbol.GetPositionX();
            }
        }

    }

	m_csGdi.Unlock();

}

void CMSStaffView::Render(CRgn *pRgn, BOOL bGdiLocked)
{
	//CSingleLock sl(&m_csGdi, !boolTRUE);
	if(!bGdiLocked)
		m_csGdi.Lock();
	class rect rect;
	pRgn->GetRgnBox(&rect);
	m_dcScreen.SelectClipRgn(NULL);
	if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 
	else
	{
//		TRACE(_T("OnDraw:\n"));
//		TRACE(_T("rect.left  : %d\n"), rect.left);
//		TRACE(_T("rect.top   : %d\n"), rect.top);
//		TRACE(_T("rect.right : %d\n"), rect.right);
//		TRACE(_T("rect.bottom: %d\n"), rect.bottom);


	} 
	GdiFlush();
	
	if(!bGdiLocked)
		m_csGdi.Unlock();

}

void CMSStaffView::Render(LPRECT lpRect, BOOL bGdiLocked)
{
	//CSingleLock sl(&m_csGdi, TRUE);
	if(!bGdiLocked)
		m_csGdi.Lock();
	class rect rect;
	rect = *lpRect;
	m_dcScreen.SelectClipRgn(NULL);
	if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 
	else
	{
//		TRACE(_T("OnDraw:\n"));
//		TRACE(_T("rect.left  : %d\n"), rect.left);
//		TRACE(_T("rect.top   : %d\n"), rect.top);
//		TRACE(_T("rect.right : %d\n"), rect.right);
//		TRACE(_T("rect.bottom: %d\n"), rect.bottom);


	} 
	GdiFlush();
	if(!bGdiLocked)
		m_csGdi.Unlock();

	


}

void CMSStaffView::Render(BOOL bGdiLocked)
{
//	CSingleLock sl(&m_csGdi, TRUE);
	if(!bGdiLocked)
		m_csGdi.Lock();
	class rect rect;
   base_wnd::GetClientRect(&rect);
	m_dcScreen.SelectClipRgn(NULL);
	if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 
	else
	{
//		TRACE(_T("OnDraw:\n"));
//		TRACE(_T("rect.left  : %d\n"), rect.left);
//		TRACE(_T("rect.top   : %d\n"), rect.top);
//		TRACE(_T("rect.right : %d\n"), rect.right);
//		TRACE(_T("rect.bottom: %d\n"), rect.bottom);


	} 
	GdiFlush();
	if(!bGdiLocked)
		m_csGdi.Unlock();


}

void CMSStaffView::OnSize(UINT nType, int cx, int cy) 
{
	BaseScrollView::OnSize(nType, cx, cy);
	if(m_bOnSizeEnabled)
	{
//		m_dwOnSizeUpdateTimeIn = timeGetTime();
		BaseView::OnSize(nType, cx, cy);
		UpdateBufferImage(cx, cy);
//		Render();
//		m_bOnSizeUpdateTimerOn = true;
	}
	// TODO: Add your message handler code here
	
}

BOOL CMSStaffView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateBuffer();
	return BaseScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}


