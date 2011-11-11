#include "StdAfx.h"

namespace userbase
{

   // IMPLEMENT_DYNCREATE(mdi_child_window, userbase::frame_window)

   /////////////////////////////////////////////////////////////////////////////
   // mdi_child_window

   // // BEGIN_MESSAGE_MAP(mdi_child_window, userbase::frame_window)
      //{{AFX_MSG_MAP(mdi_child_window)
   /* xxx   ON_WM_MOUSEACTIVATE()
      ON_WM_NCACTIVATE()
      ON_WM_MDIACTIVATE()
      ON_WM_SIZE()
      ON_WM_WINDOWPOSCHANGING()
      ON_WM_NCCREATE()
      ON_WM_CREATE()
      ON_WM_DESTROY()
      ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &mdi_child_window::OnToolTipText)
      ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &mdi_child_window::OnToolTipText) */
      //}}AFX_MSG_MAP
   // // END_MESSAGE_MAP()

   mdi_child_window::mdi_child_window(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp)
   {
      m_hMenuShared = NULL;
      m_bPseudoInactive = FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // mdi_child_window special processing

   LRESULT mdi_child_window::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      // trans return ::DefMDIChildProc(get_handle(), nMsg, wParam, lParam);
      return 0;
   }

   BOOL mdi_child_window::DestroyWindow()
   {
   /*trans   if (get_handle() == NULL)
         return FALSE;*/

      // avoid changing the caption during the destroy message(s)
      mdi_frame_window* pFrameWnd = GetMDIFrame();
      ASSERT(pFrameWnd->IsWindow());
      DWORD dwStyle = pFrameWnd->SetWindowLong(GWL_STYLE,
         pFrameWnd->GetWindowLong(GWL_STYLE) & ~FWS_ADDTOTITLE);

      MDIDestroy();

      if (pFrameWnd->IsWindow())
      {
         pFrameWnd->SetWindowLong(GWL_STYLE, dwStyle);
         pFrameWnd->on_update_frame_title(TRUE);
      }

      return TRUE;
   }

   void mdi_child_window::pre_translate_message(gen::signal_object * pobj)
   {
      // check for special cancel modes for combo boxes
      //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
      //   AfxCancelModes(pMsg->hwnd);    // filter clicks

      // allow tooltip messages to be filtered
      ::user::interaction::pre_translate_message(pobj);
      if(pobj->m_bRet)
         return;

      // we can't call 'userbase::frame_window::PreTranslate' since it will translate
      //  accelerators in the context of the MDI Child - but since MDI Child
      //  windows don't have menus this doesn't work properly.  MDI Child
      //  accelerators must be translated in context of their MDI Frame.

   /* trans   if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
      {
         // use document specific accelerator table over m_hAccelTable
         HACCEL hAccel = GetDefaultAccelerator();
         return hAccel != NULL &&
            ::TranslateAccelerator(GetMDIFrame()->get_handle(), hAccel, pMsg);
      }*/
      //return FALSE;
   }

   BOOL mdi_child_window::PreCreateWindow(CREATESTRUCT& cs)
   {
      ASSERT(cs.style & WS_CHILD);
         // ca2 API V2 requires that MDI Children are created with proper styles,
         //  usually: WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW.
         // See Technical note TN019 for more details on ca2 API V1->V2 migration.

      return userbase::frame_window::PreCreateWindow(cs);
   }

   BOOL mdi_child_window::create(const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect, mdi_frame_window* pParentWnd,
      ::ca::create_context* pContext)
   {
      if (pParentWnd == NULL)
      {
         ::radix::thread *pThread = System.GetThread();
         ENSURE_VALID(pThread);
         ::user::interaction* pMainWnd = pThread->GetMainWnd();
         ENSURE_VALID(pMainWnd);
         ASSERT_KINDOF(mdi_frame_window, pMainWnd);
         pParentWnd = dynamic_cast < mdi_frame_window * > (pMainWnd);
      }
      ASSERT(pParentWnd->m_pguieMdiClient->IsWindow());

      // insure correct ::ca::window positioning
      pParentWnd->layout();

      // first copy into a CREATESTRUCT for PreCreate
      CREATESTRUCT cs;
      cs.dwExStyle = 0L;
      cs.lpszClass = lpszClassName;
      cs.lpszName = lpszWindowName;
      cs.style = dwStyle;
      cs.x = rect.left;
      cs.y = rect.top;
      cs.cx = rect.right - rect.left;
      cs.cy = rect.bottom - rect.top;
      cs.hwndParent = pParentWnd->_get_handle();
      cs.hMenu = NULL;
      cs.hInstance = System.m_hInstance;
      cs.lpCreateParams = (LPVOID)pContext;

      if (!PreCreateWindow(cs))
      {
         PostNcDestroy();
         return FALSE;
      }
      // extended style must be zero for MDI Children (except under Win4)
   // trans   ASSERT(cs.hwndParent == pParentWnd->get_handle());    // must not change

      // now copy into a MDICREATESTRUCT for real create
      MDICREATESTRUCT mcs;
      mcs.szClass = cs.lpszClass;
      mcs.szTitle = cs.lpszName;
      mcs.hOwner = cs.hInstance;
      mcs.x = cs.x;
      mcs.y = cs.y;
      mcs.cx = cs.cx;
      mcs.cy = cs.cy;
      mcs.style = cs.style & ~(WS_MAXIMIZE | WS_VISIBLE);
      mcs.lParam = (LPARAM)cs.lpCreateParams;

      // create the ::ca::window through the MDICLIENT ::ca::window
      //AfxHookWindowCreate(this);
      ::user::interaction * hWnd = (::user::interaction *)pParentWnd->m_pguieMdiClient->SendMessage(
         WM_MDICREATE, 0, (LPARAM)&mcs);
      //if (!AfxUnhookWindowCreate())
         //PostNcDestroy();        // cleanup if MDICREATE fails too soon

      if (hWnd == NULL)
         return FALSE;

      // special handling of visibility (always created invisible)
      if (cs.style & WS_VISIBLE)
      {
         // place the ::ca::window on top in z-order before showing it
         hWnd->BringWindowToTop();

         // show it as specified
         if (cs.style & WS_MINIMIZE)
            ShowWindow(SW_SHOWMINIMIZED);
         else if (cs.style & WS_MAXIMIZE)
            ShowWindow(SW_SHOWMAXIMIZED);
         else
            ShowWindow(SW_SHOWNORMAL);

         // make sure it is active (visibility == activation)
         pParentWnd->MDIActivate(this);

         // refresh MDI Window menu
         pParentWnd->m_pguieMdiClient->SendMessage( WM_MDIREFRESHMENU, 0, 0);
      }

      //ASSERT(hWnd == get_handle());
      return TRUE;
   }

   BOOL mdi_child_window::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
         ::user::interaction* pParentWnd, ::ca::create_context* pContext)
   {
      // only do this once
   //   ASSERT_VALID_IDR(nIDResource);
   //   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

      m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

      // parent must be MDI Frame (or NULL for default)
      ASSERT(pParentWnd == NULL || base < mdi_frame_window >::bases(pParentWnd));
      // will be a child of MDIClient
      ASSERT(!(dwDefaultStyle & WS_POPUP));
      dwDefaultStyle |= WS_CHILD;

      // if available - get MDI child menus from doc template
      multiple_document_template* ptemplate;
      if (pContext != NULL &&
         (ptemplate = dynamic_cast < multiple_document_template * > (pContext->m_user->m_pNewDocTemplate)) != NULL)
      {
         ASSERT_KINDOF(multiple_document_template, ptemplate);
      }
      else
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: no shared menu/acceltable for MDI Child ::ca::window.\n");
            // if this happens, programmer must load these manually
      }

      string strFullString, strTitle;
      strFullString = System.matter_as_string(get_app(), pszMatter, "full_string.txt");
      if(!strFullString.is_empty())
         AfxExtractSubString(strTitle, strFullString, 0);    // first sub-string

   //   ASSERT(get_handle() == NULL);
   /* trans   if (!create(GetIconWndClass(dwDefaultStyle, nIDResource),
        strTitle, dwDefaultStyle, rectDefault,
        dynamic_cast < mdi_frame_window * > (pParentWnd), pContext))*/
      if (!create(GetIconWndClass(dwDefaultStyle, pszMatter),
        strTitle, dwDefaultStyle, rectDefault,
        dynamic_cast < mdi_frame_window * > (pParentWnd), pContext))
      {
         return FALSE;   // will self destruct on failure normally
      }

      // it worked !
      return TRUE;
   }

   void mdi_child_window::OnSize(UINT nType, int cx, int cy)
   {
      userbase::frame_window::OnSize(nType, cx, cy);

      // update our parent frame - in case we are now maximized or not
      GetMDIFrame()->on_update_frame_title(TRUE);
   }

   BOOL mdi_child_window::UpdateClientEdge(LPRECT lpRect)
   {
      // only adjust for active MDI child ::ca::window
      mdi_frame_window* pFrameWnd = GetMDIFrame();
      mdi_child_window* pChild = pFrameWnd->MDIGetActive();
      if (pChild == NULL || pChild == this)
      {
         // need to adjust the client edge style as max/restore happens
         DWORD dwStyle = pFrameWnd->m_pguieMdiClient->GetWindowLong( GWL_EXSTYLE);
         DWORD dwNewStyle = dwStyle;
         if (pChild != NULL && !(GetExStyle() & WS_EX_CLIENTEDGE) &&
           (GetStyle() & WS_MAXIMIZE))
            dwNewStyle &= ~(WS_EX_CLIENTEDGE);
         else
            dwNewStyle |= WS_EX_CLIENTEDGE;

         if (dwStyle != dwNewStyle)
         {
            // SetWindowPos will not move invalid bits
            pFrameWnd->m_pguieMdiClient->RedrawWindow( NULL, NULL,
               RDW_INVALIDATE | RDW_ALLCHILDREN);

            // remove/add WS_EX_CLIENTEDGE to MDI client area
            pFrameWnd->m_pguieMdiClient->SetWindowLong(GWL_EXSTYLE, dwNewStyle);
            pFrameWnd->m_pguieMdiClient->SetWindowPos(NULL, 0, 0, 0, 0,
               SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE |
               SWP_NOZORDER | SWP_NOCOPYBITS);

            // return new client area
            if (lpRect != NULL)
               pFrameWnd->m_pguieMdiClient->GetClientRect( lpRect);
            return TRUE;
         }
      }
      return FALSE;
   }

   void mdi_child_window::OnWindowPosChanging(LPWINDOWPOS lpWndPos)
   {
      if (!(lpWndPos->flags & SWP_NOSIZE))
      {
         rect rectClient;
         if (UpdateClientEdge(rectClient) && (GetStyle() & WS_MAXIMIZE))
         {
            // adjust maximized ::ca::window size and position based on new
            //  size/position of the MDI client area.
            ::AdjustWindowRectEx(rectClient, GetStyle(), FALSE, GetExStyle());
            lpWndPos->x = rectClient.left;
            lpWndPos->y = rectClient.top;
            lpWndPos->cx = rectClient.width();
            lpWndPos->cy = rectClient.height();
         }
      }

   // trans   userbase::frame_window::OnWindowPosChanging(lpWndPos);
   }

   void mdi_child_window::OnDestroy()
   {
      UpdateClientEdge();

   // trans   userbase::frame_window::OnDestroy();
   }

   BOOL mdi_child_window::OnNcActivate(BOOL bActive)
   {
      UNREFERENCED_PARAMETER(bActive);
      // bypass userbase::frame_window::OnNcActivate()
   // trans   return ::user::interaction::OnNcActivate(bActive);
      return FALSE;
   }

   int mdi_child_window::OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(message);
   // trans   int nResult = userbase::frame_window::OnMouseActivate(pDesktopWnd, nHitTest, message);
      int nResult = 0;
      if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
         return nResult;   // frame does not want to activate

      // activate this ::ca::window if necessary
      mdi_frame_window* pFrameWnd = GetMDIFrame();
      ASSERT_VALID(pFrameWnd);
      mdi_child_window* pActive = pFrameWnd->MDIGetActive();
      if (pActive != this)
         MDIActivate();

      return nResult;
   }

   BOOL mdi_child_window::OnToolTipText(UINT msg, NMHDR* pNMHDR, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(msg);
      UNREFERENCED_PARAMETER(pResult);
      ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
      UNUSED(pNMHDR);

      // check to see if the message is going directly to this ::ca::window or not
      const MSG* pMsg = ::ca::window::GetCurrentMessage();
      if (pMsg->hwnd != _get_handle())
      {
         // let top level frame handle this for us
         return FALSE;
      }

      // otherwise, handle it ourselves
   // trans   return userbase::frame_window::OnToolTipText(msg, pNMHDR, pResult);
      return FALSE;
   }

   void mdi_child_window::ActivateFrame(int nCmdShow)
   {
      BOOL bVisibleThen = (GetStyle() & WS_VISIBLE) != 0;
      mdi_frame_window* pFrameWnd = GetMDIFrame();
      ASSERT_VALID(pFrameWnd);

      // determine default show command
      if (nCmdShow == -1)
      {
         // get maximized state of frame ::ca::window (previously active child)
         BOOL bMaximized;
         pFrameWnd->MDIGetActive(&bMaximized);

         // convert show command based on current style
         DWORD dwStyle = GetStyle();
         if (bMaximized || (dwStyle & WS_MAXIMIZE))
            nCmdShow = SW_SHOWMAXIMIZED;
         else if (dwStyle & WS_MINIMIZE)
            nCmdShow = SW_SHOWMINIMIZED;
      }

      // finally, show the ::ca::window
      userbase::frame_window::ActivateFrame(nCmdShow);

      // update the Window menu to reflect new child ::ca::window
      mdi_frame_window* pFrame = GetMDIFrame();
      pFrame->m_pguieMdiClient->SendMessage( WM_MDIREFRESHMENU, 0, 0);

      // Note: Update the m_bPseudoInactive flag.  This is used to handle the
      //  last MDI child getting hidden.  Windows provides no way to deactivate
      //  an MDI child ::ca::window.

      BOOL bVisibleNow = (GetStyle() & WS_VISIBLE) != 0;
      if (bVisibleNow == bVisibleThen)
         return;

      if (!bVisibleNow)
      {
         // get current active ::ca::window according to Windows MDI
         ::user::interaction * hWnd = (::user::interaction *)pFrameWnd->m_pguieMdiClient->SendMessage(
            WM_MDIGETACTIVE, 0, 0);
         if (hWnd != this)
         {
            // not active any more -- ::ca::window must have been deactivated
            ASSERT(!m_bPseudoInactive);
            return;
         }

         // check next ::ca::window
         ASSERT(hWnd != NULL);
         pFrameWnd->MDINext();

         // see if it has been deactivated now...
         hWnd = (::user::interaction *)pFrameWnd->m_pguieMdiClient->SendMessage(
            WM_MDIGETACTIVE, 0, 0);
         if (hWnd == this)
         {
            // still active -- fake deactivate it
            ASSERT(hWnd != NULL);
            OnMDIActivate(FALSE, NULL, this);
            m_bPseudoInactive = TRUE;   // so MDIGetActive returns NULL
         }
      }
      else if (m_bPseudoInactive)
      {
         // if state transitioned from not visible to visible, but
         //  was pseudo deactivated -- send activate notify now
         OnMDIActivate(TRUE, this, NULL);
         ASSERT(!m_bPseudoInactive); // should get set in OnMDIActivate!
      }
   }

   void mdi_child_window::SetHandles(HMENU hMenu, HACCEL hAccel)
   {
      m_hMenuShared = hMenu;
      m_hAccelTable = hAccel;
   }

   /////////////////////////////////////////////////////////////////////////////
   // mdi_child_window Diagnostics

   #ifdef _DEBUG
   void mdi_child_window::assert_valid() const
   {
      userbase::frame_window::assert_valid();
      ASSERT(m_hMenuShared == NULL || ::IsMenu(m_hMenuShared));
   }

   void mdi_child_window::dump(dump_context & dumpcontext) const
   {
      userbase::frame_window::dump(dumpcontext);

      dumpcontext << "m_hMenuShared = " << (void *)m_hMenuShared;
      dumpcontext << "\n";
   }
   #endif //_DEBUG

   void mdi_child_window::MDIDestroy()
      { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIDESTROY, (WPARAM)this, 0L); }
   void mdi_child_window::MDIActivate()
      { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIACTIVATE, (WPARAM)this, 0L); }
   void mdi_child_window::MDIMaximize()
      { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIMAXIMIZE, (WPARAM)this, 0L); }
   void mdi_child_window::MDIRestore()
      { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIRESTORE, (WPARAM)this, 0L); }


} // namespace userbase