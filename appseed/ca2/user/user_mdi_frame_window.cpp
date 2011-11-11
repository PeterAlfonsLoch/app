#include "StdAfx.h"



/////////////////////////////////////////////////////////////////////////////
// CMDIFrameWnd

// // BEGIN_MESSAGE_MAP(CMDIFrameWnd, frame_window)
   //{{AFX_MSG_MAP(CMDIFrameWnd)
   /* xxx ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, CMDIFrameWnd::OnIdleUpdateCmdUI)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, &CMDIFrameWnd::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, &CMDIFrameWnd::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, &CMDIFrameWnd::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_VERT, &CMDIFrameWnd::OnUpdateMDIWindowCmd)
   ON_WM_SIZE()
   ON_COMMAND_EX(ID_WINDOW_ARRANGE, &CMDIFrameWnd::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_CASCADE, &CMDIFrameWnd::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_TILE_HORZ, &CMDIFrameWnd::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_TILE_VERT, &CMDIFrameWnd::OnMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, &CMDIFrameWnd::OnUpdateMDIWindowCmd)
   ON_COMMAND(ID_WINDOW_NEW, &CMDIFrameWnd::OnWindowNew)
   ON_WM_DESTROY()
   ON_MESSAGE(WM_COMMANDHELP, &CMDIFrameWnd::OnCommandHelp)
   ON_WM_MENUCHAR() */
   //}}AFX_MSG_MAP
// // END_MESSAGE_MAP()

CMDIFrameWnd::CMDIFrameWnd()
{
   m_pguieMdiClient = NULL;
}

BOOL CMDIFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
   // send to MDI child first - will be re-sent through _001OnCommand later
//   CMDIChildWnd* pActiveChild = MDIGetActive();
/*trans   if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
     pActiveChild->_get_handle(), WM_COMMAND, wParam, lParam) != 0)
      return TRUE; // handled by child*/

   if (frame_window::OnCommand(wParam, lParam))
      return TRUE; // handled through normal mechanism (MDI child or frame)

   HWND hWndCtrl = (HWND)lParam;

   ASSERT(AFX_IDM_FIRST_MDICHILD == 0xFF00);
   if (hWndCtrl == NULL && (LOWORD(wParam) & 0xf000) == 0xf000)
   {
      // menu or accelerator within range of MDI children
      // default frame proc will handle it
      DefWindowProc(WM_COMMAND, wParam, lParam);
      return TRUE;
   }

   return FALSE;   // not handled
}

bool CMDIFrameWnd::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{
   CMDIChildWnd* pActiveChild = MDIGetActive();
   // pump through active child FIRST
   if (pActiveChild != NULL)
   {
      if (pActiveChild->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }

   // then pump through normal frame
   return frame_window::_001OnCmdMsg(pcmdmsg);
}

LRESULT CMDIFrameWnd::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   if (lParam == 0 && IsTracking())
      lParam = HID_BASE_COMMAND+m_nIDTracking;

//   CMDIChildWnd* pActiveChild = MDIGetActive();
/* trans   if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
     pActiveChild->_get_handle(), WM_COMMANDHELP, wParam, lParam) != 0)
   {
      // handled by child
      return TRUE;
   }*/

//   if (frame_window::OnCommandHelp(wParam, lParam))
//   {
      // handled by our base
//      return TRUE;
//   }

   if (lParam != 0)
   {
      ::radix::application* pApp = &System;
      if (pApp != NULL)
      {
         System.WinHelpInternal(lParam);
         return TRUE;
      }
   }
   return FALSE;
}

BOOL CMDIFrameWnd::OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context*)
{
   return CreateClient(lpcs);
}

BOOL CMDIFrameWnd::CreateClient(LPCREATESTRUCT lpCreateStruct)
{
// trans   ASSERT(_get_handle() != NULL);
   ASSERT(m_pguieMdiClient == NULL);
   DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_BORDER |
      WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
      MDIS_ALLCHILDSTYLES;    // allow children to be created invisible
   DWORD dwExStyle = 0;
   // will be inset by the frame

   // special styles for 3d effect on Win4
   dwStyle &= ~WS_BORDER;
   dwExStyle = WS_EX_CLIENTEDGE;

   CLIENTCREATESTRUCT ccs;
      // set hWindowMenu for ca2 API V1 backward compatibility
      // for ca2 API V2, ::ca::window menu will be set in OnMDIActivate
   ccs.idFirstChild = AFX_IDM_FIRST_MDICHILD;

   if (lpCreateStruct->style & (WS_HSCROLL|WS_VSCROLL))
   {
      // parent MDIFrame's scroll styles move to the MDICLIENT
      dwStyle |= (lpCreateStruct->style & (WS_HSCROLL|WS_VSCROLL));

      // fast way to turn off the scrollbar bits (without a resize)
      ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_NOREDRAW|SWP_FRAMECHANGED);
   }

   // create MDICLIENT control with special IDC
   if ((m_pguieMdiClient = ::CreateGuieEx(get_app(), dwExStyle, "mdiclient", NULL,
      dwStyle, 0, 0, 0, 0, this, AFX_IDW_PANE_FIRST,
      System.m_hInstance, (LPVOID)&ccs)) == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: CMDIFrameWnd::OnCreateClient: failed to create MDICLIENT."
         " GetLastError returns 0x%8.8X\n", ::GetLastError());
      return FALSE;
   }
   // Move it to the top of z-order
   m_pguieMdiClient->BringWindowToTop();

   return TRUE;
}

LRESULT CMDIFrameWnd::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   return ::DefFrameProc(_get_handle(), m_pguieMdiClient->_get_handle(), nMsg, wParam, lParam);
}

void CMDIFrameWnd::pre_translate_message(gen::signal_object * pobj)
{
   // check for special cancel modes for ComboBoxes
   //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
   //   AfxCancelModes(pMsg->hwnd);    // filter clicks

   // allow tooltip messages to be filtered
   ::user::interaction::pre_translate_message(pobj);
   if(pobj->m_bRet)
      return;

   CMDIChildWnd* pActiveChild = MDIGetActive();

   // current active child gets first crack at it
   if (pActiveChild != NULL)
   {
      pActiveChild->pre_translate_message(pobj);
      if(pobj->m_bRet)
         return;
   }
   
   SCAST_PTR(user::win::message::base, pbase, pobj);

   if(pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
   {
      // translate accelerators for frame and any children
      /* linux if (m_hAccelTable != NULL &&
         ::TranslateAccelerator(_get_handle(), m_hAccelTable, pMsg))
      {
         return TRUE;
      }*/

      // special processing for MDI accelerators last
      // and only if it is not in SDI mode (print preview)
      if (GetActiveView() == NULL)
      {
         if (pbase->m_uiMessage == WM_KEYDOWN || pbase->m_uiMessage == WM_SYSKEYDOWN)
         {
            // the MDICLIENT ::ca::window may translate it
/*trans            if (::TranslateMDISysAccel(m_pguieMdiClient, pMsg))
               return TRUE;*/
         }
      }
   }
}

void CMDIFrameWnd::DelayUpdateFrameMenu(HMENU hMenuAlt)
{
   OnUpdateFrameMenu(hMenuAlt);

   m_nIdleFlags |= idleMenu;
}

void CMDIFrameWnd::OnIdleUpdateCmdUI()
{
   if (m_nIdleFlags & idleMenu)
   {
      m_nIdleFlags &= ~idleMenu;
   }
   frame_window::OnIdleUpdateCmdUI();
}

frame_window* CMDIFrameWnd::GetActiveFrame()
{
   CMDIChildWnd* pActiveChild = MDIGetActive();
   if (pActiveChild == NULL)
      return this;
   return pActiveChild;
}

BOOL CMDIFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   if (cs.lpszClass == NULL)
   {
      System.DeferRegisterClass(AFX_WNDMDIFRAME_REG, &cs.lpszClass);
   }
   return TRUE;
}

BOOL CMDIFrameWnd::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,  ::user::interaction* pParentWnd, ::ca::create_context* pContext)
{
   if (!frame_window::LoadFrame(pszMatter, dwDefaultStyle,
     pParentWnd, pContext))
      return FALSE;

   // save menu to use when no active MDI child ::ca::window is present
   ASSERT(_get_handle() != NULL);
   m_hMenuDefault = ::GetMenu(_get_handle());
   if (m_hMenuDefault == NULL)
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: CMDIFrameWnd without a default menu.\n");
   return TRUE;
}

void CMDIFrameWnd::_001OnDestroy(gen::signal_object * pobj)
{
   pobj->previous();
   //frame_window::OnDestroy();     // exit and misc cleanup

   // owned menu stored in shared slot for MDIFRAME
   if (m_hMenuDefault != NULL && ::GetMenu(_get_handle()) != m_hMenuDefault)
   {
      // must go through MDI client to get rid of MDI menu additions
      m_pguieMdiClient->SendMessage(WM_MDISETMENU,
         (WPARAM)m_hMenuDefault, NULL);
      ASSERT(::GetMenu(_get_handle()) == m_hMenuDefault);
   }
}

void CMDIFrameWnd::OnSize(UINT nType, int, int)
{
   // do not call default - it will reposition the MDICLIENT
   if (nType != SIZE_MINIMIZED)
      layout();
}

LRESULT CMDIFrameWnd::OnMenuChar(UINT nChar, UINT, ::userbase::menu*)
{
   // do not call Default() for Alt+(-) when in print preview mode
   if (m_lpfnCloseProc != NULL && nChar == (UINT)'-')
      return 0;
   else
      return Default();
}

CMDIChildWnd* CMDIFrameWnd::MDIGetActive(BOOL* pbMaximized) const
{
   // check first for MDI client ::ca::window not created
   if (m_pguieMdiClient == NULL)
   {
      if (pbMaximized != NULL)
         *pbMaximized = FALSE;
      return NULL;
   }

   // MDI client has been created, get active MDI child
   ::user::interaction * hWnd = (::user::interaction *)m_pguieMdiClient->SendMessage(WM_MDIGETACTIVE, 0,
      (LPARAM)pbMaximized);
   CMDIChildWnd* pWnd = dynamic_cast < CMDIChildWnd * > (hWnd);
   ASSERT(pWnd == NULL || base <CMDIChildWnd> :: bases(pWnd));

   // check for special pseudo-inactive state
   if (pWnd != NULL && pWnd->m_bPseudoInactive &&
      (pWnd->GetStyle() & WS_VISIBLE) == 0)
   {
      // Window is hidden, active, but m_bPseudoInactive -- return NULL
      pWnd = NULL;
      // Ignore maximized flag if pseudo-inactive and maximized
      if (pbMaximized != NULL)
         *pbMaximized = FALSE;
   }
   return pWnd;
}


CMDIChildWnd* CMDIFrameWnd::CreateNewChild(::ca::type_info pClass,
      const char * pszMatter, HMENU hMenu /* = NULL */, HACCEL hAccel /* = NULL */)
{
   UNREFERENCED_PARAMETER(pClass);
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(hMenu);
   UNREFERENCED_PARAMETER(hAccel);
   return NULL;
}



/*
CMDIChildWnd* CMDIFrameWnd::CreateNewChild(::ca::type_info pClass,
      //const char * pszMatter, HMENU hMenu /* = NULL *///, HACCEL hAccel /* = NULL */)
/*{
   ASSERT(pClass != NULL);
   CMDIChildWnd* pFrame = dynamic_cast < CMDIChildWnd* > (System.alloc(pClass));
   ASSERT_KINDOF(CMDIChildWnd, pFrame);

   // load the frame
   create_context context;
   context.m_pCurrentFrame = this;

   pFrame->SetHandles(hMenu, hAccel);
   if (!pFrame->LoadFrame(pszMatter,
         WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, &context))
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Couldn't load frame ::ca::window.\n");
      delete pFrame;
      return NULL;
   }

   string strFullString, strTitle;
   strFullString = Application.file().as_string(System.dir().path(Application.dir().matter(pszMatter, "string.txt"));
   if(strFullString.get_length() > 0)
      AfxExtractSubString(strTitle, strFullString, document_template::docName);

   // redraw the frame and parent
   pFrame->set_title(strTitle);
   pFrame->InitialUpdateFrame(NULL, TRUE);

   return pFrame;
}*/

/////////////////////////////////////////////////////////////////////////////
// CMDIFrameWnd Diagnostics

#ifdef _DEBUG
void CMDIFrameWnd::assert_valid() const
{
   frame_window::assert_valid();
   ASSERT(m_pguieMdiClient == NULL || m_pguieMdiClient->IsWindow());
   ASSERT(m_hMenuDefault == NULL || ::IsMenu(m_hMenuDefault));
}

void CMDIFrameWnd::dump(dump_context & dumpcontext) const
{
   frame_window::dump(dumpcontext);

   dumpcontext << "m_pguieMdiClient = " << (void *)m_pguieMdiClient;
   dumpcontext << "\nm_hMenuDefault = " << (void *)m_hMenuDefault;

   dumpcontext << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIChildWnd

// // BEGIN_MESSAGE_MAP(CMDIChildWnd, frame_window)
   //{{AFX_MSG_MAP(CMDIChildWnd)
/* xxx   ON_WM_MOUSEACTIVATE()
   ON_WM_NCACTIVATE()
   ON_WM_MDIACTIVATE()
   ON_WM_SIZE()
   ON_WM_WINDOWPOSCHANGING()
   ON_WM_NCCREATE()
   ON_WM_CREATE()
   ON_WM_DESTROY()
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &CMDIChildWnd::OnToolTipText)
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &CMDIChildWnd::OnToolTipText) */
   //}}AFX_MSG_MAP
// // END_MESSAGE_MAP()

CMDIChildWnd::CMDIChildWnd()
{
   m_hMenuShared = NULL;
   m_bPseudoInactive = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMDIChildWnd special processing

LRESULT CMDIChildWnd::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   return ::DefMDIChildProc(_get_handle(), nMsg, wParam, lParam);
}

BOOL CMDIChildWnd::DestroyWindow()
{
   if (_get_handle() == NULL)
      return FALSE;

   // avoid changing the caption during the destroy message(s)
   CMDIFrameWnd* pFrameWnd = GetMDIFrame();
   HWND hWndFrame = pFrameWnd->_get_handle();
   ASSERT(::IsWindow(hWndFrame));
   DWORD dwStyle = ::SetWindowLong(hWndFrame, GWL_STYLE,
      ::GetWindowLong(hWndFrame, GWL_STYLE) & ~FWS_ADDTOTITLE);

   MDIDestroy();

   if (::IsWindow(hWndFrame))
   {
      ASSERT(hWndFrame == pFrameWnd->_get_handle());
      ::SetWindowLong(hWndFrame, GWL_STYLE, dwStyle);
      pFrameWnd->on_update_frame_title(TRUE);
   }

   return TRUE;
}

void CMDIChildWnd::pre_translate_message(gen::signal_object * pobj)
{
   // check for special cancel modes for combo boxes
   //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
   //   AfxCancelModes(pMsg->hwnd);    // filter clicks

   // allow tooltip messages to be filtered
   ::user::interaction::pre_translate_message(pobj);
   if(pobj->m_bRet)
      return;

   SCAST_PTR(user::win::message::base, pbase, pobj);

   // we can't call 'frame_window::PreTranslate' since it will translate
   //  accelerators in the context of the MDI Child - but since MDI Child
   //  windows don't have menus this doesn't work properly.  MDI Child
   //  accelerators must be translated in context of their MDI Frame.

   if (pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
   {
      // use document specific accelerator table over m_hAccelTable
      //HACCEL hAccel = GetDefaultAccelerator();
      /* linux return hAccel != NULL &&
         ::TranslateAccelerator(GetMDIFrame()->_get_handle(), hAccel, pMsg);*/
   }
}

BOOL CMDIChildWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   ASSERT(cs.style & WS_CHILD);
      // ca2 API V2 requires that MDI Children are created with proper styles,
      //  usually: WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW.
      // See Technical note TN019 for more details on ca2 API V1->V2 migration.

   return frame_window::PreCreateWindow(cs);
}

BOOL CMDIChildWnd::create(const char * lpszClassName,
   const char * lpszWindowName, DWORD dwStyle,
   const RECT& rect, CMDIFrameWnd* pParentWnd,
   ::ca::create_context * pContext)
{
   if (pParentWnd == NULL)
   {
      ::radix::thread *pThread = System.GetThread();
      ENSURE_VALID(pThread);
      ::user::interaction* pMainWnd = pThread->GetMainWnd();
      ENSURE_VALID(pMainWnd);
      ASSERT_KINDOF(CMDIFrameWnd, pMainWnd);
      pParentWnd = dynamic_cast < CMDIFrameWnd * > (pMainWnd);
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
   ASSERT(cs.hwndParent == pParentWnd->_get_handle());    // must not change

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
//   AfxHookWindowCreate(this);
   HWND hWnd = (HWND)pParentWnd->m_pguieMdiClient->SendMessage(
      WM_MDICREATE, 0, (LPARAM)&mcs);
   //if (!AfxUnhookWindowCreate())
   //   PostNcDestroy();        // cleanup if MDICREATE fails too soon

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

   ASSERT(hWnd == _get_handle());
   return TRUE;
}

BOOL CMDIChildWnd::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
      ::user::interaction* pParentWnd, ::ca::create_context* pContext)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(dwDefaultStyle);
   UNREFERENCED_PARAMETER(pParentWnd);
   UNREFERENCED_PARAMETER(pContext);
   return FALSE;
   // only do this once
//   ASSERT_VALID_IDR(nIDResource);
//   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   /*m_nIDHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   // parent must be MDI Frame (or NULL for default)
   ASSERT(pParentWnd == NULL || base < CMDIFrameWnd >::bases(pParentWnd));
   // will be a child of MDIClient
   ASSERT(!(dwDefaultStyle & WS_POPUP));
   dwDefaultStyle |= WS_CHILD;

   // if available - get MDI child menus from doc template
   multiple_document_template* ptemplate;
   if (pContext != NULL &&
      (ptemplate = dynamic_cast < multiple_document_template * > (pContext->m_pNewDocTemplate)) != NULL)
   {
      ASSERT_KINDOF(multiple_document_template, ptemplate);
      // get shared menu from doc template
      m_hMenuShared = ptemplate->m_hMenuShared;
      m_hAccelTable = ptemplate->m_hAccelTable;
   }
   else
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: no shared menu/acceltable for MDI Child ::ca::window.\n");
         // if this happens, programmer must load these manually
   }

   string strFullString, strTitle;
   strFullString = Application.file().as_string(System.dir().path(Application.dir().matter(pszMatter, "string.txt"));
   if(strFullString.get_length() > 0)
      AfxExtractSubString(strTitle, strFullString, 0);    // first sub-string

   ASSERT(_get_handle() == NULL);
   if (!create(GetIconWndClass(dwDefaultStyle, pszMatter),
     strTitle, dwDefaultStyle, rectDefault,
     dynamic_cast < CMDIFrameWnd * > (pParentWnd), pContext))
   {
      return FALSE;   // will self destruct on failure normally
   }

   // it worked !
   return TRUE;*/
}

void CMDIChildWnd::OnSize(UINT nType, int cx, int cy)
{
   frame_window::OnSize(nType, cx, cy);

   // update our parent frame - in case we are now maximized or not
   GetMDIFrame()->on_update_frame_title(TRUE);
}

BOOL CMDIChildWnd::UpdateClientEdge(LPRECT lpRect)
{
   // only adjust for active MDI child ::ca::window
   CMDIFrameWnd* pFrameWnd = GetMDIFrame();
   CMDIChildWnd* pChild = pFrameWnd->MDIGetActive();
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
         pFrameWnd->m_pguieMdiClient->SetWindowLong( GWL_EXSTYLE, dwNewStyle);
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

void CMDIChildWnd::OnWindowPosChanging(LPWINDOWPOS lpWndPos)
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

   // trans frame_window::OnWindowPosChanging(lpWndPos);
}

void CMDIChildWnd::OnDestroy()
{
   UpdateClientEdge();

//   frame_window::OnDestroy();
}

BOOL CMDIChildWnd::OnNcActivate(BOOL bActive)
{
   UNREFERENCED_PARAMETER(bActive);
   // bypass frame_window::OnNcActivate()
/*   return ::user::interaction::OnNcActivate(bActive); */
   return FALSE;
}

int CMDIChildWnd::OnMouseActivate(::ca::window * pDesktopWnd, UINT nHitTest, UINT message)
{
   UNREFERENCED_PARAMETER(pDesktopWnd);
   UNREFERENCED_PARAMETER(nHitTest);
   UNREFERENCED_PARAMETER(message);
/* trans   int nResult = frame_window::OnMouseActivate(pDesktopWnd, nHitTest, message);
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
      return nResult;   // frame does not want to activate */

   // activate this ::ca::window if necessary
   CMDIFrameWnd* pFrameWnd = GetMDIFrame();
   ASSERT_VALID(pFrameWnd);
   CMDIChildWnd* pActive = pFrameWnd->MDIGetActive();
   if (pActive != this)
      MDIActivate();

   // trans return nResult;
   return 0;
}


void CMDIChildWnd::ActivateFrame(int nCmdShow)
{
   BOOL bVisibleThen = (GetStyle() & WS_VISIBLE) != 0;
   CMDIFrameWnd* pFrameWnd = GetMDIFrame();
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
   CMDIFrameWnd* pFrame = GetMDIFrame();
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
      HWND hWnd = (HWND)pFrameWnd->m_pguieMdiClient->SendMessage(
         WM_MDIGETACTIVE, 0, 0);
      if (hWnd != _get_handle())
      {
         // not active any more -- ::ca::window must have been deactivated
         ASSERT(!m_bPseudoInactive);
         return;
      }

      // check next ::ca::window
      ASSERT(hWnd != NULL);
      pFrameWnd->MDINext();

      // see if it has been deactivated now...
      hWnd = (HWND)pFrameWnd->m_pguieMdiClient->SendMessage(
         WM_MDIGETACTIVE, 0, 0);
      if (hWnd == _get_handle())
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

void CMDIChildWnd::SetHandles(HMENU hMenu, HACCEL hAccel)
{
   m_hMenuShared = hMenu;
   m_hAccelTable = hAccel;
}

/////////////////////////////////////////////////////////////////////////////
// CMDIChildWnd Diagnostics

#ifdef _DEBUG
void CMDIChildWnd::assert_valid() const
{
   frame_window::assert_valid();
   ASSERT(m_hMenuShared == NULL || ::IsMenu(m_hMenuShared));
}

void CMDIChildWnd::dump(dump_context & dumpcontext) const
{
   frame_window::dump(dumpcontext);

   dumpcontext << "m_hMenuShared = " << (void *)m_hMenuShared;
   dumpcontext << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Smarts for the "Window" menu

HMENU CMDIFrameWnd::GetWindowMenuPopup(HMENU hMenuBar)
   // find which popup is the "Window" menu
{
   if (hMenuBar == NULL)
      return NULL;

   ASSERT(::IsMenu(hMenuBar));

   int iItem = ::GetMenuItemCount(hMenuBar);
   while (iItem--)
   {
      HMENU hMenuPop = ::GetSubMenu(hMenuBar, iItem);
      if (hMenuPop != NULL)
      {
         int iItemMax = ::GetMenuItemCount(hMenuPop);
         for (int iItemPop = 0; iItemPop < iItemMax; iItemPop++)
         {
            UINT nID = GetMenuItemID(hMenuPop, iItemPop);
            if (nID >= AFX_IDM_WINDOW_FIRST && nID <= AFX_IDM_WINDOW_LAST)
               return hMenuPop;
         }
      }
   }

   // no default menu found
   TRACE(::radix::trace::category_AppMsg, 0, "Warning: GetWindowMenuPopup failed!\n");
   return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Smarts for updating the ::ca::window menu based on the current child

void CMDIFrameWnd::OnUpdateFrameMenu(HMENU hMenuAlt)
{
   CMDIChildWnd* pActiveWnd = MDIGetActive();
   if (pActiveWnd != NULL)
   {
      // let child update the menu bar
      pActiveWnd->OnUpdateFrameMenu(TRUE, pActiveWnd, hMenuAlt);
   }
   else
   {
      // no child active, so have to update it ourselves
      //  (we can't send it to a child ::ca::window, since pActiveWnd is NULL)
      if (hMenuAlt == NULL)
         hMenuAlt = m_hMenuDefault;  // use default
      m_pguieMdiClient->SendMessage(WM_MDISETMENU, (WPARAM)hMenuAlt, NULL);
   }
}

/////////////////////////////////////////////////////////////////////////////
// MDI Child Extensions

// walk up two parents for MDIFrame that owns MDIChild (skip MDIClient)
CMDIFrameWnd* CMDIChildWnd::GetMDIFrame()
{
   ASSERT_KINDOF(CMDIChildWnd, this);
   ASSERT(_get_handle() != NULL);
   ::user::interaction * hWndMDIClient = GetParent();
   ASSERT(hWndMDIClient != NULL);

   CMDIFrameWnd* pMDIFrame;
   pMDIFrame = dynamic_cast < CMDIFrameWnd * > (hWndMDIClient->GetParent());
   ASSERT(pMDIFrame != NULL);
   ASSERT_KINDOF(CMDIFrameWnd, pMDIFrame);
   ASSERT(pMDIFrame->m_pguieMdiClient == hWndMDIClient);
   ASSERT_VALID(pMDIFrame);
   return pMDIFrame;
}

::user::interaction* CMDIChildWnd::GetMessageBar()
{
   // status bar/message bar owned by parent MDI frame
   return GetMDIFrame()->GetMessageBar();
}

void CMDIChildWnd::on_update_frame_title(BOOL bAddToTitle)
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
         _template::checked::strncpy_s(szText, _countof(szText), m_strTitle, _TRUNCATE);
      else
         _template::checked::strncpy_s(szText, _countof(szText), pdocument->get_title(), _TRUNCATE);
      if (m_nWindow > 0)
      {
         char szWinNumber[16+1];
         _stprintf_s(szWinNumber, _countof(szWinNumber), ":%d", m_nWindow);
         
         if( lstrlen(szText) + lstrlen(szWinNumber) < _countof(szText) )
         {
            _template::checked::strcat_s( szText, _countof(szText), szWinNumber ); 
         }
      }

      // set title if changed, but don't remove completely
//      throw not implemented_exception();
         SetWindowText(szText);
   }
}

void CMDIChildWnd::OnMDIActivate(BOOL bActivate, ::user::interaction* pActivateWnd, ::user::interaction*)
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

void CMDIChildWnd::OnUpdateFrameMenu(BOOL bActivate, ::user::interaction* pActivateWnd,
   HMENU hMenuAlt)
{
   CMDIFrameWnd* pFrame = GetMDIFrame();

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

BOOL CMDIChildWnd::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
/* trans   if (!frame_window::OnNcCreate(lpCreateStruct))
      return FALSE;*/

   // handle extended styles under Win4
   // call PreCreateWindow again just to get dwExStyle
   VERIFY(PreCreateWindow(*lpCreateStruct));
   SetWindowLong(GWL_EXSTYLE, lpCreateStruct->dwExStyle);

   return TRUE;
}

int CMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // call base class with lParam context (not MDI one)
   MDICREATESTRUCT* lpmcs;
   lpmcs = (MDICREATESTRUCT*)lpCreateStruct->lpCreateParams;
   ::ca::create_context* pContext = (::ca::create_context*)lpmcs->lParam;

   return OnCreateHelper(lpCreateStruct, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// Special UI processing depending on current active child

void CMDIFrameWnd::on_update_frame_title(BOOL bAddToTitle)
{
   if ((GetStyle() & FWS_ADDTOTITLE) == 0)
      return;     // leave it alone!

   CMDIChildWnd* pActiveChild = NULL;
   document * pdocument = GetActiveDocument();
   if (bAddToTitle &&
     (pActiveChild = MDIGetActive()) != NULL &&
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
void CMDIFrameWnd::OnUpdateMDIWindowCmd(cmd_ui* pCmdUI)
{
   ASSERT(m_pguieMdiClient != NULL);
   pCmdUI->Enable(MDIGetActive() != NULL);
}

BOOL CMDIFrameWnd::OnMDIWindowCmd(UINT nID)
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

void CMDIFrameWnd::OnWindowNew()
{
   CMDIChildWnd* pActiveChild = MDIGetActive();
   document * pdocument;
   if (pActiveChild == NULL ||
     (pdocument = pActiveChild->GetActiveDocument()) == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: No active document for WindowNew command.\n");
      //System.simple_message_box(AFX_IDP_COMMAND_FAILURE);
      System.simple_message_box(NULL, "Warning: No active document for WindowNew command.\n");
      return;     // command failed
   }

   // otherwise we have a new frame !
   document_template * ptemplate = pdocument->get_document_template();
   ASSERT_VALID(ptemplate);
   ::ca::create_context_sp cc(get_app());
   frame_window* pFrame = ptemplate->create_new_frame(pdocument, pActiveChild, cc);
   if (pFrame == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: failed to create new frame.\n");
      return;     // command failed
   }

   ptemplate->InitialUpdateFrame(pFrame, pdocument);
}


// IMPLEMENT_DYNCREATE(CMDIFrameWnd, frame_window)
// IMPLEMENT_DYNCREATE(CMDIChildWnd, frame_window)

////////////////////////////////////////////////////////////////////////////



// MDI functions
 void CMDIFrameWnd::MDIActivate(::user::interaction* pWndActivate)
   {  m_pguieMdiClient->SendMessage(WM_MDIACTIVATE,
      (WPARAM)pWndActivate, 0); }
 void CMDIFrameWnd::MDIIconArrange()
   {  m_pguieMdiClient->SendMessage(WM_MDIICONARRANGE, 0, 0); }
 void CMDIFrameWnd::MDIMaximize(::user::interaction * pWnd)
   {  m_pguieMdiClient->SendMessage(WM_MDIMAXIMIZE, (WPARAM)pWnd, 0); }
 void CMDIFrameWnd::MDIPrev()
   {  m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 1); }
 void CMDIFrameWnd::MDINext()
   {  m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 0); }
 void CMDIFrameWnd::MDIRestore(::user::interaction * pWnd)
   {  m_pguieMdiClient->SendMessage(WM_MDIRESTORE, (WPARAM)pWnd, 0); }
 void CMDIFrameWnd::MDITile()
   {  m_pguieMdiClient->SendMessage(WM_MDITILE, 0, 0); }
 void CMDIFrameWnd::MDICascade()
   {  m_pguieMdiClient->SendMessage(WM_MDICASCADE, 0, 0); }

 void CMDIFrameWnd::MDICascade(int nType)
   {  m_pguieMdiClient->SendMessage(WM_MDICASCADE, nType, 0); }
 void CMDIFrameWnd::MDITile(int nType)
   {  m_pguieMdiClient->SendMessage(WM_MDITILE, nType, 0); }
 