#include "StdAfx.h"

namespace userbase
{

   // IMPLEMENT_DYNCREATE(mdi_frame_window, userbase::::frame_window)

   /////////////////////////////////////////////////////////////////////////////
   // mdi_frame_window

   // // BEGIN_MESSAGE_MAP(mdi_frame_window, userbase::::frame_window)
      //{{AFX_MSG_MAP(mdi_frame_window)
   /* xxx   ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, mdi_frame_window::OnIdleUpdateCmdUI)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, &mdi_frame_window::OnUpdateMDIWindowCmd)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, &mdi_frame_window::OnUpdateMDIWindowCmd)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, &mdi_frame_window::OnUpdateMDIWindowCmd)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_VERT, &mdi_frame_window::OnUpdateMDIWindowCmd)
      ON_WM_SIZE()
      ON_COMMAND_EX(ID_WINDOW_ARRANGE, &mdi_frame_window::OnMDIWindowCmd)
      ON_COMMAND_EX(ID_WINDOW_CASCADE, &mdi_frame_window::OnMDIWindowCmd)
      ON_COMMAND_EX(ID_WINDOW_TILE_HORZ, &mdi_frame_window::OnMDIWindowCmd)
      ON_COMMAND_EX(ID_WINDOW_TILE_VERT, &mdi_frame_window::OnMDIWindowCmd)
      ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, &mdi_frame_window::OnUpdateMDIWindowCmd)
      ON_COMMAND(ID_WINDOW_NEW, &mdi_frame_window::OnWindowNew)
      ON_WM_DESTROY()
      ON_MESSAGE(WM_COMMANDHELP, &mdi_frame_window::OnCommandHelp)
      ON_WM_MENUCHAR()*/
      //}}AFX_MSG_MAP
   // // END_MESSAGE_MAP()

   mdi_frame_window::mdi_frame_window(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp)
   {
      m_pguieMdiClient = NULL;
   }

   BOOL mdi_frame_window::OnCommand(WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      // send to MDI child first - will be re-sent through _001OnCommand later
   /* trans   mdi_child_window* pActiveChild = MDIGetActive();
      if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
        pActiveChild->get_handle(), WM_COMMAND, wParam, lParam) != 0)
         return TRUE; // handled by child

      if (userbase::frame_window::OnCommand(wParam, lParam))
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
   */
      return FALSE;   // not handled
   }

   bool mdi_frame_window::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
      
   {
      mdi_child_window* pActiveChild = MDIGetActive();
      // pump through active child FIRST
      if (pActiveChild != NULL)
      {
   //      push_routing_frame push(this);
         if (pActiveChild->_001OnCmdMsg(pcmdmsg))
            return TRUE;
      }

      // then pump through normal frame
      return userbase::frame_window::_001OnCmdMsg(pcmdmsg);
   }

   LRESULT mdi_frame_window::OnCommandHelp(WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
   /* trans   if (lParam == 0 && IsTracking())
         lParam = HID_BASE_COMMAND+m_nIDTracking;

      mdi_child_window* pActiveChild = MDIGetActive();
      if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
        pActiveChild->, WM_COMMANDHELP, wParam, lParam) != 0)
      {
         // handled by child
         return TRUE;
      }

      if (userbase::frame_window::OnCommandHelp(wParam, lParam))
      {
         // handled by our base
         return TRUE;
      }

      if (lParam != 0)
      {
         application* pApp = &System;
         if (pApp != NULL)
         {
            System.WinHelpInternal(lParam);
            return TRUE;
         }
      }*/
      return FALSE;
   }

   BOOL mdi_frame_window::OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context*)
   {

      return CreateClient(lpcs, NULL);
   }

   BOOL mdi_frame_window::CreateClient(LPCREATESTRUCT lpCreateStruct,
      ::userbase::menu* pWindowMenu)
   {
      UNREFERENCED_PARAMETER(lpCreateStruct);
      UNREFERENCED_PARAMETER(pWindowMenu);

   //   ASSERT(get_handle() != NULL);
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
      ccs.hWindowMenu = NULL;
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
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: mdi_frame_window::OnCreateClient: failed to create MDICLIENT."
            " GetLastError returns 0x%8.8X\n", ::GetLastError());
         return FALSE;
      }
      // Move it to the top of z-order
      m_pguieMdiClient->BringWindowToTop();

      return TRUE;
   }

   LRESULT mdi_frame_window::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
   // trans   return ::DefFrameProc(get_handle(), m_pguieMdiClient, nMsg, wParam, lParam);
      return 0;
   }

   void mdi_frame_window::pre_translate_message(gen::signal_object * pobj)
   {
      // check for special cancel modes for ComboBoxes
      //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
      //   AfxCancelModes(pMsg->hwnd);    // filter clicks

      // allow tooltip messages to be filtered
      ::user::interaction::pre_translate_message(pobj);
      if(pobj->m_bRet)
         return;

   /*#ifndef _AFX_NO_OLE_SUPPORT
      // allow hook to consume message
      if (m_pNotifyHook != NULL && m_pNotifyHook->OnPreTranslateMessage(pMsg))
         return TRUE;
   #endif*/

      SCAST_PTR(gen::message::base, pbase, pobj);

      mdi_child_window* pActiveChild = MDIGetActive();

      // current active child gets first crack at it
      if (pActiveChild != NULL)
      {
         pActiveChild->pre_translate_message(pobj);
         if(pobj->m_bRet)
            return;
      }

      if (pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
      {
         // translate accelerators for frame and any children
   /* trans      if (m_hAccelTable != NULL &&
            ::TranslateAccelerator(get_handle(), m_hAccelTable, pMsg))
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
   /* trans            if (::TranslateMDISysAccel(m_pguieMdiClient, pMsg))
                  return TRUE; */
            }
         }
      }

   }

   void mdi_frame_window::DelayUpdateFrameMenu(HMENU hMenuAlt)
   {
      OnUpdateFrameMenu(hMenuAlt);

      m_nIdleFlags |= idleMenu;
   }

   void mdi_frame_window::OnIdleUpdateCmdUI()
   {
      if (m_nIdleFlags & idleMenu)
      {
         m_nIdleFlags &= ~idleMenu;
      }
      userbase::frame_window::OnIdleUpdateCmdUI();
   }

   ::frame_window * mdi_frame_window::GetActiveFrame()
   {
      mdi_child_window* pActiveChild = MDIGetActive();
      if (pActiveChild == NULL)
         return this;
      return pActiveChild;
   }

   BOOL mdi_frame_window::PreCreateWindow(CREATESTRUCT& cs)
   {
      if (cs.lpszClass == NULL)
      {
         VERIFY(System.DeferRegisterClass(AFX_WNDMDIFRAME_REG, &cs.lpszClass));
         
      }
      return TRUE;
   }

   BOOL mdi_frame_window::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
      ::user::interaction* pParentWnd, ::ca::create_context* pContext)
   {
      if (!userbase::frame_window::LoadFrame(pszMatter, dwDefaultStyle,
        pParentWnd, pContext))
         return FALSE;

      // save menu to use when no active MDI child ::ca::window is present
   /* trans   ASSERT(get_handle() != NULL);
      m_hMenuDefault = ::GetMenu(get_handle());
      if (m_hMenuDefault == NULL)
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: mdi_frame_window without a default menu.\n"); */
      return TRUE;
   }

   void mdi_frame_window::OnDestroy()
   {
   //trans   userbase::frame_window::OnDestroy();     // exit and misc cleanup

      // owned menu stored in shared slot for MDIFRAME
   /* trans   if (m_hMenuDefault != NULL && ::GetMenu(get_handle()) != m_hMenuDefault)
      {
         // must go through MDI client to get rid of MDI menu additions
         m_pguieMdiClient->SendMessage(WM_MDISETMENU,
            (WPARAM)m_hMenuDefault, NULL);
         ASSERT(::GetMenu(_get_handle()) == m_hMenuDefault);
      }*/
   }

   void mdi_frame_window::OnSize(UINT nType, int, int)
   {
      // do not call default - it will reposition the MDICLIENT
      if (nType != SIZE_MINIMIZED)
         layout();
   }

   LRESULT mdi_frame_window::OnMenuChar(UINT nChar, UINT, ::userbase::menu*)
   {
      // do not call Default() for Alt+(-) when in print preview mode
      if (m_lpfnCloseProc != NULL && nChar == (UINT)'-')
         return 0;
      else
         return Default();
   }

   mdi_child_window* mdi_frame_window::MDIGetActive(BOOL* pbMaximized) const
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
      mdi_child_window* pWnd = dynamic_cast < mdi_child_window * > (hWnd);
      ASSERT(pWnd == NULL || base < mdi_child_window>::bases(pWnd));

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


   mdi_child_window* mdi_frame_window::CreateNewChild(::ca::type_info pClass,
         const char * pszMatter, HMENU hMenu /* = NULL */, HACCEL hAccel /* = NULL */)
   {
      ASSERT(pClass);
      mdi_child_window* pFrame = dynamic_cast < mdi_child_window * > (System.alloc(pClass));
      ASSERT_KINDOF(mdi_child_window, pFrame);

      // load the frame
      ::ca::create_context_sp context(get_app());
      stacker < ::user::create_context > cc(context->m_user);
      cc->m_pCurrentFrame = this;

      pFrame->SetHandles(hMenu, hAccel);
      if (!pFrame->LoadFrame(pszMatter, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, context))
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Couldn't load frame ::ca::window.\n");
         delete pFrame;
         return NULL;
      }

      string strFullString, strTitle;
      strFullString = System.matter_as_string(get_app(), pszMatter, "full_string.txt");
      if(!strFullString.is_empty())
         AfxExtractSubString(strTitle, strFullString, ::document_template::docName);

      // redraw the frame and parent
      pFrame->set_title(strTitle);
      pFrame->InitialUpdateFrame(NULL, TRUE);

      return pFrame;
   }

   /////////////////////////////////////////////////////////////////////////////
   // mdi_frame_window Diagnostics

   #ifdef _DEBUG
   void mdi_frame_window::assert_valid() const
   {
      userbase::frame_window::assert_valid();
      ASSERT(m_pguieMdiClient == NULL || m_pguieMdiClient->IsWindow());
      ASSERT(m_hMenuDefault == NULL || ::IsMenu(m_hMenuDefault));
   }

   void mdi_frame_window::dump(dump_context & dumpcontext) const
   {
      userbase::frame_window::dump(dumpcontext);

      dumpcontext << "m_pguieMdiClient = " << (void *)m_pguieMdiClient;
      dumpcontext << "\nm_hMenuDefault = " << (void *)m_hMenuDefault;

      dumpcontext << "\n";
   }
   #endif //_DEBUG


   /////////////////////////////////////////////////////////////////////////////
   // Smarts for the "Window" menu

   HMENU mdi_frame_window::GetWindowMenuPopup(HMENU hMenuBar)
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

   void mdi_frame_window::OnUpdateFrameMenu(HMENU hMenuAlt)
   {
      mdi_child_window* pActiveWnd = MDIGetActive();
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
   mdi_frame_window* mdi_child_window::GetMDIFrame()
   {
      ASSERT_KINDOF(mdi_child_window, this);
      ::user::interaction* hWndMDIClient = GetParent();
      ASSERT(hWndMDIClient != NULL);

      mdi_frame_window* pMDIFrame;
      pMDIFrame = dynamic_cast < mdi_frame_window * > (hWndMDIClient->GetParent());
      ASSERT(pMDIFrame != NULL);
      ASSERT_KINDOF(mdi_frame_window, pMDIFrame);
      ASSERT(pMDIFrame->m_pguieMdiClient == hWndMDIClient);
      ASSERT_VALID(pMDIFrame);
      return pMDIFrame;
   }

   ::user::interaction* mdi_child_window::GetMessageBar()
   {
      // status bar/message bar owned by parent MDI frame
      return GetMDIFrame()->GetMessageBar();
   }

   void mdi_child_window::on_update_frame_title(BOOL bAddToTitle)
   {
      // update our parent ::ca::window first
      GetMDIFrame()->on_update_frame_title(bAddToTitle);

      if ((GetStyle() & FWS_ADDTOTITLE) == 0)
         return;     // leave child ::ca::window alone!

      ::document * pdocument = GetActiveDocument();
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
         SetWindowText(szText);
      }
   }

   void mdi_child_window::OnMDIActivate(BOOL bActivate, ::user::interaction* pActivateWnd, ::user::interaction*)
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
   /*#ifndef _AFX_NO_OLE_SUPPORT
      if (m_pNotifyHook != NULL && m_pNotifyHook->OnDocActivate(bActivate))
         bHooked = TRUE;
   #endif*/

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

   void mdi_child_window::OnUpdateFrameMenu(BOOL bActivate, ::user::interaction* pActivateWnd,
      HMENU hMenuAlt)
   {
      mdi_frame_window* pFrame = GetMDIFrame();

      if (hMenuAlt == NULL && bActivate)
      {
         // attempt to get default menu from ::document
         ::document * pDoc = GetActiveDocument();
         if (pDoc != NULL)
            hMenuAlt = pDoc->GetDefaultMenu();
      }

      // use default menu stored in frame if none from ::document
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

   BOOL mdi_child_window::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
   {
   // trans   if (!userbase::frame_window::OnNcCreate(lpCreateStruct))
         //return FALSE;

      // handle extended styles under Win4
      // call PreCreateWindow again just to get dwExStyle
      VERIFY(PreCreateWindow(*lpCreateStruct));
      SetWindowLong(GWL_EXSTYLE, lpCreateStruct->dwExStyle);

      return TRUE;
   }

   int mdi_child_window::OnCreate(LPCREATESTRUCT lpCreateStruct)
   {
      // call base class with lParam context (not MDI one)
      MDICREATESTRUCT* lpmcs;
      lpmcs = (MDICREATESTRUCT*)lpCreateStruct->lpCreateParams;
      
      ::ca::create_context* pContext = (::ca::create_context*)lpmcs->lParam;

      return OnCreateHelper(lpCreateStruct, pContext);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special UI processing depending on current active child

   void mdi_frame_window::on_update_frame_title(BOOL bAddToTitle)
   {
      if ((GetStyle() & FWS_ADDTOTITLE) == 0)
         return;     // leave it alone!

      /*
   #ifndef _AFX_NO_OLE_SUPPORT
      // allow hook to set the title (used for OLE support)
      if (m_pNotifyHook != NULL && m_pNotifyHook->on_update_frame_title())
         return;
   #endif*/

      mdi_child_window* pActiveChild = NULL;
      ::document * pdocument = GetActiveDocument();
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
   void mdi_frame_window::OnUpdateMDIWindowCmd(cmd_ui * pcmdui)
   {
      ASSERT(m_pguieMdiClient != NULL);
      pcmdui->Enable(MDIGetActive() != NULL);
   }

   BOOL mdi_frame_window::OnMDIWindowCmd(UINT nID)
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

   void mdi_frame_window::OnWindowNew()
   {
      mdi_child_window* pActiveChild = MDIGetActive();
      ::document * pdocument;
      if (pActiveChild == NULL ||
        (pdocument = pActiveChild->GetActiveDocument()) == NULL)
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: No active ::document for WindowNew command.\n");
         //linux System.simple_message_box(AFX_IDP_COMMAND_FAILURE);
         System.simple_message_box(NULL, "Command failure");
         return;     // command failed
      }

      // otherwise we have a new frame !
      ::document_template * ptemplate = pdocument->get_document_template();
      ASSERT_VALID(ptemplate);
      ::ca::create_context_sp cc(get_app());
      ::frame_window* pFrame = ptemplate->create_new_frame(pdocument, pActiveChild, cc);
      if (pFrame == NULL)
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: failed to create new frame.\n");
         return;     // command failed
      }

      ptemplate->InitialUpdateFrame(pFrame, pdocument);
   }

   // frame_window
   void frame_window::DelayUpdateFrameTitle()
      { m_nIdleFlags |= idleTitle; }
   void frame_window::DelayRecalcLayout(BOOL bNotify)
      { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
   void frame_window::AddControlBar(::userbase::control_bar *pBar)
      { m_listControlBars.add_tail(pBar); }


   // MDI functions
   void mdi_frame_window::MDIActivate(::user::interaction* pWndActivate)
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIACTIVATE,
         (WPARAM)pWndActivate, 0); }
   void mdi_frame_window::MDIIconArrange()
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIICONARRANGE, 0, 0); }
   void mdi_frame_window::MDIMaximize(::user::interaction* pWnd)
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIMAXIMIZE, (WPARAM)pWnd, 0); }
   void mdi_frame_window::MDIPrev()
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 1); }
   void mdi_frame_window::MDINext()
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 0); }
   void mdi_frame_window::MDIRestore(::user::interaction* pWnd)
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIRESTORE, (WPARAM)pWnd, 0); }
   void mdi_frame_window::MDITile()
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDITILE, 0, 0); }
   void mdi_frame_window::MDICascade()
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDICASCADE, 0, 0); }

   void mdi_frame_window::MDICascade(int nType)
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDICASCADE, nType, 0); }
   void mdi_frame_window::MDITile(int nType)
      { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDITILE, nType, 0); }



} // namespace userbase