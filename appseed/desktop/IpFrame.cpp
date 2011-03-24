// IpFrame.cpp : implementation of the InPlaceFrame class
//

#include "stdafx.h"
#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InPlaceFrame

IMPLEMENT_DYNCREATE(InPlaceFrame, OleIPFrameWnd)

BEGIN_MESSAGE_MAP(InPlaceFrame, OleIPFrameWnd)
	//{{AFX_MSG_MAP(InPlaceFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, OleIPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, OleIPFrameWnd::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OleIPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, OleIPFrameWnd::OnContextHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InPlaceFrame construction/destruction

InPlaceFrame::InPlaceFrame()
{
   _001InstallMessageHandling(this);
   m_etranslucency = TranslucencyNone;

}

InPlaceFrame::~InPlaceFrame()
{
}

int InPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (OleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   igui::AppInterface  * papp = igui::AppGet();
   papp->AddFrame(this);


	// CResizeBar implements in-place resizing.
/*	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}*/

	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
//	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
BOOL InPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Remove this if you use pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Set owner to this window, so messages are delivered to correct app
/*	m_wndToolBar.SetOwner(this);

	// Create toolbar on client's frame window
	if (!m_wndToolBar.CreateEx(pWndFrame) ||
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// Set owner to this window, so messages are delivered to correct app
	m_wndDlgBar.SetOwner(this);

	// Create dialog bar on client's frame window
	if (!m_wndDlgBar.Create(pWndFrame, IDR_SRVR_INPLACE,
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return FALSE;
	}

	// Set the owner of this window, so messages are delivered to correct app
	m_wndReBar.SetOwner(this);

	// Create a rebar on client's frame window
	if (!m_wndReBar.Create(pWndFrame) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return FALSE;
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);*/

	return TRUE;
}

BOOL InPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return OleIPFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// InPlaceFrame diagnostics

#ifdef _DEBUG
void InPlaceFrame::AssertValid() const
{
	OleIPFrameWnd::AssertValid();
}

void InPlaceFrame::Dump(CDumpContext& dc) const
{
	OleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// InPlaceFrame commands


/////////////////////////////////////////////////////////////////////////////
// InPlaceChildFrame

IMPLEMENT_DYNCREATE(InPlaceChildFrame, BaseFrameWnd)

BEGIN_MESSAGE_MAP(InPlaceChildFrame, BaseFrameWnd)
	//{{AFX_MSG_MAP(InPlaceChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, BaseFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, BaseFrameWnd::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, BaseFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, BaseFrameWnd::OnContextHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InPlaceChildFrame construction/destruction

InPlaceChildFrame::InPlaceChildFrame()
{
   _001InstallMessageHandling(this);
   m_etranslucency = TranslucencyNone;

}

InPlaceChildFrame::~InPlaceChildFrame()
{
}

int InPlaceChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (BaseFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   igui::AppInterface  * papp = igui::AppGet();
   papp->AddFrame(this);


	// CResizeBar implements in-place resizing.
/*	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}*/

	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
//	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
BOOL InPlaceChildFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Remove this if you use pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Set owner to this window, so messages are delivered to correct app
/*	m_wndToolBar.SetOwner(this);

	// Create toolbar on client's frame window
	if (!m_wndToolBar.CreateEx(pWndFrame) ||
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// Set owner to this window, so messages are delivered to correct app
	m_wndDlgBar.SetOwner(this);

	// Create dialog bar on client's frame window
	if (!m_wndDlgBar.Create(pWndFrame, IDR_SRVR_INPLACE,
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return FALSE;
	}

	// Set the owner of this window, so messages are delivered to correct app
	m_wndReBar.SetOwner(this);

	// Create a rebar on client's frame window
	if (!m_wndReBar.Create(pWndFrame) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return FALSE;
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);*/

	return TRUE;
}

BOOL InPlaceChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return BaseFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// InPlaceChildFrame diagnostics

#ifdef _DEBUG
void InPlaceChildFrame::AssertValid() const
{
	BaseFrameWnd::AssertValid();
}

void InPlaceChildFrame::Dump(CDumpContext& dc) const
{
	BaseFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// InPlaceChildFrame commands
