#include "framework.h"


namespace userbase
{


   frame_window::frame_window()
   {

      CommonConstruct();

   }


   void frame_window::CommonConstruct()
   {
      // trans ASSERT(get_handle() == ::null());

      m_nWindow = -1;                 // unknown ::ca::window ID
      m_bAutoMenuEnable = TRUE;       // auto enable on by default
      m_lpfnCloseProc = ::null();
      m_hMenuDefault = ::null();
      m_hAccelTable = ::null();
      //m_nIDHelp = 0;
      m_nIDTracking = 0;
      m_nIDLastMessage = 0;

      m_cModalStack = 0;              // initialize modality support
      m_hMenuAlt = ::null();
      m_nIdleFlags = 0;               // no idle work at start
      m_rectBorder.null();
#ifdef WINDOWSEX
      m_bHelpMode = HELP_INACTIVE;    // not in Shift+F1 help mode
#endif
      m_dwPromptContext = 0;

      m_pNextFrameWnd = ::null();         // not in list yet

      m_bInRecalcLayout = FALSE;
      m_nShowDelay = -1;              // no delay pending

      AddFrameWnd();
   }

   frame_window::~frame_window()
   {

      RemoveFrameWnd();

   }


   void frame_window::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      ::frame_window::install_message_handling(pinterface);
      frame_window_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame_window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &frame_window::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_IDLEUPDATECMDUI, pinterface, this, &frame_window::_001OnIdleUpdateCmdUI);
      IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &frame_window::_001OnSetFocus);
      IGUI_WIN_MSG_LINK(WM_ACTIVATE, pinterface, this, &frame_window::_001OnActivate);
      IGUI_WIN_MSG_LINK(WM_NCACTIVATE, pinterface, this, &frame_window::_001OnNcActivate);
      IGUI_WIN_MSG_LINK(WM_QUERYENDSESSION, pinterface, this, &frame_window::_001OnQueryEndSession);
   }




   void frame_window::NotifyFloatingWindows(uint32_t dwFlags)
   {
      ASSERT_VALID(this);
   // trans   ASSERT(get_handle() != ::null());

      // get top level parent frame ::ca::window first unless this is a child ::ca::window
      sp(frame_window) pParent = (GetStyle() & WS_CHILD) ? this : (GetTopLevelFrame());
      ASSERT(pParent != ::null());
      if (dwFlags & (FS_DEACTIVATE|FS_ACTIVATE))
      {
         // update parent ::ca::window activation state
         bool bActivate = !(dwFlags & FS_DEACTIVATE);
         bool bEnabled = pParent->IsWindowEnabled();

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
      sp(::user::interaction) oswindow = System.get_desktop_window()->GetWindow(GW_CHILD);
      while (oswindow != ::null())
      {
         if(::user::is_descendant(pParent, oswindow))
            oswindow->send_message(WM_FLOATSTATUS, dwFlags, 0);
         oswindow = oswindow->GetWindow(GW_HWNDNEXT);
      }
#else
      throw todo(get_app());
#endif
   }

   extern const CHAR _vfxWndFrameOrView[];
   //const CHAR _vfxWndFrameOrView[] = __WNDFRAMEORVIEW;

   /////////////////////////////////////////////////////////////////////////////
   // frame_window second phase creation

   bool frame_window::pre_create_window(CREATESTRUCT& cs)
   {

      if ((cs.style & FWS_ADDTOTITLE))
         cs.style |= FWS_PREFIXTITLE;

      //if (afxData.bWin4)
         cs.dwExStyle |= WS_EX_CLIENTEDGE;

      return TRUE;
   }



   void frame_window::_001OnCreate(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if(pobj->previous())
         return;

   }




   void frame_window::RemoveControlBar(::userbase::control_bar *pBar)
   {
      POSITION pos = m_listControlBars.find(pBar);
      if (pos != ::null())
         m_listControlBars.remove_at(pos);
   }


   /////////////////////////////////////////////////////////////////////////////
   // frame_window command/message routing







   /////////////////////////////////////////////////////////////////////////////
   // default frame processing


   // query end session for main frame will attempt to close it all down
   void frame_window::_001OnQueryEndSession(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::base, pbase, pobj);
      if (&Cube != ::null() && Cube.GetMainWnd() == this)
      {
         pbase->set_lresult(Cube.save_all_modified());
         pbase->m_bRet = true;
         return;
      }
      pbase->set_lresult(TRUE);
      return;
   }


   /////////////////////////////////////////////////////////////////////////////
   // Special ::view swapping/activation

   void frame_window::_001OnSetFocus(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if (m_pViewActive != ::null())
         m_pViewActive->SetFocus();
   }



   void frame_window::OnUpdateControlBarMenu(cmd_ui * pcmdui)
   {
/*      ASSERT(ID_VIEW_STATUS_BAR == "status_bar");
      ASSERT(ID_VIEW_TOOLBAR == __IDW_TOOLBAR);
      ASSERT(ID_VIEW_REBAR == __IDW_REBAR);*/

      pcmdui->ContinueRouting();
   }

   bool frame_window::OnBarCheck(UINT nID)
   {
      UNREFERENCED_PARAMETER(nID);
      /*ASSERT(ID_VIEW_STATUS_BAR == "status_bar");
      ASSERT(ID_VIEW_TOOLBAR == __IDW_TOOLBAR);
      ASSERT(ID_VIEW_REBAR == __IDW_REBAR);*/

      return FALSE;
   }


   /////////////////////////////////////////////////////////////////////////////
   // Setting title of frame ::ca::window - UISG standard



   void frame_window::DelayUpdateFrameMenu(HMENU hMenuAlt)
   {
      m_hMenuAlt = hMenuAlt;
      m_nIdleFlags |= idleMenu;
   }

   void frame_window::_001OnIdleUpdateCmdUI(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // update menu if necessary
      if (m_nIdleFlags & idleMenu)
         OnUpdateFrameMenu(m_hMenuAlt);

      // update title if necessary
      if (m_nIdleFlags & idleTitle)
         on_update_frame_title(TRUE);

      // recalc layout if necessary
      if (m_nIdleFlags & idleLayout)
      {
         layout();
         UpdateWindow();
      }

      // set the current message string if necessary
      if (m_nIDTracking != m_nIDLastMessage)
      {
         SetMessageText(m_nIDTracking);
         ASSERT(m_nIDTracking == m_nIDLastMessage);
      }
      m_nIdleFlags = 0;
   }



   void frame_window::_001OnSize(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::ca::message::size, psize, pobj)
   }




   /////////////////////////////////////////////////////////////////////////////
   // frame_window Diagnostics

   //#ifdef DEBUG
   void frame_window::assert_valid() const
   {
      try
      {
         ::user::interaction::assert_valid();
      }
      catch(...)
      {
      }
      try
      {
         if (m_pViewActive != ::null())
            ASSERT_VALID(m_pViewActive);
      }
      catch(...)
      {
      }
   }


   void frame_window::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      dumpcontext << "m_hAccelTable = " << (uint_ptr)m_hAccelTable;
      dumpcontext << "\nm_nWindow = " << m_nWindow;
      dumpcontext << "\nm_nIDHelp = " << m_strMatterHelp;
      dumpcontext << "\nm_nIDTracking = " << m_nIDTracking;
      dumpcontext << "\nm_nIDLastMessage = " << m_nIDLastMessage;
      if (m_pViewActive != ::null())
         dumpcontext << "\nwith active ::view: " << m_pViewActive.m_p;
      else
         dumpcontext << "\nno active ::view";

      dumpcontext << "\n";
   }
   //#endif //DEBUG



   // in this file for is_kind_of library granularity (is_kind_of references these)
   //// IMPLEMENT_DYNCREATE(frame_window, ::user::interaction)
   //// IMPLEMENT_DYNAMIC(::view, ::user::interaction)
   //// IMPLEMENT_DYNAMIC(::::userbase::control_bar, ::user::interaction)

   /////////////////////////////////////////////////////////////////////////////



   /////////////////////////////////////////////////////////////////////////////
   // frame_window (here for library granularity)



   sp(::user::interaction) frame_window::WindowDataGetWnd()
   {
      return this;
   }


   // dwDockBarMap
   /*const uint32_t frame_window::dwDockBarMap[4][2] =
   {
      { __IDW_DOCKBAR_TOP,      CBRS_TOP    },
      { __IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
      { __IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
      { __IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
   };*/



   bool frame_window::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(m_workset.BaseOnControlEvent(pevent))
         return true;
      return ::frame_window::BaseOnControlEvent(pevent);
   }


   bool frame_window::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      if(m_workset._001OnCmdMsg(pcmdmsg))
         return true;
      return ::frame_window::_001OnCmdMsg(pcmdmsg);
   }

   void frame_window::_000OnDraw(::ca::graphics * pdc)
   {
      frame_window_interface::_000OnDraw(pdc);
   }


   void frame_window::AddControlBar(::userbase::control_bar *pBar)
   {

      m_listControlBars.add_tail(pBar);

   }


} // namespace userbase






