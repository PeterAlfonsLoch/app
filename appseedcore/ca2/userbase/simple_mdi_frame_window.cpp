#include "StdAfx.h"

/////////////////////////////////////////////////////////////////////////////
// SimpleMDIFrameWindow

/*
 // BEGIN_MESSAGE_MAP(SimpleMDIFrameWindow, frame_window)
   //{{AFX_MSG_MAP(SimpleMDIFrameWindow)
    xxx ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, SimpleMDIFrameWindow::OnIdleUpdateCmdUI)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, &SimpleMDIFrameWindow::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, &SimpleMDIFrameWindow::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, &SimpleMDIFrameWindow::OnUpdateMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_VERT, &SimpleMDIFrameWindow::OnUpdateMDIWindowCmd)
   ON_WM_SIZE()
   ON_COMMAND_EX(ID_WINDOW_ARRANGE, &SimpleMDIFrameWindow::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_CASCADE, &SimpleMDIFrameWindow::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_TILE_HORZ, &SimpleMDIFrameWindow::OnMDIWindowCmd)
   ON_COMMAND_EX(ID_WINDOW_TILE_VERT, &SimpleMDIFrameWindow::OnMDIWindowCmd)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, &SimpleMDIFrameWindow::OnUpdateMDIWindowCmd)
   ON_COMMAND(ID_WINDOW_NEW, &SimpleMDIFrameWindow::OnWindowNew)
   ON_WM_DESTROY()
   ON_MESSAGE(WM_COMMANDHELP, &SimpleMDIFrameWindow::OnCommandHelp)
   ON_WM_MENUCHAR() 
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()
*/

SimpleMDIFrameWindow::SimpleMDIFrameWindow(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp)
{
   m_pguieMdiClient = NULL;
}

BOOL SimpleMDIFrameWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   // send to MDI child first - will be re-sent through _001OnCommand later
   //SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
/*   if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
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

bool SimpleMDIFrameWindow::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   
{
   SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
   // pump through active child FIRST
   if (pActiveChild != NULL)
   {
//      push_routing_frame push(this);
      if (pActiveChild->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }

   // then pump through normal frame
   return frame_window::_001OnCmdMsg(pcmdmsg);
}

LRESULT SimpleMDIFrameWindow::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   if (lParam == 0 && IsTracking())
      lParam = HID_BASE_COMMAND+m_nIDTracking;

//   SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
/*   if (pActiveChild != NULL && AfxCallWndProc(pActiveChild,
     pActiveChild->_get_handle(), WM_COMMANDHELP, wParam, lParam) != 0)
   {
      // handled by child
      return TRUE;
   }*/

/*   if (frame_window::OnCommandHelp(wParam, lParam))
   {
      // handled by our base
      return TRUE;
   }*/

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

BOOL SimpleMDIFrameWindow::OnCreateClient(LPCREATESTRUCT lpcs, create_context*)
{

   return CreateClient(lpcs, NULL);
}

BOOL SimpleMDIFrameWindow::CreateClient(LPCREATESTRUCT lpCreateStruct,
   ::userbase::menu* pWindowMenu)
{
   UNREFERENCED_PARAMETER(pWindowMenu);
   ASSERT(_get_handle() != NULL);
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
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: SimpleMDIFrameWindow::OnCreateClient: failed to create MDICLIENT."
         " GetLastError returns 0x%8.8X\n", ::GetLastError());
      return FALSE;
   }
   // Move it to the top of z-order
   m_pguieMdiClient->BringWindowToTop();

   return TRUE;
}

LRESULT SimpleMDIFrameWindow::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nMsg);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
// trans   return ::DefFrameProc(_get_handle(), m_pguieMdiClient, nMsg, wParam, lParam);
   return 0;
}

void SimpleMDIFrameWindow::pre_translate_message(gen::signal_object * pobj)
{
   // check for special cancel modes for ComboBoxes
   //if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN)
   //   AfxCancelModes(pMsg->hwnd);    // filter clicks

   // allow tooltip messages to be filtered
   ::user::interaction::pre_translate_message(pobj);
   if(pobj->m_bRet)
      return;

   /*
#ifndef _AFX_NO_OLE_SUPPORT
   // allow hook to consume message
   if (m_pNotifyHook != NULL && m_pNotifyHook->OnPreTranslateMessage(pMsg))
      return TRUE;
#endif
*/
   SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());

   // current active child gets first crack at it
   if(pActiveChild != NULL)
   {
      pActiveChild->pre_translate_message(pobj);
      if(pobj->m_bRet)
         return;
   }

   SCAST_PTR(user::win::message::base, pbase, pobj);

   if(pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
   {
      // translate accelerators for frame and any children
   /* linux   if (m_hAccelTable != NULL &&
         ::TranslateAccelerator(_get_handle(), m_hAccelTable, pMsg))
      {
         return TRUE;
      } */

      // special processing for MDI accelerators last
      // and only if it is not in SDI mode (print preview)
/* trans      if (GetActiveView() == NULL)
      {
         if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
         {
            // the MDICLIENT ::ca::window may translate it
            if (::TranslateMDISysAccel(m_pguieMdiClient, pMsg))
               return TRUE;
         }
      }*/
   }
}

void SimpleMDIFrameWindow::DelayUpdateFrameMenu(HMENU hMenuAlt)
{
   OnUpdateFrameMenu(hMenuAlt);

   m_nIdleFlags |= idleMenu;
}

void SimpleMDIFrameWindow::OnIdleUpdateCmdUI()
{
   if (m_nIdleFlags & idleMenu)
   {
      m_nIdleFlags &= ~idleMenu;
   }
   frame_window::OnIdleUpdateCmdUI();
}

/*frame_window * SimpleMDIFrameWindow::GetActiveFrame()
{
   SimpleMDIChildWindow* pActiveChild = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
   if (pActiveChild == NULL)
      return this;
   return pActiveChild;
}*/

BOOL SimpleMDIFrameWindow::PreCreateWindow(CREATESTRUCT& cs)
{
   if (cs.lpszClass == NULL)
   {
      VERIFY(System.DeferRegisterClass(AFX_WNDMDIFRAME_REG, &cs.lpszClass));
   }
   return TRUE;
}

BOOL SimpleMDIFrameWindow::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
   ::user::interaction* pParentWnd, create_context* pContext)
{
   if (!frame_window::LoadFrame(pszMatter, dwDefaultStyle,
     pParentWnd, pContext))
      return FALSE;

   // save menu to use when no active MDI child ::ca::window is present
   ASSERT(_get_handle() != NULL);
   m_hMenuDefault = ::GetMenu(_get_handle());
   if (m_hMenuDefault == NULL)
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: SimpleMDIFrameWindow without a default menu.\n");
   return TRUE;
}

void SimpleMDIFrameWindow::_001OnDestroy(gen::signal_object * pobj)
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

void SimpleMDIFrameWindow::OnSize(UINT nType, int, int)
{
   // do not call default - it will reposition the MDICLIENT
   if (nType != SIZE_MINIMIZED)
      layout();
}

LRESULT SimpleMDIFrameWindow::OnMenuChar(UINT nChar, UINT, ::userbase::menu*)
{
   // do not call Default() for Alt+(-) when in print preview mode
   if (m_lpfnCloseProc != NULL && nChar == (UINT)'-')
      return 0;
   else
      return Default();
}

SimpleMDIChildWindow * SimpleMDIFrameWindow::MDIGetActive(BOOL* pbMaximized) const
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
   SimpleMDIChildWindow* pWnd = dynamic_cast < SimpleMDIChildWindow * > (hWnd);
   ASSERT(pWnd == NULL || base < SimpleMDIChildWindow > ::bases(pWnd));

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


SimpleMDIChildWindow* SimpleMDIFrameWindow::CreateNewChild(::ca::type_info pClass,
      const char * pszMatter, HMENU hMenu /* = NULL */, HACCEL hAccel /* = NULL */)
{
   ASSERT(pClass);
   SimpleMDIChildWindow* pFrame = dynamic_cast < SimpleMDIChildWindow* > (System.alloc(pClass));
   ASSERT_KINDOF(SimpleMDIChildWindow, pFrame);

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
   strFullString = System.matter_as_string(get_app(), pszMatter, "full_string.txt");
   if(!strFullString.is_empty())
      AfxExtractSubString(strTitle, strFullString, document_template::docName);

   // redraw the frame and parent
   pFrame->set_title(strTitle);
   pFrame->InitialUpdateFrame(NULL, TRUE);

   return pFrame;
}

/////////////////////////////////////////////////////////////////////////////
// SimpleMDIFrameWindow Diagnostics

#ifdef _DEBUG
void SimpleMDIFrameWindow::assert_valid() const
{
   frame_window::assert_valid();
   ASSERT(m_pguieMdiClient == NULL || m_pguieMdiClient->IsWindow());
   ASSERT(m_hMenuDefault == NULL || ::IsMenu(m_hMenuDefault));
}

void SimpleMDIFrameWindow::dump(dump_context & dumpcontext) const
{
   frame_window::dump(dumpcontext);

   dumpcontext << "m_pguieMdiClient = " << (void *)m_pguieMdiClient;
   dumpcontext << "\nm_hMenuDefault = " << (void *)m_hMenuDefault;

   dumpcontext << "\n";
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// Smarts for the "Window" menu

HMENU SimpleMDIFrameWindow::GetWindowMenuPopup(HMENU hMenuBar)
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

void SimpleMDIFrameWindow::OnUpdateFrameMenu(HMENU hMenuAlt)
{
   SimpleMDIChildWindow* pActiveWnd = dynamic_cast < SimpleMDIChildWindow* > (MDIGetActive());
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
SimpleMDIFrameWindow* SimpleMDIChildWindow::GetMDIFrame()
{
   ASSERT_KINDOF(SimpleMDIChildWindow, this);
// trans   ASSERT(get_handle() != NULL);
   ::user::interaction* hWndMDIClient = GetParent();
   ASSERT(hWndMDIClient != NULL);

   SimpleMDIFrameWindow* pMDIFrame;
   pMDIFrame = dynamic_cast < SimpleMDIFrameWindow * > (hWndMDIClient->GetParent());
   ASSERT(pMDIFrame != NULL);
   ASSERT_KINDOF(SimpleMDIFrameWindow, pMDIFrame);
   ASSERT(pMDIFrame->m_pguieMdiClient == hWndMDIClient);
   ASSERT_VALID(pMDIFrame);
   return pMDIFrame;
}


// MDI functions
void SimpleMDIFrameWindow::MDIActivate(::user::interaction* pWndActivate)
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIACTIVATE,
      (WPARAM)pWndActivate, 0); }
void SimpleMDIFrameWindow::MDIIconArrange()
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIICONARRANGE, 0, 0); }
void SimpleMDIFrameWindow::MDIMaximize(::user::interaction* pWnd)
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIMAXIMIZE, (WPARAM)pWnd, 0); }
void SimpleMDIFrameWindow::MDIPrev()
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 1); }
void SimpleMDIFrameWindow::MDINext()
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDINEXT, 0, 0); }
void SimpleMDIFrameWindow::MDIRestore(::user::interaction* pWnd)
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDIRESTORE, (WPARAM)pWnd, 0); }
void SimpleMDIFrameWindow::MDITile()
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDITILE, 0, 0); }
void SimpleMDIFrameWindow::MDICascade()
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDICASCADE, 0, 0); }

void SimpleMDIFrameWindow::MDICascade(int nType)
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDICASCADE, nType, 0); }
void SimpleMDIFrameWindow::MDITile(int nType)
   { ASSERT(IsWindow()); m_pguieMdiClient->SendMessage(WM_MDITILE, nType, 0); }
