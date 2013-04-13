#include "framework.h"


#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children



// like ON_MESSAGE but no return value
/*#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, ::ca::Sig_vv, \
      (__PMSG)(__PMSGW)(void (__MSG_CALL ::user::interaction::*)())&memberFxn },*/
// IMPLEMENT_DYNAMIC(::view, ::user::interaction)

/////////////////////////////////////////////////////////////////////////////
// ::view

 // BEGIN_MESSAGE_MAP(::view, ::user::interaction)
   //{{__MSG_MAP(::view)
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

namespace user
{

   view::view(sp(::ca::application) papp) :
      ca(papp),
      ::user::interaction(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      database::user::interaction::install_message_handling(pinterface);
      ::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE  , pinterface, this, &view::_001OnMouseActivate);
      IGUI_WIN_MSG_LINK(WM_DESTROY        , pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_CREATE        , pinterface, this, &view::_001OnCreate);

      // Standard commands for split pane
//      connect_command(ID_WINDOW_SPLIT , &view::_001OnSplitCmd);
  //    connect_update_cmd_ui(ID_WINDOW_SPLIT ,  &view::_001OnUpdateSplitCmd);

      // Standard commands for next pane
    //  connect_update_cmd_ui(ID_NEXT_PANE    , &view::_001OnUpdateNextPaneMenu);
      //connect_command(ID_NEXT_PANE   , &view::_001OnNextPaneCmd);
//      connect_update_cmd_ui(ID_PREV_PANE    , &view::_001OnUpdateNextPaneMenu);
  //    connect_command(ID_PREV_PANE    , &view::_001OnNextPaneCmd);

      //}}__MSG_MAP
      // special command for Initial Update
      IGUI_WIN_MSG_LINK(WM_INITIALUPDATE  , pinterface, this, &view::_001OnInitialUpdate);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_MBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::view second phase construction - bind to document

   //const CHAR _vfxWndFrameOrView[] = __WNDFRAMEORVIEW;
   bool view::pre_create_window(CREATESTRUCT & cs)
   {
      ASSERT(cs.style & WS_CHILD);


   //   if (afxData.bWin4 && (cs.style & WS_BORDER))
      if ((cs.style & WS_BORDER))
      {
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
         cs.style &= ~WS_BORDER;
      }

      return TRUE;
   }




   bool view::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      // first pump through pane
      if (::user::interaction::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      sp(::user::interaction) pwndex;
      if(base < ::view > ::bases(get_parent()))
      {
         pwndex = (get_parent().m_p);
         if(pwndex != ::null())
         {
            if (pwndex->_001OnCmdMsg(pcmdmsg))
               return TRUE;
         }
      }

      // then pump through document
      if (::view::get_document() != ::null())
      {
         if(::view::get_document()->_001OnCmdMsg(pcmdmsg))
            return TRUE;
         sp(::view) pview = ::view::get_document()->get_view(0);
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
   // ::view drawing support


   /*void view::_001OnInitialUpdate(::ca::signal_object * pobj)
   {
      on_update(::null(), 0, ::null());        // initial update
   }*/

   void view::on_update(sp(::view) pSender, LPARAM lHint, ::ca::object * pHint)
   {
      ::view::on_update(pSender, lHint, pHint);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view selection support

   bool view::IsSelected(const ::ca::object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
//      UNUSED(pDocItem);    // unused in release builds

      return FALSE;   // not implemented, so not selected
   }

   void view::OnActivateView(bool bActivate, sp(::view) pActivateView, sp(::view))
   {
  //    UNUSED(pActivateView);   // unused in release builds

      if (bActivate)
      {
         ASSERT(pActivateView == this);

         // take the focus if this frame/::view/pane is now active
         if (IsTopParentActive())
            SetFocus();
      }
   }

   void view::OnActivateFrame(UINT /*nState*/, sp(frame_window) /*pFrameWnd*/)
   {
   }

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

         // either re-activate the current ::view, or set this ::view to be active
         sp(::view) pview = pParentFrame->GetActiveView();
         sp(::user::interaction) oswindow_Focus = System.get_focus_guie();
         if (pview == this &&
            this != oswindow_Focus && !IsChild(oswindow_Focus))
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

         // either re-activate the current ::view, or set this ::view to be active
         sp(::view) pview = pParentFrame->GetActiveView();
         sp(::user::interaction) oswindow_Focus = System.get_focus_guie();
         if (pview == this &&
            this != oswindow_Focus && !IsChild(oswindow_Focus))
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
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view scrolling support

   bool view::OnScroll(UINT /*nScrollCode*/, UINT /*nPos*/, bool /*bDoScroll*/)
   {
      return FALSE;
   }

   bool view::OnScrollBy(size /*sizeScroll*/, bool /*bDoScroll*/)
   {
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view drag/drop support

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

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      if (::view::get_document() != ::null())
         dumpcontext << "with document: " << ::view::get_document().m_p;
      else
         dumpcontext << "with no document\n";
   }

   void view::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }


   // // IMPLEMENT_DYNAMIC for ::view is in wincore.cpp for .OBJ granularity reasons

   //// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for swap tuning
   //// IMPLEMENT_DYNAMIC(CCtrlView, ::view)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // ::view's OnPrintPreview.  Here to force linkage

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
         TRACE1("Warning: Dynamic create of ::view type %hs failed.\n",
            pContext->m_typeinfoNewView.name());
         return ::null();
      }
      ASSERT_KINDOF(::user::interaction, pview);

      // views are always created with a border!
      if (!pview->create(::null(), ::null(), __WS_DEFAULT_VIEW,
         rect(0,0,0,0), this, nID, (sp(::ca::create_context)) pContext))
      {
         TRACE0("Warning: could not create ::view for frame.\n");
         return ::null();        // can't continue without a ::view
      }

      sp(::view) pview =  (pview);
      pview->_001OnInitialUpdate(::null());
      if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
      {
         // remove the 3d style from the frame, since the ::view is
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
         TRACE1("Warning: Dynamic create of ::view type %hs failed.\n",
            pContext->m_typeinfoNewView.name());
         return ::null();
      }
      ASSERT_KINDOF(::ca::window, pview);

      // views are always created with a border!
      if (!pview->create(::null(), ::null(), __WS_DEFAULT_VIEW,
         rect(0,0,0,0), pwndParent, nID, (sp(::ca::create_context)) pContext))
      {
         TRACE0("Warning: could not create ::view for frame.\n");
         return ::null();        // can't continue without a ::view
      }

      ( (pview))->_001OnInitialUpdate(::null());
      if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
      {
         // remove the 3d style from the frame, since the ::view is
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

   void view::_001OnLButtonDown(::ca::signal_object * pobj)
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
