#include "framework.h"
#ifdef WINDOWSEX
#include <dde.h>
#endif





simple_frame_window::simple_frame_window(::ca::application * papp) :
   ca(papp),
   m_dibBk(papp),
   m_fastblur(papp)
{

   m_bblur_Background      = false;
   m_bCustomFrameBefore    = true;
   m_bWindowFrame          = true;
   m_bLayered              = true;
//   m_hdcOpenGL             = NULL;
//   m_hglrc                 = NULL;
   m_pframeschema          = NULL;

}

simple_frame_window::~simple_frame_window()
{
}


// // BEGIN_MESSAGE_MAP(simple_frame_window, userbase::frame_window)
   //{{__MSG_MAP(simple_frame_window)
/* xxx   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_WM_CLOSE()
   ON_WM_NCCALCSIZE()
   ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_STATUS_BAR, OnBarCheck)
   ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_TOOLBAR, OnBarCheck)
   ON_UPDATE_COMMAND_UI(ID_VIEW_REBAR, OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_REBAR, OnBarCheck) */
   //}}__MSG_MAP
// // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// simple_frame_window message handlers

void simple_frame_window::install_message_handling(::gen::message::dispatch * pinterface)
{
   userbase::frame_window::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE         , pinterface, this, &simple_frame_window::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_NCACTIVATE     , pinterface, this, &simple_frame_window::_001OnNcActivate);
#ifdef WINDOWSEX
   IGUI_WIN_MSG_LINK(WM_DDE_INITIATE   , pinterface, this, &simple_frame_window::_001OnDdeInitiate);
#endif
   IGUI_WIN_MSG_LINK(WM_DESTROY        , pinterface, this, &simple_frame_window::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_CLOSE          , pinterface, this, &simple_frame_window::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_SIZE           , pinterface, this, &simple_frame_window::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_MOVE           , pinterface, this, &simple_frame_window::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_SYSCOMMAND     , pinterface, this, &simple_frame_window::_001OnSysCommand);
   IGUI_WIN_MSG_LINK(WM_GETMINMAXINFO  , pinterface, this, &simple_frame_window::_001OnGetMinMaxInfo);
   IGUI_WIN_MSG_LINK(WM_USER + 184     , pinterface, this, &simple_frame_window::_001OnUser184);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE      , pinterface, this, &simple_frame_window::_001OnMouseMove);

   connect_update_cmd_ui("view_full_screen", &simple_frame_window::_001OnUpdateViewFullScreen);
   connect_command("view_full_screen", &simple_frame_window::_001OnViewFullScreen);
   connect_command("app_exit", &simple_frame_window::_001OnClose);
}

bool simple_frame_window::IsFullScreen()
{
   return WfiIsFullScreen();
}

::user::interaction* simple_frame_window::WindowDataGetWnd()
{
   return this;
}




void simple_frame_window::_001OnDestroy(gen::signal_object * pobj)
{
   try
   {
      if(m_papp != NULL && &Application != NULL)
      {
         Application.remove_frame(this);
      }
   }
   catch(...)
   {
   }

   try
   {
      if(&Bergedge != NULL)
      {
         Bergedge.remove_frame(this);
      }
   }
   catch(...)
   {
   }

   try
   {
      if(m_papp != NULL && m_papp->m_psystem != NULL && &System != NULL)
      {
         System.remove_frame(this);
      }
   }
   catch(...)
   {
   }

   pobj->previous();

}


::uinteraction::frame::frame * simple_frame_window::create_frame_schema()
{

   ::uinteraction::frame::frame * pschema = Application.get_frame_schema("app-core/uinteraction", "005");

   pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

   return pschema;

}


void simple_frame_window::_001OnCreate(gen::signal_object * pobj)
{

   SCAST_PTR(::gen::message::create, pcreate, pobj)

   if(pobj->previous())
      return;

   ::user::place_holder * pplaceholder = dynamic_cast < ::user::place_holder * > (get_parent());

   if(pplaceholder != NULL)
   {
      ::user::place_holder_container * pcontainer = dynamic_cast < ::user::place_holder_container * > (pplaceholder->get_parent());
      if(pcontainer != NULL)
      {
         pcontainer->on_hold(this, pplaceholder);
      }
   }

   if(m_bAutoWindowFrame)
   {
      m_bWindowFrame = get_parent() == NULL;
   }

   if(m_bWindowFrame)
   {
      /*WNDCLASS wndclass;

      char szBuf [64];
      ::GetClassName(get_handle(), szBuf, _countof(szBuf));

      GetClassInfo(System.m_hInstance,
         szBuf,
         &wndclass);*/

// trans      SetIcon(wndclass.hIcon, false);

// trans      HICON hicon = GetIcon(false);

      ::uinteraction::frame::frame * pinteractionframe = create_frame_schema();


      //frame::FrameSchema * pschema = dynamic_cast < ::frame::FrameSchema * > (pinteractionframe);

      if(pinteractionframe != NULL && (_ca_is_basis() || Application.command().m_varTopicQuery["version"] == "basis"))
      {

         pinteractionframe->set_style("BlueRedPurple");

      }

      /*{
         frame::FrameSchemaHardCoded001 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded001 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command().m_varTopicQuery["version"] == "basis"))
         {
            pschemaSpec->SetStyle(frame::FrameSchemaHardCoded001::StyleBlueRedPurple);
         }
      }
      {
         frame::FrameSchemaHardCoded002 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded002 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command().m_varTopicQuery["version"] == "basis"))
         {
            pschemaSpec->SetStyle(frame::FrameSchemaHardCoded002::StyleBlueRedPurple);
         }
      }
      {
         frame::FrameSchemaHardCoded005 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded005 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command().m_varTopicQuery["version"] == "basis"))
         {
            pschemaSpec->SetStyle(frame::FrameSchemaHardCoded005::StyleBlueRedPurple);
         }
      }
      {
         frame::FrameSchemaHardCoded008 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded008 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command().m_varTopicQuery["version"] == "basis"))
         {
            pschemaSpec->SetStyle(frame::FrameSchemaHardCoded008::StyleBlueRedPurple);
         }
      }*/

      m_pframeschema = pinteractionframe;
      m_workset.AttachFrameSchema(m_pframeschema);
      if(!m_workset.update(
         this,
         this,
         this,
         this))
      {
         pcreate->m_bRet = false;
         return;
      }

#ifdef LINUX

   m_workset.SetActiveFlag(TRUE);

#endif


   }

   defer_synch_layered();



   pcreate->m_bRet = false;

}

void simple_frame_window::_001OnSize(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if((m_workset.GetMovingManager() == NULL ||
      m_workset.GetSizingManager() == NULL) || (!m_workset.GetMovingManager()->IsMoving()
   && !m_workset.GetSizingManager()->IsSizing()))
   {
      _001RedrawWindow();
   }

   if(dynamic_cast < simple_child_frame * > (this) == NULL)
   {
      WindowDataSaveWindowRect();
   }

}

void simple_frame_window::_001OnMove(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if((m_workset.GetMovingManager() == NULL ||
      m_workset.GetSizingManager() == NULL) || (!m_workset.GetMovingManager()->IsMoving()
   && !m_workset.GetSizingManager()->IsSizing()))
   {
      _001RedrawWindow();
   }

   if(dynamic_cast < simple_child_frame * > (this) == NULL)
   {
      WindowDataSaveWindowRect();
   }

}

bool simple_frame_window::OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext)
{
// trans   HICON hicon = GetIcon(false);
   return userbase::frame_window::OnCreateClient(lpcs, pContext);
}

bool simple_frame_window::pre_create_window(CREATESTRUCT& cs)
{

#ifdef WINDOWSEX
   if(cs.lpszClass == NULL)
   {
      cs.lpszClass = System.RegisterWndClass(CS_HREDRAW | CS_VREDRAW, 0, 0, 0);
   }
#endif

   if(!userbase::frame_window::pre_create_window(cs))
      return FALSE;

#ifdef WINDOWSEX
   if(cs.hMenu != NULL)
   {
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;
   }
#endif

   //cs.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
   cs.style = WS_POPUP;

   return TRUE;
}

void simple_frame_window::layout()
{
   if(m_bWindowFrame && m_workset.IsAppearanceEnabled() && !WfiIsFullScreen())
   {
      m_workset.layout();
   }
   else
   {
      userbase::frame_window::layout();
   }
}

void simple_frame_window::ViewOnActivateFrame(::userbase::view * pview, UINT user, ::user::interaction * pframe)
{
   UNREFERENCED_PARAMETER(pview);
   UNREFERENCED_PARAMETER(user);
   UNREFERENCED_PARAMETER(pframe);
//   if(pview != NULL)
//      pview->OnActivateFrame(WA_INACTIVE, (userbase::frame_window *) pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(gen::signal_object * pobj)
{
#ifdef WINDOWSEX
   SCAST_PTR(gen::message::base, pbase, pobj);
   MINMAXINFO FAR * lpMMI = (MINMAXINFO FAR*) pbase->m_lparam;
   if (IsFullScreen())
   {
      lpMMI->ptMaxSize.y = m_FullScreenWindowRect.height();
      lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
      lpMMI->ptMaxSize.x = m_FullScreenWindowRect.width();
      lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
   }
#else
   throw todo(get_app());
#endif
}

   void simple_frame_window::ShowControlBars(bool bShow)
   {
      UINT nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

   /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
   //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/


      POSITION pos = m_toolbarmap.m_keymap.get_start_position();

      id idKey;
      ::user::interaction * pbar;
      while(pos != NULL)
      {
          m_toolbarmap.m_keymap.get_next_assoc(pos, idKey, pbar);
          try
          {
             pbar->ShowWindow(nShow);
          }
          catch(...)
          {
          }
      }

      layout();

   }

void simple_frame_window::WfiOnFullScreen(bool bFullScreen)
{
   /*oswindow oswindowTrayWindow = NULL;
   if(get_parent() == NULL)
   {
      oswindowTrayWindow = FindWindowA("Shell_traywnd", "");
   }*/
   if(bFullScreen)
   {

      ShowControlBars(false);

  //    uint32_t dwStyle = GetStyle();

//      uint32_t dwStyleEx = GetExStyle();

      rect rectDesktop;

      if(get_parent() != NULL)
      {
         get_parent()->GetClientRect(rectDesktop);
      }
      else
      {
         System.get_screen_rect(rectDesktop);
         /*::AdjustWindowRectEx(
            &rectDesktop,
            dwStyle,
            FALSE,
            dwStyleEx);*/
      }

      m_FullScreenWindowRect = rectDesktop;

      //if(get_parent() == NULL)
      {
         SetWindowPos(
            ZORDER_TOP,
            rectDesktop.left, rectDesktop.top,
            rectDesktop.width(), rectDesktop.height(),
            SWP_FRAMECHANGED |
            SWP_SHOWWINDOW);

         //::SetWindowPos(oswindowTrayWindow, 0, 0, 0, 0, 0, SWP_HIDEWINDOW);
      }
   }
   else
   {
      ShowControlBars(true);
   }
}


void simple_frame_window::_001OnViewFullScreen(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ToggleFullScreen();
}

void simple_frame_window::_001OnMouseMove(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::gen::message::mouse, pmouse, pobj)
}

void simple_frame_window::_001OnUpdateViewFullScreen(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable();
   pcmdui->m_pcmdui->_001SetCheck(WfiIsFullScreen());
   pcmdui->m_bRet = true;
}

void simple_frame_window::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

bool simple_frame_window::_001CanEnterScreenSaver()
{
   return true;
}

void simple_frame_window::_001OnSysCommand(gen::signal_object * pobj)
{
   SCAST_PTR(gen::message::base, pbase, pobj);

   if(pbase->m_wparam == SC_SCREENSAVE)
   {
      if(!_001CanEnterScreenSaver())
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
         return;
      }
   }

   if(m_bWindowFrame)
   {
      if(pbase->m_wparam == SC_MAXIMIZE)
      {
         WfiMaximize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if(pbase->m_wparam == SC_RESTORE)
      {
         WfiRestore();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if(pbase->m_wparam == SC_MINIMIZE)
      {
         WfiMinimize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }

}


void simple_frame_window::_001OnToggleCustomFrame(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   SetCustomFrame(!GetCustomFrame());
}

void simple_frame_window::_001OnUpdateToggleCustomFrame(gen::signal_object * pobj)
{
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable();
   pcmdui->m_pcmdui->_001SetCheck(m_bWindowFrame);
}



void simple_frame_window::ActivateFrame(int32_t nCmdShow)
{

   userbase::frame_window::ActivateFrame(nCmdShow);
}

void simple_frame_window::GetBorderRect(LPRECT lprect)
{
   *lprect = m_rectBorder;
}

void simple_frame_window::SetBorderRect(LPCRECT lpcrect)
{
   m_rectBorder = *lpcrect;
}

void simple_frame_window::SetCustomFrame(bool bCustom)
{
   m_bWindowFrame = bCustom;
   m_workset.Enable(bCustom);
   layout();
   _001RedrawWindow();

}

bool simple_frame_window::GetCustomFrame()
{
   return m_bWindowFrame;
}

void simple_frame_window::_001OnClose(gen::signal_object * pobj)
{
   if(m_iModalCount > 0)
   {
      EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }
   else if(GetTopLevelFrame() != NULL
   && (GetTopLevelFrame()->m_iModalCount > 0))
   {
      GetTopLevelFrame()->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }
   else if(m_pimpl->m_iModalCount > 0)
   {
      m_pimpl->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
      return;
   }
   else if(GetTopLevelFrame() != NULL
   && GetTopLevelFrame()->m_pimpl != NULL
   && (GetTopLevelFrame()->m_pimpl->m_iModalCount > 0))
   {
      GetTopLevelFrame()->m_pimpl->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }

   if(get_wnd() != NULL
   && get_wnd()->m_iModalCount > 0)
   {
      get_wnd()->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }

   pobj->m_bRet = true;
   // Note: only queries the active document
   ::user::document_interface * pdocument = GetActiveDocument();
   if (pdocument != NULL && !pdocument->can_close_frame(this))
   {
      // document can't close right now -- don't close it
      return;
   }

   ::cube8::application * papp = &Application;

   if(papp->is_cube() || papp->is_bergedge() || papp->is_session() || papp->is_system())
   {

      // TODO: instead of closing all applications in process System.m_apptra, should close application that make part of
      // cube, bergedge, session or system.

      for(int32_t i = 0; Sys(papp).m_appptra.get_count(); i++)
      {

         ::cube8::application * pappChild = &App(Sys(papp).m_appptra[i]);

         if(!pappChild->_001CloseApplicationByUser(this))
            return;

      }

   }
   else if(papp->GetVisibleTopLevelFrameCountExcept(this) <= 0)
   {

      if(!papp->_001CloseApplicationByUser(this))
         return;

   }
   else
   {
      DestroyWindow();
   }

}

#ifdef WINDOWSEX

void simple_frame_window::OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
   UNREFERENCED_PARAMETER(bCalcValidRects);
   if(m_workset.IsEnabled() && m_workset.m_pframeschema != NULL)
   {
      m_workset.OnNcCalcSize(&lpncsp->rgrc[0]);
   }
   else
   {
// trans      userbase::frame_window::OnNcCalcSize(bCalcValidRects, lpncsp);
   }

}

#endif

void simple_frame_window::_001OnNcActivate(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::nc_activate, pncactivate, pobj)
   // stay active if WF_STAYACTIVE bit is on
   if (m_nFlags & WF_STAYACTIVE)
      pncactivate->m_bActive = TRUE;

   // but do not stay active if the ::ca::window is disabled
   if (!IsWindowEnabled())
      pncactivate->m_bActive = FALSE;

   /*if(m_bWindowFrame)
   {
      m_workset.SetActiveFlag(pncactivate->m_bActive);
      pncactivate->set_lresult(TRUE); // bStop
      pncactivate->m_bRet = true;
      return;
   }
   else*/
   {
      // do not call the base class because it will call Default()
      //  and we may have changed bActive.
      pncactivate->set_lresult(DefWindowProc(WM_NCACTIVATE, pncactivate->m_bActive, 0L)); // bStop
      pncactivate->m_bRet = pncactivate->get_lresult() != 0;
      return;
   }
}



bool simple_frame_window::LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle, ::user::interaction* pParentWnd, ::ca::create_context* pContext)
{

   UNREFERENCED_PARAMETER(pParentWnd);

   Application.defer_initialize_twf();

   // only do this once
//   ASSERT_VALID_IDR(nIDResource);
//   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

//   string strFullString;
//   if (strFullString.load_string(nIDResource))
//      __extract_sub_string(m_strTitle, strFullString, 0);    // first sub-string

#ifdef WINDOWSEX
   VERIFY(System.DeferRegisterClass(__WNDFRAMEORVIEW_REG, NULL));
#endif

   // attempt to create the ::ca::window
   const char * lpszClass = (const char *) GetIconWndClass(dwDefaultStyle, pszMatter);
   const char * lpszTitle = m_strTitle;

   if(pParentWnd == NULL)
      pParentWnd = Application.get_request_parent_ui(this, pContext);

   if (!CreateEx(0L, lpszClass, lpszTitle, dwDefaultStyle, rect(0, 0, 0, 0), pParentWnd, /*nIDResource*/ 0, pContext))
   {
      return FALSE;   // will self destruct on failure normally
   }

/* trans   // save the default menu handle
   ASSERT(get_handle() != NULL);
   m_hMenuDefault = ::GetMenu(get_handle()); */

   // load accelerator resource
//   LoadAccelTable(MAKEINTRESOURCE(nIDResource));

   if (pContext == NULL)   // send initial update
      SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

   return TRUE;
}

/*bool simple_frame_window::create(const char * lpszClassName,
   const char * lpszWindowName,
   uint32_t dwStyle,
   const RECT& rect,
   ::user::interaction* pParentWnd,
   const char * lpszMenuName,
   uint32_t dwExStyle,
   create_context* pContext)
{
   HMENU hMenu = NULL;
   if (lpszMenuName != NULL)
   {
      // load in a menu that will get destroyed when ::ca::window gets destroyed
      HINSTANCE hInst = gen::FindResourceHandle(lpszMenuName, RT_MENU);
      if ((hMenu = ::LoadMenu(hInst, lpszMenuName)) == NULL)
      {
         TRACE0("Warning: failed to load menu for userbase::frame_window.\n");
         PostNcDestroy();            // perhaps delete the C++ object
         return FALSE;
      }
   }

   m_strTitle = lpszWindowName;    // save title for later

   if (!CreateExW(dwExStyle, (const wchar_t *) lpszClassName, (const wchar_t *) lpszWindowName, dwStyle,
      rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
      pParentWnd->GetSafeoswindow_(), hMenu, (LPVOID)pContext))
   {
      TRACE0("Warning: failed to create userbase::frame_window.\n");
      if (hMenu != NULL)
         DestroyMenu(hMenu);
      return FALSE;
   }

   return TRUE;
}*/


static const char gen_OldWndProc[] = "gen::OldWndProc423";



void simple_frame_window::_001OnDdeInitiate(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::base, pbase, pobj)
   pbase->set_lresult(DefWindowProc((uint32_t) pbase->m_wparam, pbase->m_lparam, pbase->get_lresult()));
}


void simple_frame_window::pre_translate_message(gen::signal_object * pobj)
{
#ifdef WINDOWSEX
   SCAST_PTR(gen::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_KEYUP)
   {
      if(pbase->m_wparam == VK_RETURN)
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000
         && ::GetKeyState(VK_MENU) & 0x80000000)
         {
            if(DeferFullScreen(true, false))
            {
               g_bFullScreenAlt = false;
               pbase->m_bRet = true;
               return;
            }
         }
      }
      else if(pbase->m_wparam == VK_MENU)
      {
         if(g_bFullScreenAlt)
         {
            g_bFullScreenAlt = false;
            if(DeferFullScreen(false, true))
            {
               pbase->m_bRet = true;
               return;
            }
         }
      }
   }
   else if(pbase->m_uiMessage == WM_KEYDOWN)
   {
      if(pbase->m_wparam == VK_MENU)
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000)
         {
            g_bFullScreenAlt = true;
         }
      }
   }
#else
   //throw todo(get_app());
#endif
   return userbase::frame_window::pre_translate_message(pobj);
}







void simple_frame_window::InitialFramePosition(bool bForceRestore)
{
   if(m_bFrameMoveEnable)
   {
      WindowDataLoadWindowRect(bForceRestore);
      WindowDataEnableSaveWindowRect(true);
   }
   userbase::frame_window::InitialFramePosition(bForceRestore);
   if(m_workset.GetAppearance() != NULL && m_workset.GetAppearanceMode() == ::uinteraction::frame::AppearanceModeIconic)
   {
      WfiRestore();
   }
}

void simple_frame_window::_001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc)
{
   if(System.savings().is_trying_to_save(gen::resource_processing)
   || System.savings().is_trying_to_save(gen::resource_translucent_background))
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(0, 0, 0));
   }
   else
   {

      userbase::frame_window::_001OnDeferPaintLayeredWindowBackground(pdc);
   }
}

void simple_frame_window::_000OnDraw(::ca::graphics * pdc)
{
   if(!m_bVisible)
      return;
#ifndef LINUX
   if(m_bblur_Background)
   {
      _001DrawThis(pdc);
      _001DrawChildren(pdc);
   }
   else
#endif
   if(!Session.savings().is_trying_to_save(gen::resource_processing)
   && !Session.savings().is_trying_to_save(gen::resource_display_bandwidth)
   && !Session.savings().is_trying_to_save(gen::resource_memory))
   //&& (get_parent() != NULL || (this->GetExStyle() & WS_EX_LAYERED) != 0))
   {
      userbase::frame_window::_000OnDraw(pdc);
   }
   else
   {
      _001DrawThis(pdc);
      _001DrawChildren(pdc);
   }
}


void simple_frame_window::_001OnDraw(::ca::graphics * pdc)
{
   #ifndef LINUX
   if(m_bblur_Background)
   {
      class imaging & imaging = Application.m_visual.imaging();
      rect rectClient;
      GetClientRect(rectClient);
      //rectClient.offset(rectClient.top_left());
      if(System.savings().is_trying_to_save(gen::resource_translucent_background))
      {
         //pdc->FillSolidRect(rectClient, RGB(150, 220, 140));
      }
      else if(System.savings().is_trying_to_save(gen::resource_processing)
      || System.savings().is_trying_to_save(gen::resource_blur_background))
      {
         imaging.color_blend(pdc, rectClient, RGB(150, 180, 140), 150);
      }
      else
      {
         if(rectClient.size() != m_dibBk->size())
         {
            m_dibBk->create(rectClient.size());
            m_dibBk->Fill(0, 184, 184, 170);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::visual::fastblur *( *pfnNew )(::ca::application *) = (::visual::fastblur *(*)(::ca::application *)) ::GetProcAddress(hmodule, "new_fastblur");
            m_fastblur.create(get_app());
            m_fastblur.initialize(rectClient.size(), 2);
         }
         if(m_fastblur.is_set() && m_fastblur->area() > 0)
         {
            m_fastblur->get_graphics()->BitBlt(0, 0, rectClient.width(), rectClient.height(), pdc, 0, 0, SRCCOPY);
            m_fastblur.blur();
            imaging.bitmap_blend(
               m_fastblur->get_graphics(),
               null_point(),
               rectClient.size(),
               m_dibBk->get_graphics(),
               null_point(),
               49);
            pdc->from(rectClient.size(),
               m_fastblur->get_graphics(),
               null_point(),
               SRCCOPY);
         }
      }
      pdc->SelectClipRgn(NULL);
   }
   #endif
   userbase::frame_window::_001OnDraw(pdc);
}


void simple_frame_window::on_set_parent(::user::interaction* pguieParent)
{
   userbase::frame_window::on_set_parent(pguieParent);
   if(m_pupdowntarget != NULL && m_pupdowntarget->is_up_down_target())
   {
      // an updowntarget always show the frame for upping/downing
      if(!m_bWindowFrame)
      {
         m_bWindowFrame = m_bCustomFrameBefore;
      }
      if(!m_workset.IsEnabled())
      {
         m_workset.Enable(true);
         layout();
      }
   }
   else
   {
      if(pguieParent != NULL)
      {
         m_bCustomFrameBefore = m_bWindowFrame;
         m_bWindowFrame = false;
         m_workset.Enable(false);
         layout();
      }
      else
      {
         m_bWindowFrame = m_bCustomFrameBefore;
         m_workset.Enable(m_bWindowFrame);
         layout();
      }
   }
}

void simple_frame_window::GetClientRect(LPRECT lprect)
{
   if(m_bWindowFrame && m_pframeschema != NULL && !WfiIsFullScreen())
   {
      m_pframeschema->GetWndClientRect(lprect);
   }
   else
   {
      userbase::frame_window::GetClientRect(lprect);
   }
}


bool simple_frame_window::is_application_main_window()
{
   return Application.GetMainWnd() == this;
}


void simple_frame_window::LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle, uint32_t dwStyle)
{
   ::user::interaction * pui = m_toolbarmap[idToolBar];
   simple_toolbar * ptoolbar;
   if(pui != NULL)
   {
      ptoolbar = dynamic_cast < simple_toolbar * > (pui);
   }
   else
   {
      ptoolbar = new simple_toolbar(get_app());
      ptoolbar->CreateEx(this, dwCtrlStyle, dwStyle);
      pui = ptoolbar;
      m_toolbarmap.set_at(idToolBar, pui);
   }
   if(ptoolbar != NULL)
   {
      ptoolbar->LoadXmlToolBar(Application.file().as_string(Application.dir().matter(pszToolBar)));
      layout();
   }
}


void simple_frame_window::_001OnUser184(gen::signal_object * pobj)
{
   SCAST_PTR(gen::message::base, pbase, pobj);
   if(pbase->m_wparam == 0 &&
      pbase->m_lparam == 0)
   {
      InitialFramePosition(true);
      pbase->m_bRet = true;
   }
}

// persistent frame implemenation using updowntarget
bool simple_frame_window::WndFrameworkDownUpGetUpEnable()
{
   return
      m_pupdowntarget != NULL
   && m_pupdowntarget->is_up_down_target()
   && m_pupdowntarget->up_down_target_is_down();
}

bool simple_frame_window::WndFrameworkDownUpGetDownEnable()
{
   return
      m_pupdowntarget != NULL
   && m_pupdowntarget->is_up_down_target()
   && m_pupdowntarget->up_down_target_is_up();
}

void simple_frame_window::WfiOnDown()
{
   frame_Attach();
}

void simple_frame_window::WfiOnUp()
{
   frame_Detach();
}


bool simple_frame_window::create(const char * lpszClassName,
         const char * lpszWindowName,
         uint32_t dwStyle,
         const RECT& rect,
         ::user::interaction* pParentWnd,        // != NULL for popups
         const char * lpszMenuName,
         uint32_t dwExStyle,
         ::ca::create_context* pContext)
{
   return ::userbase::frame_window::create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, lpszMenuName, dwExStyle, pContext);
}





