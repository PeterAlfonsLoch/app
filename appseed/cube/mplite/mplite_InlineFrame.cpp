#include "StdAfx.h"
#include "InlineFrame.h"


InlineFrame::InlineFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp)
{

   m_dataid = "InlineFrame";
   m_bCustomFrame = false;
   m_etranslucency = TranslucencyNone;

}

InlineFrame::~InlineFrame()
{
}

void InlineFrame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_frame_window::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &InlineFrame::_001OnEraseBkgnd);
}

int InlineFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
   System.add_frame(this);

   // CResizeBar implements in-place resizing.
/*   if (!m_wndResizeBar.create(this))
   {
      TRACE0("Failed to create resize bar\n");
      return -1;      // fail to create
   }*/

   // By default, it is a good idea to register a drop-target that does
   //  nothing with your frame ::ca::window.  This prevents drops from
   //  "falling through" to a container that supports drag-drop.
//   m_dropTarget.Register(this);

   return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame ::ca::window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame ::ca::window
//  and will be NULL when the container is an SDI application.  A server
//  application can place ca2 API control bars on either ::ca::window.
BOOL InlineFrame::OnCreateControlBars(frame_window* pWndFrame, frame_window* pWndDoc)
{
   UNREFERENCED_PARAMETER(pWndFrame);
   // remove this if you use pWndDoc
   UNREFERENCED_PARAMETER(pWndDoc);

   // Set owner to this ::ca::window, so messages are delivered to correct cast
/*   m_wndToolBar.SetOwner(this);

   // create toolbar on client's frame ::ca::window
   if (!m_wndToolBar.CreateEx(pWndFrame) ||
      !m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
   {
      TRACE0("Failed to create toolbar\n");
      return FALSE;
   }

   // Set owner to this ::ca::window, so messages are delivered to correct cast
   m_wndDlgBar.SetOwner(this);

   // create dialog bar on client's frame ::ca::window
   if (!m_wndDlgBar.create(pWndFrame, IDR_SRVR_INPLACE,
      CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
   {
      TRACE0("Failed to create dialogbar\n");
      return FALSE;
   }

   // Set the owner of this ::ca::window, so messages are delivered to correct cast
   m_wndReBar.SetOwner(this);

   // create a rebar on client's frame ::ca::window
   if (!m_wndReBar.create(pWndFrame) ||
      !m_wndReBar.AddBar(&m_wndToolBar) ||
      !m_wndReBar.AddBar(&m_wndDlgBar))
   {
      TRACE0("Failed to create rebar\n");
      return FALSE;
   }

   // TODO: remove this if you don't want tool tips
   m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);
   m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);*/

   return TRUE;
}

BOOL InlineFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs

   return simple_frame_window::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// InlineFrame diagnostics

#ifdef _DEBUG
void InlineFrame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void InlineFrame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}
#endif //_DEBUG



void InlineFrame::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}
