// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#include "StdAfx.h"




view::view()
{
   m_ulFlags         |= ::ca::ca::flag_auto_delete;
}

view::~view()
{
   if(m_spdocument.is_set())
      m_spdocument->remove_view(this);
}

void view::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::user::interaction::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_VIEW, pinterface, this, &view::_001OnView);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);

/* ON_WM_MOUSEACTIVATE()

   // Standard commands for split pane
   ON_COMMAND_EX(ID_WINDOW_SPLIT, &view::OnSplitCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_SPLIT, &view::OnUpdateSplitCmd)

   // Standard commands for next pane
   ON_UPDATE_COMMAND_UI(ID_NEXT_PANE, &view::OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_NEXT_PANE, &view::OnNextPaneCmd)
   ON_UPDATE_COMMAND_UI(ID_PREV_PANE, &view::OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_PREV_PANE, &view::OnNextPaneCmd)
   //}}AFX_MSG_MAP
   // special command for Initial Update
   ON_MESSAGE_VOID(WM_INITIALUPDATE, view::OnInitialUpdate) */

}


/////////////////////////////////////////////////////////////////////////////
// ::view second phase construction - bind to document

BOOL view::PreCreateWindow(CREATESTRUCT & cs)
{
   ASSERT(cs.style & WS_CHILD);

   if (cs.lpszClass == NULL)
   {
      // COLOR_WINDOW background
      VERIFY(System.DeferRegisterClass(AFX_WNDFRAMEORVIEW_REG, &cs.lpszClass));
   }

   if (cs.style & WS_BORDER)
   {
      cs.dwExStyle |= WS_EX_CLIENTEDGE;
      cs.style &= ~WS_BORDER;
   }

   return TRUE;
}

void view::_001OnCreate(::gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::create, pcreate, pobj);

   if(pcreate->previous())
      return;

   // if ok, wire in the current document
   ASSERT(::view::get_document() == NULL);
   ::ca::create_context* pContext = (::ca::create_context*)pcreate->m_lpcreatestruct->lpCreateParams;

   // A ::view should be created in a given context!
   if (pContext != NULL && pContext->m_user->m_pCurrentDoc != NULL)
   {
      pContext->m_user->m_pCurrentDoc->add_view(this);
      ASSERT(::view::get_document() != NULL);
   }
   else
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: Creating a pane with no document.\n");
   }

   pcreate->set_lresult(0);
}

void view::_001OnDestroy(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   frame_window* pFrame = GetParentFrame();
   if (pFrame != NULL && pFrame->GetActiveView() == this)
      pFrame->SetActiveView(NULL);    // deactivate during death
//   ::user::interaction::OnDestroy();
}

// self destruction
void view::PostNcDestroy()
{
   ::user::interaction::PostNcDestroy();
   if(is_set_ca_flag(::ca::ca::flag_auto_delete))
   {
      // default for views is to allocate them on the heap
      //  the default post-cleanup is to 'delete this'.
      //  never explicitly call 'delete' on a ::view
      delete_this();
   }
}

void view::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
/* trans   ENSURE_ARG(lpClientRect != NULL);
   if (nAdjustType != 0)
   {
      // allow for special client-edge style
      ::AdjustWindowRectEx(lpClientRect, 0, FALSE, GetExStyle());

      // default behavior for in-place editing handles scrollbars
      DWORD dwStyle = GetStyle();
      if (dwStyle & WS_VSCROLL)
      {
         int nAdjust = afxData.cxVScroll;
         if (dwStyle & WS_BORDER)
            nAdjust -= CX_BORDER;
         lpClientRect->right += nAdjust;
      }
      if (dwStyle & WS_HSCROLL)
      {
         int nAdjust = afxData.cyHScroll;
         if (dwStyle & WS_BORDER)
            nAdjust -= CY_BORDER;
         lpClientRect->bottom += nAdjust;
      }
      return;
   }*/

   // call default to place borders outside of client rect
   ::user::interaction::CalcWindowRect(lpClientRect, nAdjustType);
}

/////////////////////////////////////////////////////////////////////////////
// Command routing

bool view::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   
{
   // first pump through pane
   if (::user::interaction::_001OnCmdMsg(pcmdmsg))
      return TRUE;

   // then pump through document
   if (::view::get_document() != NULL)
   {
      // special state for saving ::view before routing to document
      if(::view::get_document()->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }

   if(!GetParent()->IsFrameWnd())
   {
      if(GetParent()->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }

   return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ::view drawing support

void view::OnPaint()
{
   // standard paint routine
// trans   CPaintDC spgraphics(this);
//   trans OnPrepareDC(&spgraphics);
//   trans OnDraw(&spgraphics);
}

document * view::get_document(::user::interaction * pguie)
{
   ::view * pview = dynamic_cast < ::view * > (pguie);
   if(pview != NULL)
      return NULL;
   return pview->get_document();
}

void view::_001OnInitialUpdate(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   on_update(NULL, 0, NULL);        // initial update
}

void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint)
{
   if(pHint != NULL)
   {
      if(base < view_update_hint > ::bases(pHint))
      {
         view_update_hint * puh = dynamic_cast < view_update_hint * > (pHint);
         OnViewUpdateHint(pSender, lHint, puh);
      }
   }
   ASSERT(pSender != this);
   UNUSED(pSender);     // unused in release builds

   // invalidate the entire pane, erase background too
   //Invalidate(TRUE);
}

void view::OnViewUpdateHint(::view * pSender, LPARAM lHint, view_update_hint * pHint)
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
   UNREFERENCED_PARAMETER(pHint);
}

void view::OnDraw(::ca::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
}


/////////////////////////////////////////////////////////////////////////////
// ::view selection support

BOOL view::IsSelected(const ::radix::object* pDocItem) const
{
   ASSERT_VALID(pDocItem);
   UNUSED(pDocItem);    // unused in release builds

   return FALSE;   // not implemented, so not selected
}

void view::OnActivateView(BOOL bActivate, ::view * pActivateView, ::view *)
{
   UNUSED(pActivateView);   // unused in release builds

   if (bActivate)
   {
      ASSERT(pActivateView == this);

      // take the focus if this frame/::view/pane is now active
// trans      if (IsTopParentActive())
      //trans   SetFocus();
   }
}

void view::OnActivateFrame(UINT /*nState*/, frame_window* /*pFrameWnd*/)
{
}

/* trans
int view::OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message)
{
   int nResult = ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
      return nResult;   // frame does not want to activate

   frame_window* pParentFrame = GetParentFrame();
   if (pParentFrame != NULL)
   {
      // eat it if this will cause activation
      ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

      // either re-activate the current ::view, or set this ::view to be active
      ::view * pview = pParentFrame->GetActiveView();
      HWND hWndFocus = ::GetFocus();
      if (pview == this &&
         get_handle() != hWndFocus && !::IsChild(get_handle(), hWndFocus))
      {
         // re-activate this ::view
         OnActivateView(TRUE, this, this);
      }
      else
      {
         // activate this ::view
         pParentFrame->SetActiveView(this);
      }
   }
   return nResult;
}
*/

/////////////////////////////////////////////////////////////////////////////
// ::view scrolling support

BOOL view::OnScroll(UINT /*nScrollCode*/, UINT /*nPos*/, BOOL /*bDoScroll*/)
{
   return FALSE;
}

BOOL view::OnScrollBy(size /*sizeScroll*/, BOOL /*bDoScroll*/)
{
   return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ::view drag/drop support

///*DROPEFFECT view::OnDragScroll(DWORD /*dwKeyState*/, point /*point*/)
//{
//#ifndef _AFX_NO_OLE_SUPPORT
  // return DROPEFFECT_SCROLL; // this means do the default
//#else
  // return 0;
//#endif
//}

//DROPEFFECT view::OnDragEnter(COleDataObject* /*pDataObject*/,
  // DWORD /*dwKeyState*/, point /*point*/)
//{
  // return 0;   // DROPEFFECT_NONE
//}

//DROPEFFECT view::OnDragOver(COleDataObject* /*pDataObject*/,
   //DWORD /*dwKeyState*/, point /*point*/)
//{
   //return 0;   // DROPEFFECT_NONE
//}

//BOOL view::OnDrop(COleDataObject* /*pDataObject*/,
   //DROPEFFECT /*dropEffect*/, point /*point*/)
//{
  // return FALSE;
//}

//DROPEFFECT view::OnDropEx(COleDataObject* /*pDataObject*/,
  // DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, point /*point*/)
//{
  // return (DROPEFFECT)-1;  // not implemented
//}

//void view::OnDragLeave()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// ::view splitting commands


CScrollBar* view::GetScrollBarCtrl(int nBar) const
{
   ASSERT(nBar == SB_HORZ || nBar == SB_VERT);
// trans   if (GetStyle() & ((nBar == SB_HORZ) ? WS_HSCROLL : WS_VSCROLL))
//   {
      // it has a regular windows style scrollbar (no control)
//      return NULL;
//   }


   return NULL;
}


void view::OnUpdateSplitCmd(cmd_ui* pCmdUI)
{
   UNREFERENCED_PARAMETER(pCmdUI);
   /*ENSURE_ARG(pCmdUI != NULL);
   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
   pCmdUI->Enable(pSplitter != NULL && !pSplitter->IsTracking());*/
}

BOOL view::OnSplitCmd(UINT)
{
/*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
   if (pSplitter == NULL)
      return FALSE;

   ASSERT(!pSplitter->IsTracking());
   pSplitter->DoKeyboardSplit();*/
   return TRUE;    // attempted at least
}

void view::OnUpdateNextPaneMenu(cmd_ui* pCmdUI)
{
   UNREFERENCED_PARAMETER(pCmdUI);
   /*ASSERT(pCmdUI->m_nID == ID_NEXT_PANE ||
      pCmdUI->m_nID == ID_PREV_PANE);
   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
   pCmdUI->Enable(pSplitter != NULL &&
      pSplitter->CanActivateNext(pCmdUI->m_nID == ID_PREV_PANE));*/
}

BOOL view::OnNextPaneCmd(UINT nID)
{
   UNREFERENCED_PARAMETER(nID);
/*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
   if (pSplitter == NULL)
      return FALSE;

   ASSERT(nID == ID_NEXT_PANE || nID == ID_PREV_PANE);
   pSplitter->ActivateNext(nID == ID_PREV_PANE);*/
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Printing support virtual functions (others in viewpr.cpp)

void view::OnPrepareDC(::ca::graphics * pgraphics, CPrintInfo* pInfo)
{
   UNREFERENCED_PARAMETER(pInfo);
   ASSERT_VALID(pgraphics);
   UNUSED(pgraphics); // unused in release builds

   // Default to one page printing if doc length not known
}




/////////////////////////////////////////////////////////////////////////////
// ::view diagnostics

#ifdef _DEBUG
void view::dump(dump_context & dumpcontext) const
{
   ::user::interaction::dump(dumpcontext);

   if (::view::get_document() != NULL)
      dumpcontext << "with document: ";
   else
      dumpcontext << "with no document\n";
}

void view::assert_valid() const
{
   ::user::interaction::assert_valid();
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCtrlView

// // BEGIN_MESSAGE_MAP(CCtrlView, ::view)
// xxx   ON_WM_PAINT()
// // END_MESSAGE_MAP()

CCtrlView::~CCtrlView()
{
}

CCtrlView::CCtrlView(const char * lpszClass, DWORD dwStyle)
{
   m_strClass = lpszClass;
   m_dwDefaultStyle = dwStyle;
}

BOOL CCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
   ASSERT(cs.lpszClass == NULL);
   cs.lpszClass = m_strClass;

   // initialize common controls
   VERIFY(System.DeferRegisterClass(AFX_WNDCOMMCTLS_REG, NULL));
   System.DeferRegisterClass(AFX_WNDCOMMCTLSNEW_REG, NULL);

   // ::collection::map default ::view style to default style
   // WS_BORDER is insignificant
   /*if ((cs.style | WS_BORDER) == AFX_WS_DEFAULT_VIEW)
      cs.style = m_dwDefaultStyle & (cs.style | ~WS_BORDER);*/

   return view::PreCreateWindow(cs);
}

void CCtrlView::OnDraw(::ca::graphics *)
{
   ASSERT(FALSE);
}

void CCtrlView::OnPaint()
{
   // this is done to avoid view::OnPaint
// trans   Default();
}

/////////////////////////////////////////////////////////////////////////////
// CCtrlView diagnostics

#ifdef _DEBUG
void CCtrlView::dump(dump_context & dumpcontext) const
{
   view::dump(dumpcontext);
   dumpcontext << "\nClass Name: " << m_strClass;
   dumpcontext << "\nDefault Style: ";
   dumpcontext.dumpAsHex(m_dwDefaultStyle);
}

void CCtrlView::assert_valid() const
{
   ::user::interaction::assert_valid();
   ASSERT(!m_strClass.is_empty());
}
#endif //_DEBUG


void view::_001OnView(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::base, pbase, pobj)
   if(pbase->m_wparam == 0)
   {
      document::update * pupdate = (document::update *) pbase->m_lparam;
      on_update(pupdate->m_pSender, pupdate->m_lHint, pupdate->m_pHint);
   }
}


// // IMPLEMENT_DYNAMIC for ::view is in wincore.cpp for .OBJ granularity reasons

// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for swap tuning
// IMPLEMENT_DYNAMIC(CCtrlView, ::view)

/////////////////////////////////////////////////////////////////////////////

::user::interaction* view::create_view(::ca::type_info info, document * pdoc, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast)
{
   ::ca::create_context_sp cacc(get_app());
   stacker < ::user::create_context > cc(cacc->m_user);
   cc->m_typeinfoNewView    = &info;
   cc->m_pLastView          = pviewLast;
   if(pdoc == NULL)
   {
      cc->m_pCurrentDoc        = get_document();
   }
   else
   {
      cc->m_pCurrentDoc = pdoc;
   }
   if(pwndParent == NULL)
   {
      pwndParent = this;
   }
   if(id == NULL)
   {
      id = cc->m_typeinfoNewView.raw_name();
   }
   return s_create_view(cacc, pwndParent, id);
}


::user::interaction* view::s_create_view(::ca::type_info info, document * pdoc, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast)
{
   ::ca::create_context_sp cacc(pdoc->get_app());
   stacker < ::user::create_context > cc(cacc->m_user);
   cc->m_typeinfoNewView    = &info;
   cc->m_pLastView          = pviewLast;
   cc->m_pCurrentDoc        = pdoc;
   return s_create_view(cacc, pwndParent, id);
}

::user::interaction* view::s_create_view(::ca::create_context* pContext, ::user::interaction * pwndParent, id id)
{
// trans   ASSERT(pwndParent->get_handle() != NULL);
// trans   ASSERT(::IsWindow(pwndParent->get_handle()));
   ASSERT(pContext != NULL);
   ASSERT(pContext->m_user->m_typeinfoNewView || pContext->m_user->m_puiNew != NULL);

   ::ca::application * papp = pwndParent->get_app();

   ::user::interaction * pguie;
   if(pContext->m_user->m_puiNew != NULL)
   {
      pguie = dynamic_cast < ::user::interaction * > (pContext->m_user->m_puiNew);
   }
   else
   {
      // Note: can be a ::user::interaction with PostNcDestroy self cleanup
      pguie = dynamic_cast < ::user::interaction * > (App(papp).alloc(pContext->m_user->m_typeinfoNewView));
      if (pguie == NULL)
      {
//         TRACE1("Warning: Dynamic create of ::view type %hs failed.\n", pContext->m_typeinfoNewView.raw_name());
         return NULL;
      }
   }
   ASSERT_KINDOF(::user::interaction, pguie);

   // views are always created with a border!
   if (!pguie->create(NULL, NULL, WS_VISIBLE | WS_CHILD, rect(0,0,0,0), pwndParent, id, pContext))
   {
      //TRACE0("Warning: could not create ::view for frame.\n");
      return NULL;        // can't continue without a ::view
   }

   ::view * pview = dynamic_cast < ::view * > (pguie);
   if(pview != NULL)
   {
      pview->_001OnInitialUpdate(NULL);
   }
/*   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
   {
      // remove the 3d style from the frame, since the ::view is
      //  providing it.
      // make sure to recalc the non-client area
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   return pguie;
}


void view::_001OnLButtonDown(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::gen::message::mouse, pmouse, pobj);
   GetParentFrame()->SetActiveView(this);
}

void view::_001OnLButtonUp(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::gen::message::mouse, pmouse, pobj);
}

void view::_001OnMouseMove(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::gen::message::mouse, pmouse, pobj);
}


document * view::get_document() const
 { 
    ASSERT(this != NULL); 
    return m_spdocument; 
 }

 ::ca::data * view::get_data() const
 { 
    ASSERT(this != NULL); 
    if(m_spdata.is_set())
       return m_spdata;
    if(m_spdocument.is_set() && m_spdocument->get_data() != NULL)
       return m_spdocument->get_data();
    return NULL;
 }

void view::collaborate(::ca::job * pjob)
{
   {
      ::user::job * puserjob = (dynamic_cast < ::user::job * > (pjob));
      if(puserjob != NULL)
      {
         puserjob->m_pview = this;
      }
   }
}



int view::get_total_page_count(::ca::job * pjob)
{
   UNREFERENCED_PARAMETER(pjob);
   return 1;
}



view_update_hint::view_update_hint(::ca::application * papp) :
ca(papp)
{
}
