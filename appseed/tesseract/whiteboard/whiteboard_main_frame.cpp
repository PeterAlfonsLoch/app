#include "StdAfx.h"

// // BEGIN_MESSAGE_MAP(main_frame, simple_frame_window)
   //{{AFX_MSG_MAP(main_frame)
/*   ON_WM_CREATE()
   ON_WM_CLOSE()
//   ON_COMMAND(ID_APP_EXIT, OnAppExit)
   ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
//   ON_COMMAND(ID_VIEW_WHITEBOARD, OnViewWhiteboard)
   ON_UPDATE_COMMAND_UI(ID_VIEW_WHITEBOARD, OnUpdateViewWhiteboard)
   //}}AFX_MSG_MAP
   // Global help commands
   ON_COMMAND(ID_HELP_FINDER, simple_frame_window::OnHelpFinder)
   ON_COMMAND(ID_HELP, simple_frame_window::OnHelp)
   ON_COMMAND(ID_CONTEXT_HELP, simple_frame_window::OnContextHelp)
   ON_COMMAND(ID_DEFAULT_HELP, simple_frame_window::OnHelpFinder)
   ON_WM_SIZE()
   ON_MESSAGE(WM_ENDSESSION, OnEndSession)*/
// // END_MESSAGE_MAP()

static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

namespace whiteboard
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_toolbarHtml(papp),
      m_toolbarWindow(papp),
      m_toolbarOptions(papp),
      ::ca::message_window_simple_callback(papp)
   {
      m_pview = NULL;
   }

   main_frame::~main_frame()
   {
   }

   void main_frame::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      
      pobj->previous();

      if(!initialize_message_window("ca2::fontopus::message_wnd::whiteboard"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }

      //if (!m_toolbarHtml.CreateEx(this, TBSTYLE_AUTOSIZE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_WRAPABLE, WS_CHILD | WS_VISIBLE | CBRS_TOP
      //   | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
      //   !m_toolbarHtml.LoadToolBar(IDR_HTML_FRAME))

      string str = Application.file().as_string(Application.dir().matter("whiteboard/html_toolbar.xml"));

      if (!m_toolbarHtml.CreateEx(this, TBSTYLE_AUTOSIZE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_WRAPABLE, 
         WS_CHILD | WS_VISIBLE | CBRS_TOP
         | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC) ||
         !m_toolbarHtml.LoadXmlToolBar(str))
      {
         TRACE0("Failed to create toolbar\n");
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;      // fail to create
      }
      /*if (!m_toolbarWindow.CreateEx(this,TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_WRAPABLE, WS_CHILD | WS_VISIBLE | CBRS_TOP
         | CBRS_TOOLTIPS | CBRS_SIZE_FIXED) ||
         !m_toolbarWindow.LoadToolBar(IDR_WINDOW))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }*/

      /*
      m_toolbarHtml.SetButtonText(0, "Back");
      m_toolbarHtml.SetButtonText(1, "Forward");
      m_toolbarHtml.SetButtonText(3, "DB");
      m_toolbarHtml.SetButtonText(4, "Whiteboard");
      m_toolbarHtml.SetButtonText(5, "Calendar");
      //m_toolbarHtml.SetButtonText(7, "Mrts");
      //m_toolbarHtml.SetButtonText(8, "Mrts qry lst");
      m_toolbarHtml.SetButtonText(10, "::view in Ie");
      m_toolbarHtml.SetButtonText(11, "Refresh");
      m_toolbarHtml.SetButtonText(12, "Options");
      m_toolbarHtml.SetButtonText(14, "More");
      */

      /*m_toolbarHtml.SetButtonStyle(0, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(0));
      m_toolbarHtml.SetButtonStyle(1, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(1));
      m_toolbarHtml.SetButtonStyle(2, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(2));
      m_toolbarHtml.SetButtonStyle(3, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(3));
      m_toolbarHtml.SetButtonStyle(4, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(4));
      m_toolbarHtml.SetButtonStyle(5, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(5));
      m_toolbarHtml.SetButtonStyle(6, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(6));
      m_toolbarHtml.SetButtonStyle(7, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(7));
      m_toolbarHtml.SetButtonStyle(8, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(8));
      //m_toolbarHtml.SetButtonStyle(8, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(8));
      m_toolbarHtml.SetButtonStyle(10, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(10));
      m_toolbarHtml.SetButtonStyle(11, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(11));
      m_toolbarHtml.SetButtonStyle(12, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(12));
      m_toolbarHtml.SetButtonStyle(14, TBBS_AUTOSIZE | m_toolbarHtml.GetButtonStyle(14));*/

      /* xxx
      if (!m_toolbarOptions.CreateEx(this, TBSTYLE_AUTOSIZE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_WRAPABLE,
         WS_CHILD | CBRS_TOP 
         | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC) ||
         !m_toolbarOptions.LoadToolBar(IDR_OPTIONS_VIEW))
      {
         TRACE0("Failed to create toolbar\n");
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;      // fail to create
      }*/


      /*m_toolbarOptions.SetButtonStyle(0, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(0));
      m_toolbarOptions.SetButtonStyle(1, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(1));
      m_toolbarOptions.SetButtonStyle(2, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(2));
      m_toolbarOptions.SetButtonStyle(3, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(1));
      m_toolbarOptions.SetButtonStyle(4, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(2));
*/
      /*
      m_toolbarOptions.SetButtonText(0, "Browser");
      m_toolbarOptions.SetButtonText(2, "About whiteboard...");
      m_toolbarOptions.SetButtonText(4, "More");
      */
   /*   m_toolbarOptions.SetButtonText(1, "Forward");
      m_toolbarOptions.SetButtonText(3, "Com EN PSY DB Home");
      m_toolbarOptions.SetButtonText(4, "Whiteboard Home");
      m_toolbarOptions.SetButtonText(5, "Calendar");
      m_toolbarOptions.SetButtonText(7, "::view in IE");
      m_toolbarOptions.SetButtonText(9, "Refresh");
      m_toolbarOptions.SetButtonText(11, "Options");

      m_toolbarOptions.SetButtonStyle(0, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(0));
      m_toolbarOptions.SetButtonStyle(1, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(1));
      m_toolbarOptions.SetButtonStyle(2, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(2));
      m_toolbarOptions.SetButtonStyle(3, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(3));
      m_toolbarOptions.SetButtonStyle(4, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(4));
      m_toolbarOptions.SetButtonStyle(5, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(5));
      m_toolbarOptions.SetButtonStyle(6, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(6));
      m_toolbarOptions.SetButtonStyle(7, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(7));
      m_toolbarOptions.SetButtonStyle(8, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(8));
      m_toolbarOptions.SetButtonStyle(9, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(9));
      m_toolbarOptions.SetButtonStyle(10, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(10));
      m_toolbarOptions.SetButtonStyle(11, TBBS_AUTOSIZE | m_toolbarOptions.GetButtonStyle(11));*/

      // TODO: Delete these three lines if you don't want the toolbar to
      //  be dockable
      /*m_toolbarHtml.EnableDocking(CBRS_ALIGN_ANY);
      EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_toolbarHtml);*/

      /*m_toolbarHtml.GetDockingFrame()->layout(TRUE);

      SetMenu(NULL);
      ModifyStyle(WS_MINIMIZEBOX | 0xc000, 0, SWP_FRAMECHANGED);
      ModifyStyleEx(WS_EX_APPWINDOW | WS_EX_CLIENTEDGE 
         | WS_EX_WINDOWEDGE, 0, SWP_FRAMECHANGED);   

      m_toolbarHtml.ModifyStyle(WS_BORDER | 0x10, 0, SWP_FRAMECHANGED);*/

   /*   if(!m_wndReBar.create(this))
      {
         return -1;
      }

      m_wndReBar.AddBar(&m_toolbarHtml);*/

      //SetMenu(NULL);
      ModifyStyle(WS_MINIMIZEBOX | 0xc000, 0, SWP_FRAMECHANGED);
      ModifyStyleEx(WS_EX_APPWINDOW | WS_EX_CLIENTEDGE 
         | WS_EX_WINDOWEDGE, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);   

   /*   if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
         | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
         !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }


      // TODO: Delete these three lines if you don't want the toolbar to
      //  be dockable
      m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
      EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_wndToolBar);*/

      /*SetParent(GetDesktopWindow());

      ModifyStyle(0, WS_CHILD | WS_VISIBLE);

      SetParent(GetDesktopWindow());*/

      ModifyStyle(WS_BORDER, 0, SWP_FRAMECHANGED);


      return;
   }

   BOOL main_frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;

      cs.style &= ~WS_VISIBLE;


      //cs.style |= FWS_ADDTOTITLE;

      // TODO: Modify the Window class or styles here by modifying
      //  the CREATESTRUCT cs

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // main_frame diagnostics

   #ifdef _DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }

   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // main_frame message handlers


   void main_frame::DisableCloseButton()
   {
      /* linux ::userbase::menu * pmenu = GetSystemMenu(FALSE);

      pmenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);*/
   }

   void main_frame::_001OnClose(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      Iconify();
   }

   void main_frame::Iconify()
   {
      ShowWindow(SW_HIDE);
   }



   //void main_frame::OnAppExit() 
   /*{
      DestroyWindow();
      
   }*/

   void main_frame::OnUpdateAppExit(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();
      
   }

   void main_frame::OnUpdateViewWhiteboard(cmd_ui *) 
   {
   }





   void main_frame::SetMrtsStyle() 
   {
      m_toolbarHtml.ChangeBackgroundColor(RGB(130, 180, 190));
   }

   void main_frame::SetNormalStyle() 
   {
      m_toolbarHtml.SetOriginalBackground();
   }


   void main_frame::_001OnEndSession(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      BOOL bEndSession = pbase->m_wparam;
      if(bEndSession)
      {
         LPARAM lReason = pbase->m_lparam;
         if((lReason & ENDSESSION_LOGOFF) != 0)
         {
            m_pview->_UserHour_PulseEvent(user_hour::event_wts_logoff);
         }
         else
         {
            // Shutdown
            m_pview->_UserHour_PulseEvent(user_hour::event_end_session);
         }
      }
      pbase->set_lresult(0);
      pbase->m_bRet = true;
   }


   void main_frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &main_frame::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_ENDSESSION, pinterface, this, &main_frame::_001OnEndSession);
   }


   void main_frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
   }


   void main_frame::_001OnApp2000(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)


      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 2)
         {
         }
      }
   }


} // namespace whiteboard