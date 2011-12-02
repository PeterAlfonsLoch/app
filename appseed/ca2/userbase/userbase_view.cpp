#include "StdAfx.h"


#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children



// like ON_MESSAGE but no return value
/*#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, AfxSig_vv, \
      (AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL ::user::interaction::*)(void))&memberFxn },*/
// IMPLEMENT_DYNAMIC(::view, ::user::interaction)

/////////////////////////////////////////////////////////////////////////////
// ::view

 // BEGIN_MESSAGE_MAP(::view, ::user::interaction)
   //{{AFX_MSG_MAP(::view)
/*   ON_WM_PAINT()
   ON_WM_MOUSEACTIVATE()
   ON_WM_CREATE()
   ON_WM_DESTROY()

   // Standard commands for split pane
   ON_COMMAND_EX(ID_WINDOW_SPLIT, OnSplitCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_SPLIT, OnUpdateSplitCmd)

   // Standard commands for next pane
   ON_UPDATE_COMMAND_UI(ID_NEXT_PANE, OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_NEXT_PANE, OnNextPaneCmd)
   ON_UPDATE_COMMAND_UI(ID_PREV_PANE, OnUpdateNextPaneMenu)
   ON_COMMAND_EX(ID_PREV_PANE, OnNextPaneCmd)
   //}}AFX_MSG_MAP
   // special command for Initial Update
   ON_MESSAGE_VOID(WM_INITIALUPDATE, OnInitialUpdate)*/
 // END_MESSAGE_MAP()

namespace userbase
{

   view::view(::ax::application * papp) :
      ax(papp),
      ::user::interaction(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      database::user::interaction::install_message_handling(pinterface);
      ::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE  , pinterface, this, &view::_001OnMouseActivate);
      IGUI_WIN_MSG_LINK(WM_DESTROY        , pinterface, this, &view::_001OnDestroy);

      // Standard commands for split pane
      connect_command(ID_WINDOW_SPLIT , &view::_001OnSplitCmd);
      connect_update_cmd_ui(ID_WINDOW_SPLIT ,  &view::_001OnUpdateSplitCmd);

      // Standard commands for next pane
      connect_update_cmd_ui(ID_NEXT_PANE    , &view::_001OnUpdateNextPaneMenu);
      connect_command(ID_NEXT_PANE   , &view::_001OnNextPaneCmd);
      connect_update_cmd_ui(ID_PREV_PANE    , &view::_001OnUpdateNextPaneMenu);
      connect_command(ID_PREV_PANE    , &view::_001OnNextPaneCmd);
      
      //}}AFX_MSG_MAP
      // special command for Initial Update
      IGUI_WIN_MSG_LINK(WM_INITIALUPDATE  , pinterface, this, &view::_001OnInitialUpdate);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_MBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN    , pinterface, this, &view::_001OnRButtonDown);
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::view second phase construction - bind to document

   const CHAR _vfxWndFrameOrView[] = AFX_WNDFRAMEORVIEW;
   BOOL view::PreCreateWindow(CREATESTRUCT & cs)
   {
      ASSERT(cs.style & WS_CHILD);

      if (cs.lpszClass == NULL)
      {
         VERIFY(System.DeferRegisterClass(AFX_WNDFRAMEORVIEW_REG, & cs.lpszClass));
      }

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
      ::user::interaction * pwndex;
      if(base < ::view > ::bases(GetParent()))
      {
         pwndex = dynamic_cast < ::user::interaction * >(GetParent());
         if(pwndex != NULL)
         {
            if (pwndex->_001OnCmdMsg(pcmdmsg))
               return TRUE;
         }
      }

      // then pump through document
      if (::view::get_document() != NULL)
      {
         if(::view::get_document()->_001OnCmdMsg(pcmdmsg))
            return TRUE;
         ::view * pview = ::view::get_document()->get_view(0);
         ASSERT_VALID(pview);
         if (pview != this
            && pview != GetParent())
         {
            pwndex = dynamic_cast < ::user::interaction * >(pview);
            if(pwndex != NULL)
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


   /*void view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      on_update(NULL, 0, NULL);        // initial update
   }*/

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint)
   {
      ::view::on_update(pSender, lHint, pHint);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view selection support

   BOOL view::IsSelected(const ::radix::object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
      UNUSED(pDocItem);    // unused in release builds

      return FALSE;   // not implemented, so not selected
   }

   void view::OnActivateView(BOOL bActivate, ::view* pActivateView, ::view*)
   {
      UNUSED(pActivateView);   // unused in release builds

      if (bActivate)
      {
         ASSERT(pActivateView == this);

         // take the focus if this frame/::view/pane is now active
         if (IsTopParentActive())
            SetFocus();
      }
   }

   void view::OnActivateFrame(UINT /*nState*/, ::frame_window* /*pFrameWnd*/)
   {
   }

   void view::_001OnMouseActivate(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse_activate, pmouseactivate, pobj);
      pobj->previous();
      //int nResult = pmouseactivate->get_lresult();

      if (pmouseactivate->GetMessage() == MA_NOACTIVATE 
       || pmouseactivate->GetMessage() == MA_NOACTIVATEANDEAT)
      {
         pmouseactivate->set_lresult(pmouseactivate->GetMessageA()); // frame does not want to activate
         pmouseactivate->m_bRet = true;
      }

      userbase::frame_window* pParentFrame = dynamic_cast < userbase::frame_window * > (GetParentFrame());
      if (pParentFrame != NULL)
      {
         // eat it if this will cause activation
         ASSERT(pParentFrame == pmouseactivate->GetDesktopWindow()
             || pmouseactivate->GetDesktopWindow()->IsChild(pParentFrame));

         // either re-activate the current ::view, or set this ::view to be active
         ::view * pview = pParentFrame->GetActiveView();
         ::user::interaction* hWndFocus = System.get_focus_guie();
         if (pview == this &&
            this != hWndFocus && !IsChild(hWndFocus))
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
      pmouseactivate->set_lresult(pmouseactivate->GetMessageA());
      pmouseactivate->m_bRet = true;
   }

   void view::on_select()
   {
      userbase::frame_window* pParentFrame = dynamic_cast < userbase::frame_window * > (GetParentFrame());
      if (pParentFrame != NULL)
      {
         // eat it if this will cause activation
   /*      ASSERT(pParentFrame == pmouseactivate->GetDesktopWindow()
             || pmouseactivate->GetDesktopWindow()->IsChild(pParentFrame));*/

         // either re-activate the current ::view, or set this ::view to be active
         ::view * pview = pParentFrame->GetActiveView();
         ::user::interaction* hWndFocus = System.get_focus_guie();
         if (pview == this &&
            this != hWndFocus && !IsChild(hWndFocus))
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

   DROPEFFECT view::OnDragScroll(DWORD /*dwKeyState*/, point /*point*/)
   {
   #ifndef _AFX_NO_OLE_SUPPORT
      return DROPEFFECT_SCROLL; // this means do the default
   #else
      return 0;
   #endif
   }

   DROPEFFECT view::OnDragEnter(COleDataObject* /*pDataObject*/,
      DWORD /*dwKeyState*/, point /*point*/)
   {
      return 0;   // DROPEFFECT_NONE
   }

   DROPEFFECT view::OnDragOver(COleDataObject* /*pDataObject*/,
      DWORD /*dwKeyState*/, point /*point*/)
   {
      return 0;   // DROPEFFECT_NONE
   }

   BOOL view::OnDrop(COleDataObject* /*pDataObject*/,
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



   void view::_001OnUpdateSplitCmd(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnSplitCmd(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnUpdateNextPaneMenu(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::_001OnNextPaneCmd(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   #ifdef _DEBUG
   void view::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      if (::view::get_document() != NULL)
         dumpcontext << "with document: " << ::view::get_document();
      else
         dumpcontext << "with no document\n";
   }

   void view::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }
   #endif //_DEBUG


   // // IMPLEMENT_DYNAMIC for ::view is in wincore.cpp for .OBJ granularity reasons

   //// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for swap tuning
   //// IMPLEMENT_DYNAMIC(CCtrlView, ::view)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // ::view's OnPrintPreview.  Here to force linkage

   void view::_001OnFilePrintPreview(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   BOOL CALLBACK _AfxPreviewCloseProc(userbase::frame_window* pFrameWnd)
   {
      ASSERT_VALID(pFrameWnd);


      return FALSE;
   }

   void view::_001OnFilePrint(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   document* view::get_document() const
      { ASSERT(this != NULL); return dynamic_cast < document * > (::view::get_document()); }


   /*
   ::user::interaction* view::CreateView(create_context* pContext, UINT nID)
   {
      ASSERT(IsWindow());
      ASSERT(pContext != NULL);
      ASSERT(pContext->m_typeinfoNewView != NULL);

      // Note: can be a ::user::interaction with PostNcDestroy self cleanup
      ::user::interaction* pview = dynamic_cast < ::user::interaction * > (System.alloc(pContext->m_typeinfoNewView));
      if (pview == NULL)
      {
         TRACE1("Warning: Dynamic create of ::view type %hs failed.\n",
            pContext->m_typeinfoNewView.name());
         return NULL;
      }
      ASSERT_KINDOF(::user::interaction, pview);

      // views are always created with a border!
      if (!pview->create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
         rect(0,0,0,0), this, nID, (create_context *) pContext))
      {
         TRACE0("Warning: could not create ::view for frame.\n");
         return NULL;        // can't continue without a ::view
      }

      ::view * pview = dynamic_cast < ::view * > (pview);
      pview->_001OnInitialUpdate(NULL);
   /*   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
      {
         // remove the 3d style from the frame, since the ::view is
         //  providing it.
         // make sure to recalc the non-client area
         ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
      }*/
   /*   return pview;
   }*/


   /*::user::interaction * view::CreateView(create_context* pContext, UINT nID, ::user::interaction  * pwndParent)
   {
      ASSERT(pwndParent->IsWindow());
      ASSERT(pContext != NULL);
      ASSERT(pContext->m_typeinfoNewView != NULL);

      // Note: can be a ::ax::window with PostNcDestroy self cleanup
      ::ax::window* pview = dynamic_cast < ::ax::window * > (pwndParent->System.alloc(pContext->m_typeinfoNewView));
      if (pview == NULL)
      {
         TRACE1("Warning: Dynamic create of ::view type %hs failed.\n",
            pContext->m_typeinfoNewView.name());
         return NULL;
      }
      ASSERT_KINDOF(::ax::window, pview);

      // views are always created with a border!
      if (!pview->create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
         rect(0,0,0,0), pwndParent, nID, (create_context *) pContext))
      {
         TRACE0("Warning: could not create ::view for frame.\n");
         return NULL;        // can't continue without a ::view
      }

      (dynamic_cast < ::view * > (pview))->_001OnInitialUpdate(NULL);
   /*   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
      {
         // remove the 3d style from the frame, since the ::view is
         //  providing it.
         // make sure to recalc the non-client area
         ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
      }*/
   //   return pview;
   //}


   void view::_001OnRButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::mouse, pmouse, pobj);

      GetParentFrame()->SetActiveView(dynamic_cast < ::view * > (this));
   }

   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::mouse, pmouse, pobj);

      GetParentFrame()->SetActiveView(dynamic_cast < ::view * > (this));
   }

   void view::_001OnMButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::mouse, pmouse, pobj);

      GetParentFrame()->SetActiveView(dynamic_cast < ::view * > (this));
   }

} // namespace userbase