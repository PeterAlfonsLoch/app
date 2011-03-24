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




/////////////////////////////////////////////////////////////////////////////
// SimpleMDIChildWindow
/*
 // BEGIN_MESSAGE_MAP(SimpleMDIChildWindow, frame_window)
   //{{AFX_MSG_MAP(SimpleMDIChildWindow)
 xxx   ON_WM_MOUSEACTIVATE()
   ON_WM_NCACTIVATE()
   ON_WM_MDIACTIVATE()
   ON_WM_SIZE()
   ON_WM_WINDOWPOSCHANGING()
   ON_WM_NCCREATE()
   ON_WM_CREATE()
   ON_WM_DESTROY()
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &SimpleMDIChildWindow::OnToolTipText)
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &SimpleMDIChildWindow::OnToolTipText)
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()
*/

SimpleMDIChildWindow::SimpleMDIChildWindow(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp)
{
   m_hMenuShared = NULL;
   m_bPseudoInactive = FALSE;
}

void SimpleMDIChildWindow::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_frame_window::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &SimpleMDIChildWindow::_001OnCreate);
}


/////////////////////////////////////////////////////////////////////////////
// SimpleMDIChildWindow special processing

LRESULT SimpleMDIChildWindow::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nMsg);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
// trans   return ::DefMDIChildProc(get_handle(), nMsg, wParam, lParam);
   return 0;
}

BOOL SimpleMDIChildWindow::DestroyWindow()
{
   if (!IsWindow())
      return FALSE;

   // avoid changing the caption during the destroy message(s)
   SimpleMDIFrameWindow* pFrameWnd = GetMDIFrame();
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

void SimpleMDIChildWindow::pre_translate_message(gen::signal_object * pobj)
{
   // check for special cancel modes for combo boxes
   //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
   //   AfxCancelModes(pMsg->hwnd);    // filter clicks

   // allow tooltip messages to be filtered
   ::user::interaction::pre_translate_message(pobj);
   if(pobj->m_bRet)
      return;

   // we can't call 'frame_window::PreTranslate' since it will translate
   //  accelerators in the context of the MDI Child - but since MDI Child
   //  windows don't have menus this doesn't work properly.  MDI Child
   //  accelerators must be translated in context of their MDI Frame.

/* transs   if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
   {
      // use document specific accelerator table over m_hAccelTable
      HACCEL hAccel = GetDefaultAccelerator();
      return hAccel != NULL &&
         ::TranslateAccelerator(GetMDIFrame()->get_handle(), hAccel, pMsg);
   } */
}

BOOL SimpleMDIChildWindow::PreCreateWindow(CREATESTRUCT& cs)
{
   ASSERT(cs.style & WS_CHILD);
      // ca2 API V2 requires that MDI Children are created with proper styles,
      //  usually: WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW.
      // See Technical note TN019 for more details on ca2 API V1->V2 migration.

   return frame_window::PreCreateWindow(cs);
}

BOOL SimpleMDIChildWindow::create(const char * lpszClassName,
   const char * lpszWindowName, DWORD dwStyle,
   const RECT& rect, SimpleMDIFrameWindow* pParentWnd,
   create_context* pContext)
{
   UNREFERENCED_PARAMETER(lpszClassName);
   UNREFERENCED_PARAMETER(lpszWindowName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(pParentWnd);
   UNREFERENCED_PARAMETER(pContext);
   throw not_implemented_exception();
/*   if (pParentWnd == NULL)
   {
      thread *pThread = System.GetThread();
      ENSURE_VALID(pThread);
      ::user::interaction* pMainWnd = pThread->GetMainWnd();
      ENSURE_VALID(pMainWnd);
      ASSERT_KINDOF(SimpleMDIFrameWindow, pMainWnd);
      pParentWnd = dynamic_cast < SimpleMDIFrameWindow * > (pMainWnd);
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
//   ASSERT(cs.hwndParent == pParentWnd->get_handle());    // must not change

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
   AfxHookWindowCreate(this);
   HWND hWnd = (HWND)pParentWnd->m_pguieMdiClient->SendMessage(
      WM_MDICREATE, 0, (LPARAM)&mcs);
   if (!AfxUnhookWindowCreate())
      PostNcDestroy();        // cleanup if MDICREATE fails too soon

   if (hWnd == NULL)
      return FALSE;

   // special handling of visibility (always created invisible)
   if (cs.style & WS_VISIBLE)
   {
      // place the ::ca::window on top in z-order before showing it
      ::BringWindowToTop(hWnd);

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

//   ASSERT(hWnd == get_handle());*/
   return TRUE;
}

BOOL SimpleMDIChildWindow::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
      ::user::interaction* pParentWnd, create_context* pContext)
{
   // only do this once
   //ASSERT_VALID_IDR(nIDResource);
   //ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   // parent must be MDI Frame (or NULL for default)
   ASSERT(pParentWnd == NULL || base < SimpleMDIFrameWindow > :: bases(pParentWnd));
   // will be a child of MDIClient
   ASSERT(!(dwDefaultStyle & WS_POPUP));
   dwDefaultStyle |= WS_CHILD;

   // if available - get MDI child menus from doc template
   multiple_document_template* ptemplate;
   if (pContext != NULL &&
      (ptemplate = dynamic_cast < multiple_document_template * > (pContext->m_pNewDocTemplate)) != NULL)
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

   if(!create(GetIconWndClass(dwDefaultStyle, pszMatter),
     strTitle, dwDefaultStyle, rectDefault,
     dynamic_cast < SimpleMDIFrameWindow * > (pParentWnd), pContext))
   {
      return FALSE;   // will self destruct on failure normally
   }

   // it worked !
   return TRUE;
}

void SimpleMDIChildWindow::OnSize(UINT nType, int cx, int cy)
{
   frame_window::OnSize(nType, cx, cy);

   // update our parent frame - in case we are now maximized or not
   GetMDIFrame()->on_update_frame_title(TRUE);
}

BOOL SimpleMDIChildWindow::UpdateClientEdge(LPRECT lpRect)
{
   // only adjust for active MDI child ::ca::window
   SimpleMDIFrameWindow* pFrameWnd = GetMDIFrame();
   SimpleMDIChildWindow * pChild = dynamic_cast < SimpleMDIChildWindow * > (pFrameWnd->MDIGetActive());
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

void SimpleMDIChildWindow::OnWindowPosChanging(LPWINDOWPOS lpWndPos)
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

// trans   frame_window::OnWindowPosChanging(lpWndPos);
}

void SimpleMDIChildWindow::OnDestroy()
{
   UpdateClientEdge();

//   frame_window::OnDestroy();
}

BOOL SimpleMDIChildWindow::OnNcActivate(BOOL bActive)
{
   UNREFERENCED_PARAMETER(bActive);
   // bypass frame_window::OnNcActivate()
// trans   return ::user::interaction::OnNcActivate(bActive);
   return FALSE;
}

int SimpleMDIChildWindow::OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message)
{
   UNREFERENCED_PARAMETER(pDesktopWnd);
   UNREFERENCED_PARAMETER(nHitTest);
   UNREFERENCED_PARAMETER(message);
// trans   int nResult = frame_window::OnMouseActivate(pDesktopWnd, nHitTest, message);
   int nResult = 0;
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
      return nResult;   // frame does not want to activate

   // activate this ::ca::window if necessary
   SimpleMDIFrameWindow* pFrameWnd = GetMDIFrame();
   ASSERT_VALID(pFrameWnd);
   SimpleMDIChildWindow* pActive = dynamic_cast < SimpleMDIChildWindow* > (pFrameWnd->MDIGetActive());
   if (pActive != this)
      MDIActivate();

   return nResult;
}


void SimpleMDIChildWindow::ActivateFrame(int nCmdShow)
{
   BOOL bVisibleThen = (GetStyle() & WS_VISIBLE) != 0;
   SimpleMDIFrameWindow* pFrameWnd = GetMDIFrame();
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
   frame_window::ActivateFrame(nCmdShow);

   // update the Window menu to reflect new child ::ca::window
   SimpleMDIFrameWindow* pFrame = GetMDIFrame();
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

void SimpleMDIChildWindow::SetHandles(HMENU hMenu, HACCEL hAccel)
{
   m_hMenuShared = hMenu;
   m_hAccelTable = hAccel;
}

/////////////////////////////////////////////////////////////////////////////
// SimpleMDIChildWindow Diagnostics

#ifdef _DEBUG
void SimpleMDIChildWindow::assert_valid() const
{
   frame_window::assert_valid();
   ASSERT(m_hMenuShared == NULL || ::IsMenu(m_hMenuShared));
}

void SimpleMDIChildWindow::dump(dump_context & dumpcontext) const
{
   frame_window::dump(dumpcontext);

   dumpcontext << "m_hMenuShared = " << (void *)m_hMenuShared;
   dumpcontext << "\n";
}
#endif //_DEBUG


::user::interaction* SimpleMDIChildWindow::GetMessageBar()
{
   // status bar/message bar owned by parent MDI frame
   return GetMDIFrame()->GetMessageBar();
}

void SimpleMDIChildWindow::on_update_frame_title(BOOL bAddToTitle)
{
   // update our parent ::ca::window first
   GetMDIFrame()->on_update_frame_title(bAddToTitle);

   if ((GetStyle() & FWS_ADDTOTITLE) == 0)
      return;     // leave child ::ca::window alone!

   document * pdocument = GetActiveDocument();
   if (bAddToTitle)
   {
      char szText[256+_MAX_PATH];
      if (pdocument == NULL)
         _template::checked::tcsncpy_s(szText, _countof(szText), m_strTitle, _TRUNCATE);
      else
         _template::checked::tcsncpy_s(szText, _countof(szText), pdocument->get_title(), _TRUNCATE);
      if (m_nWindow > 0)
      {
         char szWinNumber[16+1];
         _stprintf_s(szWinNumber, _countof(szWinNumber), ":%d", m_nWindow);
         
         if( lstrlen(szText) + lstrlen(szWinNumber) < _countof(szText) )
         {
            _template::checked::tcscat_s( szText, _countof(szText), szWinNumber ); 
         }
      }

      // set title if changed, but don't remove completely
      SetWindowText( szText);
   }
}

void SimpleMDIChildWindow::OnMDIActivate(BOOL bActivate, ::user::interaction* pActivateWnd, ::user::interaction*)
{
   m_bPseudoInactive = FALSE;  // must be happening for real

   // make sure MDI client ::ca::window has correct client edge
   UpdateClientEdge();

   // send deactivate notification to active ::view
   ::view * pActiveView = GetActiveView();
   if (!bActivate && pActiveView != NULL)
      pActiveView->OnActivateView(FALSE, pActiveView, pActiveView);

   // allow hook to short circuit normal activation
   BOOL bHooked = FALSE;
   /*
#ifndef _AFX_NO_OLE_SUPPORT
   if (m_pNotifyHook != NULL && m_pNotifyHook->OnDocActivate(bActivate))
      bHooked = TRUE;
#endif
*/
   // update titles (don't AddToTitle if deactivate last)
   if (!bHooked)
      on_update_frame_title(bActivate || (pActivateWnd != NULL));

   // re-activate the appropriate ::view
   if (bActivate)
   {
      if (pActiveView != NULL && GetMDIFrame() == GetActiveWindow())
         pActiveView->OnActivateView(TRUE, pActiveView, pActiveView);
   }

   // update menus
   if (!bHooked)
   {
      OnUpdateFrameMenu(bActivate, pActivateWnd, NULL);
   }
}

void SimpleMDIChildWindow::OnUpdateFrameMenu(BOOL bActivate, ::user::interaction* pActivateWnd,
   HMENU hMenuAlt)
{
   SimpleMDIFrameWindow* pFrame = GetMDIFrame();

   if (hMenuAlt == NULL && bActivate)
   {
      // attempt to get default menu from document
      document * pDoc = GetActiveDocument();
      if (pDoc != NULL)
         hMenuAlt = pDoc->GetDefaultMenu();
   }

   // use default menu stored in frame if none from document
   if (hMenuAlt == NULL)
      hMenuAlt = m_hMenuShared;

   if (hMenuAlt != NULL && bActivate)
   {
      ASSERT(pActivateWnd == this);

      // activating child, set parent menu
      pFrame->m_pguieMdiClient->SendMessage( WM_MDISETMENU,
         (WPARAM)hMenuAlt, (LPARAM)pFrame->GetWindowMenuPopup(hMenuAlt));
   }
   else if (hMenuAlt != NULL && !bActivate && pActivateWnd == NULL)
   {
      // destroying last child
      HMENU hMenuLast = NULL;
      pFrame->m_pguieMdiClient->SendMessage( WM_MDISETMENU,
         (WPARAM)pFrame->m_hMenuDefault, (LPARAM)hMenuLast);
   }
   else
   {
      // refresh MDI Window menu (even if non-shared menu)
      pFrame->m_pguieMdiClient->SendMessage( WM_MDIREFRESHMENU, 0, 0);
   }
}

BOOL SimpleMDIChildWindow::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
// trans   if (!frame_window::OnNcCreate(lpCreateStruct))
      //return FALSE;

   // handle extended styles under Win4
   // call PreCreateWindow again just to get dwExStyle
   VERIFY(PreCreateWindow(*lpCreateStruct));
   SetWindowLong(GWL_EXSTYLE, lpCreateStruct->dwExStyle);

   return TRUE;
}

void SimpleMDIChildWindow::_001OnCreate(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::create, pcreate, pobj);
   // call base class with lParam context (not MDI one)
   MDICREATESTRUCT* lpmcs;
   lpmcs = (MDICREATESTRUCT*)pcreate->m_lpcreatestruct->lpCreateParams;
   create_context* pContext = (create_context*)lpmcs->lParam;
   pcreate->previous();
   pcreate->set_lresult(OnCreateHelper(pcreate->m_lpcreatestruct, pContext));
   pcreate->m_bRet = true;
}

/////////////////////////////////////////////////////////////////////////////
// Special UI processing depending on current active child

void SimpleMDIFrameWindow::on_update_frame_title(BOOL bAddToTitle)
{
   if ((GetStyle() & FWS_ADDTOTITLE) == 0)
      return;     // leave it alone!
/*
#ifndef _AFX_NO_OLE_SUPPORT
   // allow hook to set the title (used for OLE support)
   if (m_pNotifyHook != NULL && m_pNotifyHook->on_update_frame_title())
      return;
#endif
*/
   SimpleMDIChildWindow* pActiveChild = NULL;
   document * pdocument = GetActiveDocument();
   if (bAddToTitle &&
     (pActiveChild = (dynamic_cast < SimpleMDIChildWindow * > (MDIGetActive()))) != NULL &&
     (pActiveChild->GetStyle() & WS_MAXIMIZE) == 0 &&
     (pdocument != NULL ||
      (pdocument = pActiveChild->GetActiveDocument()) != NULL))
      UpdateFrameTitleForDocument(pdocument->get_title());
   else
   {
      const char * lpstrTitle = NULL;
      string strTitle;

      if (pActiveChild != NULL &&
         (pActiveChild->GetStyle() & WS_MAXIMIZE) == 0)
      {
         strTitle = pActiveChild->get_title();
         if (!strTitle.is_empty())
            lpstrTitle = strTitle;
      }
      UpdateFrameTitleForDocument(lpstrTitle);
   }
}

/////////////////////////////////////////////////////////////////////////////
// Standard MDI Commands

// Two function for all standard MDI "Window" commands
void SimpleMDIFrameWindow::OnUpdateMDIWindowCmd(cmd_ui * pcmdui)
{
   ASSERT(m_pguieMdiClient != NULL);
   pcmdui->Enable(MDIGetActive() != NULL);
}

BOOL SimpleMDIFrameWindow::OnMDIWindowCmd(UINT nID)
{
   ASSERT(m_pguieMdiClient != NULL);

   UINT msg;
   UINT wParam = 0;
   switch (nID)
   {
   default:
      return FALSE;       // not for us
   case ID_WINDOW_ARRANGE:
      msg = WM_MDIICONARRANGE;
      break;
   case ID_WINDOW_CASCADE:
      msg = WM_MDICASCADE;
      break;
   case ID_WINDOW_TILE_HORZ:
      wParam = MDITILE_HORIZONTAL;
      // fall through
   case ID_WINDOW_TILE_VERT:
      ASSERT(MDITILE_VERTICAL == 0);
      msg = WM_MDITILE;
      break;
   }

   m_pguieMdiClient->SendMessage(msg, wParam, 0);
   return TRUE;
}

void SimpleMDIFrameWindow::OnWindowNew()
{
   SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
   document * pdocument;
   if (pActiveChild == NULL ||
     (pdocument = pActiveChild->GetActiveDocument()) == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: No active document for WindowNew command.\n");
      // linhx System.simple_message_box(AFX_IDP_COMMAND_FAILURE);
      System.simple_message_box(NULL, "Command Failure");
      return;     // command failed
   }

   // otherwise we have a new frame !
   document_template * ptemplate = pdocument->get_document_template();
   ASSERT_VALID(ptemplate);
   ::frame_window* pFrame = ptemplate->create_new_frame(pdocument, pActiveChild);
   if (pFrame == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: failed to create new frame.\n");
      return;     // command failed
   }

   ptemplate->InitialUpdateFrame(pFrame, pdocument);
}


// IMPLEMENT_DYNCREATE(SimpleMDIFrameWindow, frame_window)
// IMPLEMENT_DYNCREATE(SimpleMDIChildWindow, frame_window)

////////////////////////////////////////////////////////////////////////////

void SimpleMDIChildWindow::MDIDestroy()
   { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIDESTROY, (WPARAM)this, 0L); }
void SimpleMDIChildWindow::MDIActivate()
   { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIACTIVATE, (WPARAM)this, 0L); }
void SimpleMDIChildWindow::MDIMaximize()
   { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIMAXIMIZE, (WPARAM)this, 0L); }
void SimpleMDIChildWindow::MDIRestore()
   { ASSERT(IsWindow()); GetParent()->SendMessage( WM_MDIRESTORE, (WPARAM)this, 0L); }
