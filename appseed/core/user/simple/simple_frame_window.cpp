#include "framework.h"
#ifdef WINDOWSEX
#include <dde.h>
#endif

#define TEST 0


simple_frame_window::simple_frame_window(sp(::base::application) papp) :
element(papp),
m_dibBk(allocer()),
m_fastblur(allocer())
{

   m_bblur_Background = false;
   m_bCustomFrameBefore = true;
   m_bWindowFrame = true;
   m_bLayered = true;
   m_pframeschema = NULL;

}

simple_frame_window::~simple_frame_window()
{
}

void simple_frame_window::assert_valid() const
{

   ::user::frame_window::assert_valid();

}

void simple_frame_window::dump(dump_context & dumpcontext) const
{

   ::user::frame_window::dump(dumpcontext);

}

// // BEGIN_MESSAGE_MAP(simple_frame_window, ::user::frame_window)
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

void simple_frame_window::install_message_handling(::message::dispatch * pinterface)
{
   ::user::frame_window::install_message_handling(pinterface);
   ::database::user::interaction::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_frame_window::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_NCACTIVATE, pinterface, this, &simple_frame_window::_001OnNcActivate);
#ifdef WINDOWSEX
   IGUI_WIN_MSG_LINK(WM_DDE_INITIATE   , pinterface, this, &simple_frame_window::_001OnDdeInitiate);
#endif
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &simple_frame_window::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &simple_frame_window::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &simple_frame_window::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &simple_frame_window::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_SYSCOMMAND, pinterface, this, &simple_frame_window::_001OnSysCommand);
   IGUI_WIN_MSG_LINK(WM_GETMINMAXINFO, pinterface, this, &simple_frame_window::_001OnGetMinMaxInfo);
   IGUI_WIN_MSG_LINK(WM_USER + 184, pinterface, this, &simple_frame_window::_001OnUser184);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &simple_frame_window::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_DISPLAYCHANGE, pinterface, this, &simple_frame_window::_001OnDisplayChange);

   connect_update_cmd_ui("view_full_screen", &simple_frame_window::_001OnUpdateViewFullScreen);
   connect_command("view_full_screen", &simple_frame_window::_001OnViewFullScreen);
   connect_command("app_exit", &simple_frame_window::_001OnClose);
}




bool simple_frame_window::IsFullScreen()
{
   return WfiIsFullScreen();
}

sp(::user::interaction) simple_frame_window::WindowDataGetWnd()
{
   return this;
}




void simple_frame_window::_001OnDestroy(signal_details * pobj)
{
   try
   {
      if (m_pbaseapp != NULL && &Application != NULL)
      {
         Application.remove_frame(this);
      }
   }
   catch (...)
   {
   }

   try
   {
      if (&session() != NULL)
      {
         session().remove_frame(this);
      }
   }
   catch (...)
   {
   }

   try
   {
      if (m_pbaseapp != NULL && m_pbaseapp->m_pcoresystem != NULL && &System != NULL)
      {
         System.remove_frame(this);
      }
   }
   catch (...)
   {
   }

   pobj->previous();

}


sp(::user::uinteraction::frame::frame) simple_frame_window::create_frame_schema()
{

   sp(::user::uinteraction::frame::frame) pschema = Application.uinteraction().get_frame_schema("app-core/uinteraction", "005");

   pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton >();

   return pschema;

}


void simple_frame_window::_001OnCreate(signal_details * pobj)
{

   SCAST_PTR(::message::create, pcreate, pobj)

   if (pobj->previous())
      return;

   sp(::user::place_holder) pplaceholder = GetParent();

   if (pplaceholder != NULL)
   {
      sp(::user::place_holder_container) pcontainer = pplaceholder->GetParent();
      if (pcontainer != NULL)
      {
         pcontainer->on_hold(this, pplaceholder);
      }
   }

   if (m_bAutoWindowFrame)
   {
#ifdef METROWIN
      m_bWindowFrame = GetParent() == NULL || dynamic_cast < window * > (GetParent()->m_pimpl.m_p) != NULL;
#else
      m_bWindowFrame = GetParent() == NULL;
#endif
   }


   if (m_bWindowFrame)
   {
      /*WNDCLASS wndclass;

      char szBuf [64];
      ::GetClassName(get_handle(), szBuf, _countof(szBuf));

      GetClassInfo(System.m_hInstance,
      szBuf,
      &wndclass);*/

      // trans      SetIcon(wndclass.hIcon, false);

      // trans      HICON hicon = GetIcon(false);

      sp(::user::uinteraction::frame::frame) pinteractionframe = NULL;

      try
      {


         pinteractionframe = create_frame_schema();

      }
      catch (not_installed & e)
      {

         System.remove_frame(this);

         throw e;

      }


      //frame::FrameSchema * pschema = dynamic_cast < ::frame::FrameSchema * > (pinteractionframe);

      if (pinteractionframe != NULL && (_ca_is_basis() || Application.command()->m_varTopicQuery["version"] == "basis"))
      {

         //pinteractionframe->set_style("BlueRedPurple");

      }

      /*{
         frame::FrameSchemaHardCoded001 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded001 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command()->m_varTopicQuery["version"] == "basis"))
         {
         pschemaSpec->SetStyle(frame::FrameSchemaHardCoded001::StyleBlueRedPurple);
         }
         }
         {
         frame::FrameSchemaHardCoded002 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded002 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command()->m_varTopicQuery["version"] == "basis"))
         {
         pschemaSpec->SetStyle(frame::FrameSchemaHardCoded002::StyleBlueRedPurple);
         }
         }
         {
         frame::FrameSchemaHardCoded005 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded005 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command()->m_varTopicQuery["version"] == "basis"))
         {
         pschemaSpec->SetStyle(frame::FrameSchemaHardCoded005::StyleBlueRedPurple);
         }
         }
         {
         frame::FrameSchemaHardCoded008 * pschemaSpec = dynamic_cast < frame::FrameSchemaHardCoded008 * > (pschema);
         if(pschemaSpec != NULL && (_ca_is_basis() || Application.command()->m_varTopicQuery["version"] == "basis"))
         {
         pschemaSpec->SetStyle(frame::FrameSchemaHardCoded008::StyleBlueRedPurple);
         }
         }*/

      m_pframeschema = pinteractionframe;
      m_workset.AttachFrameSchema(m_pframeschema);
      if (!m_workset.update(
         this,
         this,
         this,
         this))
      {
         pcreate->m_bRet = false;
         return;
      }

#if defined(LINUX) || defined(APPLEOS)

      m_workset.SetActiveFlag(TRUE);

#endif


   }

   defer_synch_layered();


   create_bars();


   pcreate->m_bRet = false;

   

}



void simple_frame_window::_001OnDisplayChange(signal_details * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);

   post_simple_command(simple_command_load_window_rect, (LPARAM)FALSE);

   pobj->m_bRet = true;

   pbase->set_lresult(0);

   Default();

}


void simple_frame_window::_001OnSize(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   if (does_display_match())
   {

      WindowDataSaveWindowRect();

   }

}


void simple_frame_window::_001OnMove(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //if ((m_workset.GetMovingManager() == NULL ||
   //   m_workset.GetSizingManager() == NULL) || (!m_workset.GetMovingManager()->IsMoving()
   //   && !m_workset.GetSizingManager()->IsSizing()))
   //{
   //   _001RedrawWindow();
   //}



   if (does_display_match())
   {

      WindowDataSaveWindowRect();

   }

}

bool simple_frame_window::OnCreateClient(LPCREATESTRUCT lpcs, sp(::create_context) pContext)
{
   // trans   HICON hicon = GetIcon(false);
   return ::user::frame_window::OnCreateClient(lpcs, pContext);
}

bool simple_frame_window::pre_create_window(CREATESTRUCT& cs)
{

   if (!::user::frame_window::pre_create_window(cs))
      return FALSE;


   //cs.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
   cs.style = WS_POPUP;
   cs.style &= ~WS_VISIBLE;

   return TRUE;
}

void simple_frame_window::layout()
{

   if (m_bWindowFrame && m_workset.IsAppearanceEnabled())
   {
      //m_workset.layout();
   }
   else
   {
      ::user::frame_window::layout();
   }

}

void simple_frame_window::ViewOnActivateFrame(sp(::user::impact) pview, UINT user, sp(::user::interaction) pframe)
{
   UNREFERENCED_PARAMETER(pview);
   UNREFERENCED_PARAMETER(user);
   UNREFERENCED_PARAMETER(pframe);
   //   if(pview != NULL)
   //      pview->OnActivateFrame(WA_INACTIVE, (sp(::user::simple_frame_window)) pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(signal_details * pobj)
{
#ifdef WINDOWSEX
   SCAST_PTR(::message::base, pbase, pobj);
   MINMAXINFO FAR * lpMMI = (MINMAXINFO FAR*) pbase->m_lparam.m_lparam;
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
   if (bShow)
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


   POSITION pos = m_toolbarmap.get_start_position();

   id idKey;
   sp(::user::interaction) pbar;
   while (pos != NULL)
   {
      m_toolbarmap.get_next_assoc(pos, idKey, pbar);
      try
      {
         pbar->ShowWindow(nShow);
      }
      catch (...)
      {
      }
   }

   layout();

}


void simple_frame_window::WfiOnFullScreen()
{

   ShowControlBars(false);

   _001WindowFullScreen();

}


void simple_frame_window::WfiOnExitFullScreen()
{

   ShowControlBars(true);

   WorkSetClientInterface::WfiOnExitFullScreen();

}


void simple_frame_window::_001OnViewFullScreen(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   ToggleFullScreen();

}


void simple_frame_window::_001OnMouseMove(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //   SCAST_PTR(::message::mouse, pmouse, pobj)
}

void simple_frame_window::_001OnUpdateViewFullScreen(signal_details * pobj)
{
   SCAST_PTR(::base::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable();
   pcmdui->m_pcmdui->_001SetCheck(WfiIsFullScreen());
   pcmdui->m_bRet = true;
}


void simple_frame_window::ToggleFullScreen()
{

   if (WfiIsFullScreen())
   {

      WfiRestore(false);

   }
   else
   {

      WfiFullScreen();

   }

}


bool simple_frame_window::_001CanEnterScreenSaver()
{
   return true;
}

void simple_frame_window::_001OnSysCommand(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);

   if (pbase->m_wparam == SC_SCREENSAVE)
   {
      if (!_001CanEnterScreenSaver())
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
         return;
      }
   }

   if (m_bWindowFrame)
   {
      if (pbase->m_wparam == SC_MAXIMIZE)
      {
         WfiMaximize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if (pbase->m_wparam == SC_RESTORE)
      {
         if (WfiIsFullScreen())
         {
            WfiFullScreen();
         }
         else
         {
            WfiRestore(false);
         }
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if (pbase->m_wparam == SC_MINIMIZE)
      {
         WfiMinimize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }

}


void simple_frame_window::_001OnToggleCustomFrame(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   SetCustomFrame(!GetCustomFrame());
}

void simple_frame_window::_001OnUpdateToggleCustomFrame(signal_details * pobj)
{
   SCAST_PTR(::base::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable();
   pcmdui->m_pcmdui->_001SetCheck(m_bWindowFrame);
}



void simple_frame_window::ActivateFrame(int32_t nCmdShow)
{

   ::user::frame_window::ActivateFrame(nCmdShow);
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

void simple_frame_window::_001OnClose(signal_details * pobj)
{
   if (m_iModalCount > 0)
   {
      EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }
   else if (GetTopLevelFrame() != NULL
      && (GetTopLevelFrame()->m_iModalCount > 0))
   {
      GetTopLevelFrame()->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }
   else if (m_iModalCount > 0)
   {
      m_pimpl->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
      return;
   }
   else if (GetTopLevelFrame() != NULL && GetTopLevelFrame()->m_iModalCount > 0)
   {
      GetTopLevelFrame()->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }


   pobj->m_bRet = true;
   // Note: only queries the active document
   sp(::user::document) pdocument = GetActiveDocument();
   if (pdocument != NULL && !pdocument->can_close_frame(this))
   {
      // document can't close right now -- don't close it
      return;
   }

   sp(::application) papp = &Application;

   if (papp->m_pcoreapp->is_system() || papp->m_pcoreapp->is_session())
   {

      // TODO: instead of closing all applications in process System.m_apptra, should close application that make part of
      // cube, bergedge, session or system.

      ::base::application_ptra appptra = System.get_appptra();

      for (int32_t i = 0; i <  appptra.get_count(); i++)
      {

         sp(::application) pappChild = &appptra[i];

         if (!pappChild->_001CloseApplicationByUser(this))
            return;

      }

   }
   else if (papp->m_pcoreapp->userex()->GetVisibleTopLevelFrameCountExcept(this) <= 0)
   {

      if (!papp->m_pcoreapp->_001CloseApplicationByUser(this))
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
      // trans      ::user::frame_window::OnNcCalcSize(bCalcValidRects, lpncsp);
   }

}

#endif

void simple_frame_window::_001OnNcActivate(signal_details * pobj)
{
   SCAST_PTR(::message::nc_activate, pncactivate, pobj)
      // stay active if WF_STAYACTIVE bit is on
   if (m_nFlags & WF_STAYACTIVE)
      pncactivate->m_bActive = TRUE;

   // but do not stay active if the window is disabled
   if (!is_window_enabled())
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
      pncactivate->set_lresult(DefWindowProc(WM_NCACTIVATE, pncactivate->m_bActive, 0)); // bStop
      pncactivate->m_bRet = pncactivate->get_lresult() != 0;
      return;
   }
}



bool simple_frame_window::LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle, sp(::user::interaction) pParentWnd, sp(::create_context) pContext)
{

   UNREFERENCED_PARAMETER(pParentWnd);

   // only do this once
   //   ASSERT_VALID_IDR(nIDResource);
   //   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   //   string strFullString;
   //   if (strFullString.load_string(nIDResource))
   //      __extract_sub_string(m_strTitle, strFullString, 0);    // first sub-string

   const char * lpszTitle = m_strTitle;

   if (pParentWnd == NULL)
      pParentWnd = Application.get_request_parent_ui(this, pContext);

   dwDefaultStyle &= ~WS_VISIBLE;

   if (!CreateEx(0L, NULL, lpszTitle, dwDefaultStyle, rect(0, 0, 0, 0), pParentWnd, /*nIDResource*/ 0, pContext))
   {
      return FALSE;   // will self destruct on failure normally
   }

   /* trans   // save the default menu handle
      ASSERT(get_handle() != NULL);
      m_hMenuDefault = ::GetMenu(get_handle()); */

   // load accelerator resource
   //   LoadAccelTable(MAKEINTRESOURCE(nIDResource));

   if (pContext == NULL)   // send initial update
      SendMessageToDescendants(WM_INITIALUPDATE, 0, (LPARAM)0, TRUE, TRUE);

   return TRUE;
}




void simple_frame_window::_001OnDdeInitiate(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj)
      pbase->set_lresult(DefWindowProc((uint32_t)pbase->m_wparam, pbase->m_lparam, pbase->get_lresult()));
}


void simple_frame_window::pre_translate_message(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (pbase->m_uiMessage == WM_MOUSEMOVE)
   {

   }
   else if (pbase->m_uiMessage == WM_KEYDOWN)
   {

      SCAST_PTR(::message::key, pkey, pobj);

      if (pkey->m_ekey == ::user::key_alt)
      {
         m_bFullScreenAlt = false;
      }
      else if (pkey->m_ekey == ::user::key_return)
      {
         if (session().is_key_pressed(::user::key_control)
            && session().is_key_pressed(::user::key_alt))
         {
            m_bFullScreenAlt = true;
            if (!IsFullScreen())
            {
               if (DeferFullScreen(true, false))
               {
                  pbase->m_bRet = true;
                  return;
               }
            }
         }
      }
   }
   else if (pbase->m_uiMessage == WM_KEYUP)
   {

      SCAST_PTR(::message::key, pkey, pobj);

      if (pkey->m_ekey == ::user::key_alt)
      {
         if (IsFullScreen()
            && session().is_key_pressed(::user::key_control)
            && !m_bFullScreenAlt)
         {
            if (DeferFullScreen(false, true))
            {
               pbase->m_bRet = true;
               return;
            }
         }
      }
   }
   return ::user::frame_window::pre_translate_message(pobj);
}







void simple_frame_window::InitialFramePosition(bool bForceRestore)
{

#ifdef WINDOWSEX

   if(GetParent() == NULL)
   {

      //::SetWindowRgn(get_handle(),NULL,false); // Clean any persisted window region

      /*keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

      keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

      keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

      keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

      ::SetWindowPos(get_handle(),NULL,0,0,0,0,SWP_SHOWWINDOW); // skip possible ShowWindow with "good" (worst ) "Windows" (Loosedows) defaults*/

      //::ShowWindow(get_handle(),SW_SHOWNORMAL); // skip possible ShowWindow with "good" (worst ) "Windows" (Loosedows) defaults

      //::ShowWindow(get_handle(),SW_SHOWDEFAULT); // skip possible ShowWindow with "good" (worst ) "Windows" (Loosedows) defaults

   }

#endif

   if (m_bFrameMoveEnable)
   {



      WindowDataLoadWindowRect(bForceRestore,true);

      WindowDataEnableSaveWindowRect(true);

   }

   ActivateTopParent();

   BringToTop(-1);

   if (m_workset.get_appearance() != NULL && m_workset.GetAppearance() == ::user::AppearanceIconic)
   {

      WfiRestore(false);

   }

   if(m_workset.m_pframeschema != NULL)
   {

      m_workset.m_pframeschema->title_bar_layout(true);

   }

}


void simple_frame_window::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
{
   if (session().savings().is_trying_to_save(::base::resource_processing)
      || session().savings().is_trying_to_save(::base::resource_translucent_background))
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(0, 0, 0));
   }
   else
   {

      ::user::frame_window::_001OnDeferPaintLayeredWindowBackground(pdc);
   }
}

void simple_frame_window::_000OnDraw(::draw2d::graphics * pdc)
{
   if (!m_bVisible)
      return;
   if (m_bblur_Background)
   {
      _001DrawThis(pdc);
      _001DrawChildren(pdc);
   }
   else if(!session().savings().is_trying_to_save(::base::resource_processing)
      && !session().savings().is_trying_to_save(::base::resource_display_bandwidth)
      && !session().savings().is_trying_to_save(::base::resource_memory))
      //&& (GetParent() != NULL || (this->GetExStyle() & WS_EX_LAYERED) != 0))
   {
#if TEST

      pdc->FillSolidRect(60, 10, 50, 50, ARGB(128, 184, 177, 84));
#endif

      _010OnDraw(pdc);
#if TEST

      pdc->FillSolidRect(10, 60, 50, 50, ARGB(128, 255, 248, 84));
#endif
   }
   else
   {
#if TEST

      pdc->FillSolidRect(60, 10, 50, 50, ARGB(128, 184, 177, 84));
#endif

      _001DrawThis(pdc);
      _001DrawChildren(pdc);
#if TEST

      pdc->FillSolidRect(10, 60, 50, 50, ARGB(128, 184, 177, 84));
#endif
   }
}


void simple_frame_window::_001OnDraw(::draw2d::graphics * pdc)
{
   single_lock sl(m_pmutex, true);

   if (m_bblur_Background)
   {
      class imaging & imaging = System.visual().imaging();
      rect rectClient;
      GetClientRect(rectClient);
      //rectClient.offset(rectClient.top_left());
      if (session().savings().is_trying_to_save(::base::resource_translucent_background))
      {
         //pdc->FillSolidRect(rectClient, RGB(150, 220, 140));
      }
      else if (session().savings().is_trying_to_save(::base::resource_processing)
         || session().savings().is_trying_to_save(::base::resource_blur_background))
      {
         imaging.color_blend(pdc, rectClient, RGB(150, 180, 140), 150);
      }
      else
      {
#ifndef LINUX
         if (rectClient.size() != m_dibBk->size())
         {
            m_dibBk->create(rectClient.size());
            m_dibBk->Fill(0, 184, 184, 170);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::visual::fastblur *( *pfnNew )(sp(::base::application)) = (::visual::fastblur *(*)(sp(::base::application))) ::GetProcAddress(hmodule, "new_fastblur");
            m_fastblur.create(allocer());
            m_fastblur.initialize(rectClient.size(), 2);
         }
         if (m_fastblur.is_set() && m_fastblur->area() > 0)
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
#endif
      }
   }

   _011OnDraw(pdc);

}


bool simple_frame_window::on_before_set_parent(sp(::user::interaction) pinterface)
{

   WindowDataSaveWindowRect();

   if (!::database::user::interaction::on_before_set_parent(pinterface))
      return false;

   return true;

}


void simple_frame_window::on_set_parent(sp(::user::interaction) puiParent)
{

   ::database::user::interaction::on_set_parent(puiParent);

   UNREFERENCED_PARAMETER(puiParent);
   m_workset.m_pwndEvent = m_pimpl->m_pui;

   if (m_pupdowntarget != NULL && m_pupdowntarget->is_up_down_target())
   {
      if (puiParent == NULL)
      {
         m_bWindowFrame = true;
         m_workset.Enable(true);
      }
      else
      {
         m_bWindowFrame = false;
         m_workset.Enable(false);
      }
   }

   if (puiParent == NULL || !puiParent->is_place_holder())
   {

      WindowDataLoadWindowRect(false);

      WindowDataEnableSaveWindowRect(true);


   }

   if (m_bAutoWindowFrame)
   {
      // an updowntarget always show the frame for upping/downing
      if (!m_bWindowFrame)
      {
         m_bWindowFrame = m_bCustomFrameBefore;
      }
      if (!m_workset.IsEnabled())
      {
         m_workset.Enable(true);
         layout();
      }
   }
   else
   {
      if (puiParent != NULL)
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
   if (m_bWindowFrame && m_pframeschema != NULL && !WfiIsFullScreen())
   {
      m_pframeschema->get_window_client_rect(lprect);
   }
   else
   {
      ::user::frame_window::GetClientRect(lprect);
   }
}


bool simple_frame_window::is_application_main_window()
{
   return Application.m_puiMain == this;
}


void simple_frame_window::LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle, uint32_t dwStyle)
{
   sp(::user::interaction) pui = m_toolbarmap[idToolBar];
   simple_toolbar * ptoolbar;
   if (pui != NULL)
   {
      ptoolbar = dynamic_cast <simple_toolbar *> (pui.m_p);
   }
   else
   {
      ptoolbar = new simple_toolbar(get_app());
      ptoolbar->CreateEx(this, dwCtrlStyle, dwStyle);
      pui = ptoolbar;
      m_toolbarmap.set_at(idToolBar, pui);
   }
   if (ptoolbar != NULL)
   {
      ptoolbar->LoadXmlToolBar(session().file().as_string(session().dir().matter(pszToolBar)));
      layout();
   }
}


void simple_frame_window::_001OnUser184(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (pbase->m_wparam == 0 &&
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
   sp(::user::interaction) pParentWnd,        // != NULL for popups
   const char * lpszMenuName,
   uint32_t dwExStyle,
   sp(::create_context) pContext)
{
   return ::user::frame_window::create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, lpszMenuName, dwExStyle, pContext);

}





bool simple_frame_window::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
{

   if (m_workset._001OnCmdMsg(pcmdmsg))
      return true;

   // pump through current ::user::impact FIRST
   sp(::user::impact) pview = GetActiveView();
   if (pview != NULL && pview->_001OnCmdMsg(pcmdmsg))
      return TRUE;

   pview = get_child_by_id("pane_first");
   if (pview != NULL && pview->_001OnCmdMsg(pcmdmsg))
      return TRUE;

   // then pump through frame
   if (::user::frame_window::_001OnCmdMsg(pcmdmsg))
      return TRUE;

   // then pump through parent
   sp(::user::interaction) puiParent = GetParent();
   if (puiParent != NULL && puiParent->_001OnCmdMsg(pcmdmsg))
      return TRUE;

   // last but not least, pump through cast
   application* pApp = get_app()->m_pcoreapp;
   if (pApp != NULL && pApp->_001OnCmdMsg(pcmdmsg))
      return TRUE;

   sp(command_target_interface) pcommandtargetinterface = session().user()->get_keyboard_focus();

   if (pcommandtargetinterface != NULL)
   {
      if (pcommandtargetinterface->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }

   return FALSE;
}


#ifdef WINDOWSEX



void simple_frame_window::OnDropFiles(HDROP hDropInfo)
{

   SetActiveWindow();      // activate us first !
   UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

   ::userex::userex* puser = System.userex();
   ASSERT(puser != NULL);
   for (UINT iFile = 0; iFile < nFiles; iFile++)
   {
      char szFileName[_MAX_PATH];
      ::DragQueryFile(hDropInfo, iFile, szFileName, _MAX_PATH);

      sp(::create_context) createcontext(allocer());
      createcontext->m_spCommandLine->m_varFile = szFileName;

      puser->open_document_file(createcontext);
   }
   ::DragFinish(hDropInfo);


}

#else

void simple_frame_window::OnDropFiles(HDROP hDropInfo)
{

   UNREFERENCED_PARAMETER(hDropInfo);

}



#endif




// query end session for main frame will attempt to close it all down
bool simple_frame_window::OnQueryEndSession()
{
   application* pApp = &System;
   if (pApp != NULL && pApp->m_puiMain == this)
      return pApp->save_all_modified();

   return TRUE;
}


void simple_frame_window::OnEndSession(bool bEnding)
{

   if (!bEnding)
      return;

   application* pApp = &System;
   if (pApp != NULL && pApp->m_puiMain == this)
   {

      pApp->close_all_documents(TRUE);

      pApp->exit_instance();

   }

}


LRESULT simple_frame_window::OnDDEInitiate(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWSEX

   application* pApp = &System;
   if (pApp != NULL &&
      LOWORD(lParam) != 0 && HIWORD(lParam) != 0 &&
      (ATOM)LOWORD(lParam) == pApp->m_atomApp &&
      (ATOM)HIWORD(lParam) == pApp->m_atomSystemTopic)
   {
      // make duplicates of the incoming atoms (really adding a reference)
      char szAtomName[_MAX_PATH];
      VERIFY(GlobalGetAtomName(pApp->m_atomApp,
         szAtomName, _MAX_PATH - 1) != 0);
      VERIFY(GlobalAddAtom(szAtomName) == pApp->m_atomApp);
      VERIFY(GlobalGetAtomName(pApp->m_atomSystemTopic,
         szAtomName, _MAX_PATH - 1) != 0);
      VERIFY(GlobalAddAtom(szAtomName) == pApp->m_atomSystemTopic);

      // send the WM_DDE_ACK (caller will delete duplicate atoms)
      ::SendMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
         MAKELPARAM(pApp->m_atomApp, pApp->m_atomSystemTopic));
   }

#else

   throw not_implemented(get_app());

#endif

   return 0L;
}


// always ACK the execute command - even if we do nothing
LRESULT simple_frame_window::OnDDEExecute(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWSEX

   // unpack the DDE message
   uint_ptr unused;
   HGLOBAL hData;
   //IA64: Assume DDE LPARAMs are still 32-bit
   VERIFY(UnpackDDElParam(WM_DDE_EXECUTE, lParam, &unused, (uint_ptr*)&hData));

   // get the command string
   const char * lpsz = (const char *)GlobalLock(hData);
   string strCommand;
   try
   {
      strCommand = lpsz;
      GlobalUnlock(hData);
   }
   catch (memory_exception * pe)
   {
      GlobalUnlock(hData);
      pe->Delete();
   }


   // acknowledge now - before attempting to execute
   ::PostMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
      //IA64: Assume DDE LPARAMs are still 32-bit
      ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
      (UINT)0x8000, (uint_ptr)hData));

   // don't execute the command when the window is disabled
   if (!is_window_enabled())
   {
      TRACE(::base::trace::category_AppMsg, 0, "Warning: DDE command '%s' ignored because window is disabled.\n",
         strCommand.GetString());
      return 0;
   }

   // execute the command
   LPTSTR lpszCommand = strCommand.GetBuffer();
   if (!System.OnDDECommand(lpszCommand))
      TRACE(::base::trace::category_AppMsg, 0, "Error: failed to execute DDE command '%s'.\n", lpszCommand);
   strCommand.ReleaseBuffer();

#else

   throw not_implemented(get_app());

#endif

   return 0L;

}

LRESULT simple_frame_window::OnDDETerminate(WPARAM wParam, LPARAM lParam)
{

#ifdef WINDOWSEX

   ::PostMessage((oswindow)wParam, WM_DDE_TERMINATE, (WPARAM)get_handle(), lParam);

#else

   throw not_implemented(get_app());

#endif

   return 0L;

}


void simple_frame_window::NotifyFloatingWindows(uint32_t dwFlags)
{
   ASSERT_VALID(this);
   // trans   ASSERT(get_handle() != NULL);

   // get top level parent frame window first unless this is a child window
   sp(::user::frame_window) pParent = (GetStyle() & WS_CHILD) ? this : (GetTopLevelFrame().m_p);
   ASSERT(pParent != NULL);
   if (dwFlags & (FS_DEACTIVATE | FS_ACTIVATE))
   {
      // update parent window activation state
      bool bActivate = !(dwFlags & FS_DEACTIVATE);
      bool bEnabled = pParent->is_window_enabled();

      if (bActivate && bEnabled && pParent != this)
      {
         // Excel will try to Activate itself when it receives a
         // WM_NCACTIVATE so we need to keep it from doing that here.
         m_nFlags |= WF_KEEPMINIACTIVE;
         pParent->send_message(WM_NCACTIVATE, TRUE);
         m_nFlags &= ~WF_KEEPMINIACTIVE;
      }
      else
      {
         pParent->send_message(WM_NCACTIVATE, FALSE);
      }
   }

   // then update the state of all floating windows owned by the parent
#ifdef WINDOWSEX

   sp(::user::interaction) oswindowDesktop = System.get_desktop_window();

   if (oswindowDesktop.is_null())
      return;

   sp(::user::interaction) oswindow = oswindowDesktop->GetWindow(GW_CHILD);

   while (oswindow != NULL)
   {

      if (::user::is_descendant(pParent, oswindow))
         oswindow->send_message(WM_FLOATSTATUS, dwFlags);

      oswindow = oswindow->GetWindow(GW_HWNDNEXT);

   }

#else
   throw todo(get_app());
#endif
}



// query end session for main frame will attempt to close it all down
void simple_frame_window::_001OnQueryEndSession(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (&System != NULL && System.m_puiMain == this)
   {
      pbase->set_lresult(System.save_all_modified());
      pbase->m_bRet = true;
      return;
   }
   pbase->set_lresult(TRUE);
   return;
}

bool simple_frame_window::BaseOnControlEvent(::user::control_event * pevent)
{
   if (m_workset.BaseOnControlEvent(pevent))
      return true;
   return ::user::frame_window::BaseOnControlEvent(pevent);
}


string simple_frame_window::get_window_default_matter()
{

   if (m_pdocumenttemplate == NULL)
   {

      return simple_frame_window::get_window_default_matter();

   }

   return m_pdocumenttemplate->m_strMatter;

}


void simple_frame_window::guserbaseOnInitialUpdate(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj)
      ::user::FrameInitialUpdate * pfiu = (::user::FrameInitialUpdate *)pbase->m_lparam.m_lparam;
   if (pfiu != NULL)
   {
      sp(::user::frame_window) pframe = (this);
      // if the frame does not have an active ::user::impact, set to first pane
      sp(::user::impact) pview = NULL;
      if (pframe->GetActiveView() == NULL)
      {
         sp(::user::interaction) pwindow = pframe->GetDescendantWindow("pane_first");
         if (pwindow != NULL && base_class < ::user::impact >::bases(pwindow))
         {
            pview = (pwindow.m_p);
            pframe->SetActiveView(pview, FALSE);
         }
      }

      if (pfiu->m_bMakeVisible)
      {
         // send initial update to all views (and other controls) in the frame
         pframe->SendMessageToDescendants(WM_INITIALUPDATE, 0, (LPARAM)0, TRUE, TRUE);

         // give ::user::impact a chance to save the focus (CFormView needs this)
         if (pview != NULL)
            pview->OnActivateFrame(WA_INACTIVE, pframe);

         // finally, activate the frame
         // (send the default show command unless the main desktop window)
         int32_t nCmdShow = -1;      // default
         application* pApp = &System;
         if (pApp != NULL && pApp->m_puiMain == pframe)
         {
            nCmdShow = System.m_nCmdShow; // use the parameter from WinMain
            System.m_nCmdShow = -1; // set to default after first time
         }
         bool bFullScreen;
         data_get("FullScreen", ::base::system::idEmpty, bFullScreen);
         if (bFullScreen)
         {
            WfiFullScreen();
         }
         else
         {
            pframe->ActivateFrame(nCmdShow);
         }
         if (pview != NULL)
            pview->OnActivateView(TRUE, pview, pview);

      }

      sp(::user::document) pdoc = pfiu->m_pdoc;
      // update frame counts and frame title (may already have been visible)
      if (pdoc != NULL)
         pdoc->update_frame_counts();
      pframe->on_update_frame_title(TRUE);

      _001RedrawWindow();
   }
   pbase->set_lresult(0);
}


void simple_frame_window::_010OnDraw(::draw2d::graphics * pdc)
{

   if (!m_bVisible)
      return;

   if (GetExStyle() & WS_EX_LAYERED || m_etranslucency == TranslucencyTotal || m_etranslucency == TranslucencyPresent)
   {

      sp(::user::interaction) pui = get_bottom_child();

      while (pui != NULL)
      {

         if (pui->IsWindowVisible() && !base_class < ::user::uinteraction::frame::control_box > ::bases(pui))
         {

            pui->_000OnDraw(pdc);

         }

         pui = pui->above_sibling();

      }

      _001DrawThis(pdc);

      pui = get_bottom_child();

      while (pui != NULL)
      {
         if (base_class < ::user::uinteraction::frame::control_box > ::bases(pui))
         {
            string str;
            pui->GetWindowText(str);
            if (str == "r")
            {
               //TRACE0("x button");
            }
            if (pui->IsWindowVisible())
            {
               if (str == "r")
               {
                  //TRACE0("x button visible");
               }
               pui->_000OnDraw(pdc);
            }

         }
         pui = pui->above_sibling();
      }
   }
   else
   {

      _001DrawThis(pdc);

      _001DrawChildren(pdc);

   }

}


void simple_frame_window::_011OnDraw(::draw2d::graphics *pdc)
{

   if ((m_bWindowFrame || m_etranslucency == TranslucencyTotal || m_etranslucency == TranslucencyPresent) && !session().savings().is_trying_to_save(::base::resource_display_bandwidth))
   {

      ::user::uinteraction::frame::WorkSetClientInterface::_001OnDraw(pdc);

   }
   else
   {

      rect rect;

      GetClientRect(rect);

      pdc->FillSolidRect(rect, get_background_color());

   }

}


bool simple_frame_window::WfiOnMove(bool bTracking)
{
   if (!bTracking)
   {
      WindowDataSaveWindowRect();
   }
   return true;
}


bool simple_frame_window::WfiOnSize(bool bTracking)
{

   if (!bTracking)
   {

      WindowDataSaveWindowRect();

   }

   return true;

}


void simple_frame_window::WfiOnClose()
{

   post_message(WM_CLOSE);

}


void simple_frame_window::WfiOnMaximize()
{

   _001WindowMaximize();

}


void simple_frame_window::WfiOnMinimize()
{

   _001WindowMinimize();

}


void simple_frame_window::WfiOnRestore()
{

   _001WindowRestore();

   //good_restore(NULL,NULL,true);

}


bool simple_frame_window::DeferFullScreen(bool bFullScreen, bool bRestore)
{
   if (bFullScreen)
   {
      sp(::user::interaction) pwndParentFrame = GetParentFrame();
      if (pwndParentFrame == NULL)
      {
         if (!WfiIsFullScreen())
         {
            WfiFullScreen();
            return true;
         }
         else
         {
            return false;
         }
      }
      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
      if (pframe == NULL)
      {
         if (!WfiIsFullScreen())
         {
            WfiFullScreen();
            return true;
         }
         else
         {
            return false;
         }
      }

      if (pframe->DeferFullScreen(bFullScreen, bRestore))
         return true;

      if (!WfiIsFullScreen())
      {
         WfiFullScreen();
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      if (WfiIsFullScreen())
      {
         WfiRestore(false);
         return true;
      }
      sp(::user::interaction) pwndParentFrame = GetParentFrame();
      if (pwndParentFrame == NULL)
      {
         return false;
      }
      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
      if (pframe == NULL)
      {
         return false;
      }
      return pframe->DeferFullScreen(bFullScreen, bRestore);
   }
}


bool simple_frame_window::calc_layered()
{
   if (m_bLayered && _001GetTranslucency() != TranslucencyNone)
   {
      return !session().savings().is_trying_to_save(::base::resource_processing)
         && !session().savings().is_trying_to_save(::base::resource_display_bandwidth);
   }
   else
   {

      return false;

   } 

}


void simple_frame_window::data_on_after_change(signal_details * pobj)
{
   database::user::interaction::data_on_after_change(pobj);
   SCAST_PTR(database::change_event, phint, pobj);
   if (phint->m_key.m_idKey == "ca2"
      && phint->m_key.m_idIndex == "savings")
   {
      defer_synch_layered();
   }
}




bool simple_frame_window::on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult)
{

   return ::user::frame_window::on_simple_command(ecommand, lparam, lresult);

}

class mini_dock_frame_window* simple_frame_window::CreateFloatingFrame(uint32_t dwStyle)
{
   UNREFERENCED_PARAMETER(dwStyle);
   return NULL;
}


















bool simple_frame_window::set_appearance(::user::EAppearance eappearance)
{

   bool bOk1 = ::user::frame_window::set_appearance(eappearance);

   m_workset.SetAppearance(eappearance);

   return bOk1;

}


bool simple_frame_window::create_bars()
{

   if(!on_create_bars())
      return false;

   return true;

}


bool simple_frame_window::on_create_bars()
{

   return true;

}



















