// This is ca API library.
//
//
//
//
//
//
//
//




   // like ON_MESSAGE but no return value
   /*#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, ::ca::Sig_vv, \
   (__PMSG)(__PMSGW)(void (__MSG_CALL ::user::interaction::*)())&memberFxn },*/
   // IMPLEMENT_DYNAMIC(::user::view, ::user::interaction)

   /////////////////////////////////////////////////////////////////////////////
   // ::user::view

   // BEGIN_MESSAGE_MAP(::user::view, ::user::interaction)
   //{{__MSG_MAP(::user::view)
   /*   ON_WM_PAINT()
   ON_WM_MOUSEACTIVATE()

   ON_WM_DESTROY()

   // Standard commands for split pane
   ON_COMMAND_EX(ID_WINDOW_SPLIT, OnSplitCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_SPLIT, OnUpdateSplitCmd)

   // Standard commands for next pane
   ON_UPDATE_COMMAND_UI(ID_NEXT_PANE, OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_NEXT_PANE, OnNextPaneCmd)
   ON_UPDATE_COMMAND_UI(ID_PREV_PANE, OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_PREV_PANE, OnNextPaneCmd)
   //}}__MSG_MAP
   // special command for Initial Update
   ON_MESSAGE_VOID(WM_INITIALUPDATE, OnInitialUpdate)*/
   // END_MESSAGE_MAP()
#include "framework.h"


#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children


namespace user
{


   view::view()
   {

      m_ulFlags         |= ::ca::ca::flag_auto_delete;

   }


   view::~view()
   {
      if(m_spdocument.is_set())
         m_spdocument->remove_view(this);
   }

   void view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_VIEW, pinterface, this, &view::_001OnView);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_INITIALUPDATE  , pinterface, this, &view::_001OnInitialUpdate);

//      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_MBUTTONDOWN    , pinterface, this, &view::_001OnMButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);


      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE  , pinterface, this, &view::_001OnMouseActivate);
//      IGUI_WIN_MSG_LINK(WM_DESTROY        , pinterface, this, &view::_001OnDestroy);
  //    IGUI_WIN_MSG_LINK(WM_CREATE        , pinterface, this, &view::_001OnCreate);

      // Standard commands for split pane
//  //      connect_command(ID_WINDOW_SPLIT , &view::_001OnSplitCmd);
      //    connect_update_cmd_ui(ID_WINDOW_SPLIT ,  &view::_001OnUpdateSplitCmd);

      // Standard commands for next pane
      //  connect_update_cmd_ui(ID_NEXT_PANE    , &view::_001OnUpdateNextPaneMenu);
      //connect_command(ID_NEXT_PANE   , &view::_001OnNextPaneCmd);
      //      connect_update_cmd_ui(ID_PREV_PANE    , &view::_001OnUpdateNextPaneMenu);
      //    connect_command(ID_PREV_PANE    , &view::_001OnNextPaneCmd);

      //}}__MSG_MAP
      // special command for Initial Update


      /* ON_WM_MOUSEACTIVATE()

      // Standard commands for split pane
      ON_COMMAND_EX(ID_WINDOW_SPLIT, &view::OnSplitCmd)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_SPLIT, &view::OnUpdateSplitCmd)

      // Standard commands for next pane
      ON_UPDATE_COMMAND_UI(ID_NEXT_PANE, &view::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_NEXT_PANE, &view::OnNextPaneCmd)
      ON_UPDATE_COMMAND_UI(ID_PREV_PANE, &view::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_PREV_PANE, &view::OnNextPaneCmd)
      //}}__MSG_MAP
      // special command for Initial Update
      ON_MESSAGE_VOID(WM_INITIALUPDATE, view::OnInitialUpdate) */

   }


   /////////////////////////////////////////////////////////////////////////////
   // ::user::view second phase construction - bind to ::user::document_interface

   bool view::pre_create_window(CREATESTRUCT & cs)
   {

      ASSERT(cs.style & WS_CHILD);

      if (cs.style & WS_BORDER)
      {
#ifdef WINDOWSEX
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
#endif
         cs.style &= ~WS_BORDER;
      }

      return TRUE;

   }


   void view::_001OnCreate(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::create, pcreate, pobj);

      if(pcreate->previous())
         return;

      // if ok, wire in the current ::user::document_interface
      ASSERT(::user::view::get_document() == ::null());
      sp(::ca::create_context) pContext = pcreate->m_lpcreatestruct->lpCreateParams;

      // A ::user::view should be created in a given context!
      if (pContext != ::null() && pContext->m_user->m_pCurrentDoc != ::null())
      {
         pContext->m_user->m_pCurrentDoc->add_view(this);
         ASSERT(::user::view::get_document() != ::null());
      }
      else
      {
         TRACE(::ca::trace::category_AppMsg, 0, "Warning: Creating a pane with no ::user::document_interface.\n");
      }

      pcreate->set_lresult(0);
   }

   void view::_001OnDestroy(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      sp(::user::frame_window) pFrame = GetParentFrame();
      if (pFrame != ::null() && pFrame->GetActiveView() == this)
         pFrame->SetActiveView(::null());    // deactivate during death
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
         //  never explicitly call 'delete' on a ::user::view
         delete_this();
      }
   }

   void view::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {
      /* trans   ENSURE_ARG(lpClientRect != ::null());
      if (nAdjustType != 0)
      {
      // allow for special client-edge style
      ::AdjustWindowRectEx(lpClientRect, 0, FALSE, GetExStyle());

      // default behavior for in-place editing handles scrollbars
      uint32_t dwStyle = GetStyle();
      if (dwStyle & WS_VSCROLL)
      {
      int32_t nAdjust = afxData.cxVScroll;
      if (dwStyle & WS_BORDER)
      nAdjust -= CX_BORDER;
      lpClientRect->right += nAdjust;
      }
      if (dwStyle & WS_HSCROLL)
      {
      int32_t nAdjust = afxData.cyHScroll;
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
      sp(::user::interaction) pwndex;
      if(base < ::user::view > ::bases(get_parent()))
      {
         pwndex = (get_parent().m_p);
         if(pwndex != ::null())
         {
            if (pwndex->_001OnCmdMsg(pcmdmsg))
               return TRUE;
         }
      }

      // then pump through document
      if (::user::view::get_document() != ::null())
      {
         if(::user::view::get_document()->_001OnCmdMsg(pcmdmsg))
            return TRUE;
         sp(::user::view) pview = ::user::view::get_document()->get_view(0);
         ASSERT_VALID(pview);
         if (pview != this
            && pview != get_parent())
         {
            pwndex = (pview);
            if(pwndex != ::null())
            {
               if(pwndex->::user::interaction::_001OnCmdMsg(pcmdmsg))
                  return TRUE;
            }
         }

      }


      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::user::view drawing support

   void view::OnPaint()
   {
      // standard paint routine
      // trans   CPaintDC spgraphics(this);
      //   trans OnPrepareDC(&spgraphics);
      //   trans OnDraw(&spgraphics);
   }

   sp(::user::document_interface) view::get_document(sp(::user::interaction) pguie)
   {
      sp(::user::view) pview =  (pguie.m_p);
      if(pview != ::null())
         return ::null();
      return pview->get_document();
   }

   void view::_001OnInitialUpdate(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      on_update(::null(), 0, ::null());        // initial update
   }

   void view::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object* pHint)
   {
      if(pHint != ::null())
      {
         if(base < ::user::view_update_hint > ::bases(pHint))
         {
            ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint * > (pHint);
            OnViewUpdateHint(pSender, lHint, puh);
         }
      }
      if(lHint >= hint_begin && lHint < hint_end)
      {
         on_simple_view_update_hint(pSender, (e_hint) lHint, pHint);
      }
      ASSERT(pSender != this);
      UNUSED(pSender);     // unused in release builds

      // invalidate the entire pane, erase background too
      //Invalidate(TRUE);
   }

   void view::on_simple_view_update_hint(sp(::user::view) pviewSender, e_hint ehint, ::ca::object * phint)
   {

      switch(ehint)
      {
      case hint_set_edit_file:
         {
            post_simple_command(simple_command_set_edit_file, (LPARAM) phint);
         }
         break;
      default:
         break;
      };

   }

   void view::OnViewUpdateHint(sp(::user::view) pSender, LPARAM lHint, ::user::view_update_hint * pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::user::view selection support

   bool view::IsSelected(const ::ca::object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
      UNUSED(pDocItem);    // unused in release builds

      return FALSE;   // not implemented, so not selected
   }

   void view::OnActivateView(bool bActivate, sp(::user::view) pActivateView, sp(::user::view))
   {
      UNUSED(pActivateView);   // unused in release builds

      if (bActivate)
      {
         ASSERT(pActivateView == this);

         // take the focus if this frame/::user::view/pane is now active
         // trans      if (IsTopParentActive())
         //trans   SetFocus();
      }
   }

   void view::OnActivateFrame(UINT /*nState*/, sp(::user::frame_window) /*pFrameWnd*/)
   {
   }

   /* trans
   int32_t view::OnMouseActivate(sp(::ca::window) pDesktopWnd, UINT nHitTest, UINT message)
   {
   int32_t nResult = ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
   return nResult;   // frame does not want to activate

   sp(::user::frame_window) pParentFrame = GetParentFrame();
   if (pParentFrame != ::null())
   {
   // eat it if this will cause activation
   ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

   // either re-activate the current ::user::view, or set this ::user::view to be active
   sp(::user::view) pview = pParentFrame->GetActiveView();
   oswindow oswindow_Focus = ::GetFocus();
   if (pview == this &&
   get_handle() != oswindow_Focus && !::IsChild(get_handle(), oswindow_Focus))
   {
   // re-activate this ::user::view
   OnActivateView(TRUE, this, this);
   }
   else
   {
   // activate this ::user::view
   pParentFrame->SetActiveView(this);
   }
   }
   return nResult;
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // ::user::view scrolling support

   bool view::OnScroll(UINT /*nScrollCode*/, UINT /*nPos*/, bool /*bDoScroll*/)
   {
      return FALSE;
   }

   bool view::OnScrollBy(size /*sizeScroll*/, bool /*bDoScroll*/)
   {
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::user::view drag/drop support

   ///*DROPEFFECT view::OnDragScroll(uint32_t /*dwKeyState*/, point /*point*/)
   //{
   //#ifndef ___NO_OLE_SUPPORT
   // return DROPEFFECT_SCROLL; // this means do the default
   //#else
   // return 0;
   //#endif
   //}

   //DROPEFFECT view::OnDragEnter(COleDataObject* /*pDataObject*/,
   // uint32_t /*dwKeyState*/, point /*point*/)
   //{
   // return 0;   // DROPEFFECT_NONE
   //}

   //DROPEFFECT view::OnDragOver(COleDataObject* /*pDataObject*/,
   //uint32_t /*dwKeyState*/, point /*point*/)
   //{
   //return 0;   // DROPEFFECT_NONE
   //}

   //bool view::OnDrop(COleDataObject* /*pDataObject*/,
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
   // ::user::view splitting commands


   CScrollBar* view::GetScrollBarCtrl(int32_t nBar) const
   {

      ///ASSERT(nBar == SB_HORZ || nBar == SB_VERT);
      // trans   if (GetStyle() & ((nBar == SB_HORZ) ? WS_HSCROLL : WS_VSCROLL))
      //   {
      // it has a regular windows style scrollbar (no control)
      //      return ::null();
      //   }


      return ::null();
   }


   void view::OnUpdateSplitCmd(cmd_ui* pCmdUI)
   {
      UNREFERENCED_PARAMETER(pCmdUI);
      /*ENSURE_ARG(pCmdUI != ::null());
      CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      pCmdUI->Enable(pSplitter != ::null() && !pSplitter->IsTracking());*/
   }

   bool view::OnSplitCmd(UINT)
   {
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      if (pSplitter == ::null())
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
      pCmdUI->Enable(pSplitter != ::null() &&
      pSplitter->CanActivateNext(pCmdUI->m_nID == ID_PREV_PANE));*/
   }

   bool view::OnNextPaneCmd(UINT nID)
   {
      UNREFERENCED_PARAMETER(nID);
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      if (pSplitter == ::null())
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
   // ::user::view diagnostics


   void view::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      if (((view *) this)->::user::view::get_document() != ::null())
         dumpcontext << "with ::user::document_interface: ";
      else
         dumpcontext << "with no ::user::document_interface\n";
   }

   void view::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }




   void view::_001OnView(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::base, pbase, pobj)
         if(pbase->m_wparam == 0)
         {
            ::user::document_interface::update * pupdate = (::user::document_interface::update *) pbase->m_lparam;
            on_update(pupdate->m_pSender, pupdate->m_lHint, pupdate->m_pHint);
         }
   }


   sp(::user::interaction) view::create_view(::ca::type_info * pinfo, sp(::user::document_interface) pdoc, sp(::user::interaction) pwndParent, id id, sp(::user::interaction) pviewLast)
   {

      sp(::ca::type_info) info(pinfo);

      sp(::ca::create_context) cacc(allocer());

      stacker < ::user::create_context > cc(cacc->m_user);

      cc->m_typeinfoNewView    = info;

      cc->m_pLastView          = pviewLast;

      if(pdoc == ::null())
      {
         cc->m_pCurrentDoc        = get_document();
      }
      else
      {
         cc->m_pCurrentDoc = pdoc;
      }

      if(pwndParent == ::null())
      {
         pwndParent = this;
      }

      if(id.is_empty())
      {

         id = (const ::id &) cc->m_typeinfoNewView->name();

      }

      return s_create_view(cacc, pwndParent, id);

   }


   sp(::user::interaction) view::s_create_view(::ca::type_info * pinfo, sp(::user::document_interface) pdoc, sp(::user::interaction) pwndParent, id id, sp(::user::interaction) pviewLast)
   {

      sp(::ca::type_info) info(pinfo);

      sp(::ca::create_context) cacc(pdoc->allocer());

      stacker < ::user::create_context > cc(cacc->m_user);

      cc->m_typeinfoNewView    = info;

      cc->m_pLastView          = pviewLast;

      cc->m_pCurrentDoc        = pdoc;

      return s_create_view(cacc, pwndParent, id);

   }

   sp(::user::interaction) view::s_create_view(::ca::create_context * pContext, sp(::user::interaction) pwndParent, id id)
   {

      // trans   ASSERT(pwndParent->get_handle() != ::null());
      // trans   ASSERT(::IsWindow(pwndParent->get_handle()));

      ASSERT(pContext != ::null());

      ASSERT(pContext->m_user->m_typeinfoNewView || pContext->m_user->m_puiNew != ::null());


      sp(::ca::application) papp = pwndParent->get_app();

      sp(::user::interaction) pguie;

      if(pContext->m_user->m_puiNew != ::null())
      {

         pguie =  (pContext->m_user->m_puiNew.m_p);

      }
      else
      {

         // Note: can be a ::user::interaction with PostNcDestroy self cleanup
         pguie = App(papp).alloc(pContext->m_user->m_typeinfoNewView);
         if (pguie == ::null())
         {
            //         TRACE1("Warning: Dynamic create of ::user::view type %hs failed.\n", pContext->m_typeinfoNewView.name());
            return ::null();
         }

      }

      ASSERT_KINDOF(::user::interaction, pguie);

      // views are always created with a border!
      if (!pguie->create(::null(), ::null(), WS_VISIBLE | WS_CHILD, rect(0,0,0,0), pwndParent, id, pContext))
      {

         //TRACE0("Warning: could not create ::user::view for frame.\n");
         return ::null();        // can't continue without a ::user::view

      }


      sp(::user::view) pview =  (pguie.m_p);
      if(pview != ::null())
      {
         pview->_001OnInitialUpdate(::null());
      }
      /*   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
      {
      // remove the 3d style from the frame, since the ::user::view is
      //  providing it.
      // make sure to recalc the non-client area
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
      }*/


      if(pguie != ::null())
      {

         if(pguie->get_parent() != ::null())
         {

            sp(::user::place_holder) pholder = pguie->get_parent();

            if(pholder != ::null())
            {

               pholder->hold(pguie);

            }

         }

      }

      return pguie;

   }


   void view::_001OnLButtonDown(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      if(GetParentFrame() != ::null())
      {

         GetParentFrame()->SetActiveView(this);

      }

   }

   void view::_001OnLButtonUp(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   }

   void view::_001OnMouseMove(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::ca::message::mouse, pmouse, pobj);
   }


   sp(::user::document_interface) view::get_document() const
   {
      ASSERT(this != ::null());
      return ((::user::view *) this)->m_spdocument;
   }


   void view::collaborate(::ca::job * pjob)
   {
      {
         ::user::job * puserjob = (dynamic_cast < ::user::job * > (pjob));
         if(puserjob != ::null())
         {
            puserjob->m_pview = this;
         }
      }
   }



   int32_t view::get_total_page_count(::ca::job * pjob)
   {
      UNREFERENCED_PARAMETER(pjob);
      return 1;
   }


   ::user::interaction::e_type view::get_window_type()
   {
      return type_view;
   }


   void view::on_draw_view_nc(::ca::graphics * pdc)
   {

      UNREFERENCED_PARAMETER(pdc);

   }

   void view::on_draw_view(::ca::graphics * pdc, spa(::ca::data) spadata)
   {

      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(spadata);

   }

   void view::defer_draw_view(::ca::graphics * pdc)
   {

      if(get_document() == ::null())
         return;

      spa(::ca::data) spadata;

      spadata.add(get_document()->m_spadata);

      sync_object_ptra sync;

      for(index i = 0; i < spadata.get_count(); i++)
      {

         sync.add(spadata[i].data_mutex());

      }

      retry_multi_lock sl(sync, millis(1), millis(1));

      try
      {
         on_draw_view(pdc, spadata);
      }
      catch(...)
      {
      }

   }

   void view::_001OnDraw(::ca::graphics * pdc)
   {

      on_draw_view_nc(pdc);

      int32_t iTry = 0;

      bool bOk;

retry:

      bOk = true;

      try
      {
         defer_draw_view(pdc);
      }
      catch(...)
      {
         bOk = false;
      }

      iTry++;
      if(!bOk && iTry < 9)
         goto retry;

   }


   /////////////////////////////////////////////////////////////////////////////
   // ::user::view second phase construction - bind to document

   //const CHAR _vfxWndFrameOrView[] = __WNDFRAMEORVIEW;




   /////////////////////////////////////////////////////////////////////////////
   // ::user::view drawing support


   /*void view::_001OnInitialUpdate(::ca::signal_object * pobj)
   {
   on_update(::null(), 0, ::null());        // initial update
   }*/

/*   void view::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object * pHint)
   {
      ::user::view::on_update(pSender, lHint, pHint);
   }
   */
   /////////////////////////////////////////////////////////////////////////////
   // ::user::view selection support

/*   bool view::IsSelected(const ::ca::object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
      //      UNUSED(pDocItem);    // unused in release builds

      return FALSE;   // not implemented, so not selected
   }*/


   void view::_001OnMouseActivate(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::mouse_activate, pmouseactivate, pobj);
      pobj->previous();
      //int32_t nResult = pmouseactivate->get_lresult();

      if (pmouseactivate->GetMessage() == MA_NOACTIVATE
         || pmouseactivate->GetMessage() == MA_NOACTIVATEANDEAT)
      {
         pmouseactivate->set_lresult(pmouseactivate->GetMessage()); // frame does not want to activate
         pmouseactivate->m_bRet = true;
      }

      sp(::user::frame_window) pParentFrame = (GetParentFrame());
      if (pParentFrame != ::null())
      {
         // eat it if this will cause activation
         ASSERT(pParentFrame == pmouseactivate->GetDesktopWindow()
            || pmouseactivate->GetDesktopWindow()->IsChild(pParentFrame));

         // either re-activate the current ::user::view, or set this ::user::view to be active
         sp(::user::view) pview = pParentFrame->GetActiveView();
         sp(::user::interaction) oswindow_Focus = System.get_focus_guie();
         if (pview == this &&
            this != oswindow_Focus && !IsChild(oswindow_Focus))
         {
            // re-activate this ::user::view
            OnActivateView(TRUE, this, this);
         }
         else
         {
            // activate this ::user::view
            pParentFrame->SetActiveView(this);
         }
      }
      pmouseactivate->set_lresult(pmouseactivate->GetMessage());
      pmouseactivate->m_bRet = true;
   }

   void view::on_select()
   {
      sp(::user::frame_window) pParentFrame = (GetParentFrame());
      if (pParentFrame != ::null())
      {
         // eat it if this will cause activation
         /*      ASSERT(pParentFrame == pmouseactivate->GetDesktopWindow()
         || pmouseactivate->GetDesktopWindow()->IsChild(pParentFrame));*/

         // either re-activate the current ::user::view, or set this ::user::view to be active
         sp(::user::view) pview = pParentFrame->GetActiveView();
         sp(::user::interaction) oswindow_Focus = System.get_focus_guie();
         if (pview == this &&
            this != oswindow_Focus && !IsChild(oswindow_Focus))
         {
            // re-activate this ::user::view
            OnActivateView(TRUE, this, this);
         }
         else
         {
            // activate this ::user::view
            pParentFrame->SetActiveView(this);
         }
      }
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::user::view drag/drop support

   DROPEFFECT view::OnDragScroll(uint32_t /*dwKeyState*/, point /*point*/)
   {
#if !defined(___NO_OLE_SUPPORT) && !defined(METROWIN) && !defined(LINUX) && !defined(MACOS)
      return DROPEFFECT_SCROLL; // this means do the default
#else
      return 0;
#endif
   }

   DROPEFFECT view::OnDragEnter(COleDataObject* /*pDataObject*/,
      uint32_t /*dwKeyState*/, point /*point*/)
   {
      return 0;   // DROPEFFECT_NONE
   }

   DROPEFFECT view::OnDragOver(COleDataObject* /*pDataObject*/,
      uint32_t /*dwKeyState*/, point /*point*/)
   {
      return 0;   // DROPEFFECT_NONE
   }

   bool view::OnDrop(COleDataObject* /*pDataObject*/,
      DROPEFFECT /*dropEffect*/, point /*point*/)
   {
      return FALSE;
   }

   DROPEFFECT view::OnDropEx(COleDataObject* /*pDataObject*/,
      DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, point /*point*/)
   {
      return (DROPEFFECT)-1;  // not implemented
   }

   void view::OnDragLeave()
   {
   }



   void view::_001OnUpdateSplitCmd(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnSplitCmd(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnUpdateNextPaneMenu(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnNextPaneCmd(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   // // IMPLEMENT_DYNAMIC for ::user::view is in wincore.cpp for .OBJ granularity reasons

   //// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for swap tuning
   //// IMPLEMENT_DYNAMIC(CCtrlView, ::user::view)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // ::user::view's OnPrintPreview.  Here to force linkage

   void view::_001OnFilePrintPreview(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::_001OnFilePrint(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   /*
   sp(::user::interaction) view::CreateView(sp(::ca::create_context) pContext, UINT nID)
   {
   ASSERT(IsWindow());
   ASSERT(pContext != ::null());
   ASSERT(pContext->m_typeinfoNewView != ::null());

   // Note: can be a ::user::interaction with PostNcDestroy self cleanup
   sp(::user::interaction) pview =  (System.alloc(pContext->m_typeinfoNewView));
   if (pview == ::null())
   {
   TRACE1("Warning: Dynamic create of ::user::view type %hs failed.\n",
   pContext->m_typeinfoNewView.name());
   return ::null();
   }
   ASSERT_KINDOF(::user::interaction, pview);

   // views are always created with a border!
   if (!pview->create(::null(), ::null(), __WS_DEFAULT_VIEW,
   rect(0,0,0,0), this, nID, (sp(::ca::create_context)) pContext))
   {
   TRACE0("Warning: could not create ::user::view for frame.\n");
   return ::null();        // can't continue without a ::user::view
   }

   sp(::user::view) pview =  (pview);
   pview->_001OnInitialUpdate(::null());
   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // remove the 3d style from the frame, since the ::user::view is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   /*   return pview;
   }*/


   /*sp(::user::interaction) view::CreateView(sp(::ca::create_context) pContext, UINT nID, ::user::interaction  * pwndParent)
   {
   ASSERT(pwndParent->IsWindow());
   ASSERT(pContext != ::null());
   ASSERT(pContext->m_typeinfoNewView != ::null());

   // Note: can be a ::ca::window with PostNcDestroy self cleanup
   sp(::ca::window) pview = (pwndParent->System.alloc(pContext->m_typeinfoNewView));
   if (pview == ::null())
   {
   TRACE1("Warning: Dynamic create of ::user::view type %hs failed.\n",
   pContext->m_typeinfoNewView.name());
   return ::null();
   }
   ASSERT_KINDOF(::ca::window, pview);

   // views are always created with a border!
   if (!pview->create(::null(), ::null(), __WS_DEFAULT_VIEW,
   rect(0,0,0,0), pwndParent, nID, (sp(::ca::create_context)) pContext))
   {
   TRACE0("Warning: could not create ::user::view for frame.\n");
   return ::null();        // can't continue without a ::user::view
   }

   ( (pview))->_001OnInitialUpdate(::null());
   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // remove the 3d style from the frame, since the ::user::view is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   //   return pview;
   //}


   void view::_001OnRButtonDown(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      GetParentFrame()->SetActiveView( (this));
   }

   void view::_001OnMButtonDown(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::ca::message::mouse, pmouse, pobj);

      GetParentFrame()->SetActiveView( (this));
   }

} // namespace user
