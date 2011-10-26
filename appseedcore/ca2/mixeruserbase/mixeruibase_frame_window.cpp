#include "StdAfx.h"
#include "mixeruserbase_frame_window.h"


namespace mixeruserbase
{


   frame_window::frame_window(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_wndToolBar(papp),
      m_wndToolBarExport(papp),
      m_wndToolBarHtmlView(papp),
      m_wndStatusBar(papp)
   {
      m_pmainview          = NULL;
      m_pdbcentral         = (db_server *) &System.db();
      m_bSizeEnable        = false;
      m_bblur_Background   = true;
      m_bLayered           = true;
      m_etranslucency      = TranslucencyPresent;
   }

   frame_window::~frame_window()
   {
   }


   //BEGIN_MESSAGE_MAP(frame_window, simple_frame_window)
   //{{AFX_MSG_MAP(frame_window)
   //ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
   //ON_COMMAND(ID_MIXER_EXIT, OnMixerExit)
   //END_MESSAGE_MAP()

   void frame_window::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame_window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &frame_window::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_MEASUREITEM, pinterface, this, &frame_window::_001OnMeasureItem);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame_window::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &frame_window::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_NCDESTROY, pinterface, this, &frame_window::_001OnNcDestroy);
      IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &frame_window::OnUserMessage);
      IGUI_WIN_MSG_LINK(UM_FRAMEWORKV033_COMMAND, pinterface, this, &frame_window::OnFrameworkV033Command);
      //xxx   VMSGEN_WINDOW_ON_COMMAND(ID_TOOLS_OPTIONS, pinterface, this, &frame_window::OnToolsOptions);
      //xxx   VMSGEN_WINDOW_ON_COMMAND(ID_MIXER_EXIT, pinterface, this, &frame_window::OnMixerExit);

   }


   BOOL frame_window::OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext) 
   {
      return simple_frame_window::OnCreateClient(lpcs, pContext);
   }

   void frame_window::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
         if(System.GetThread()->GetMainWnd() == this)
            System.GetThread()->SetMainWnd(NULL);

      pobj->previous();



      rect rectWnd;
      m_wndToolBar.GetWindowRect(rectWnd);
      size size;
      m_wndToolBar.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
      m_wndToolBar.GetWindowRect(rectWnd);
      m_wndToolBar.ModifyStyle(0, WS_VISIBLE);


      m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

      m_wndToolBarExport.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

      stringa straIndicator;
      straIndicator.add("IDS_APP_TITLE");
      straIndicator.add("IDS_APP_TITLE");
      /*if (!m_wndStatusBar.create(this) ||
      !m_wndStatusBar.SetIndicators(straIndicator))
      {
      TRACE0("Failed to create status bar\n");
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
      }
      m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
      m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);*/


      //    m_pDialog = new CAlbumDialog(this);
      //  m_pDialog->create(IDD_ALBUM, this);
      //m_pDialog->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

      //return TRUE;

      //m_pDialog->create(this);

      /*m_pMainView = dynamic_cast < ::view * > (GetDlgItem(AFX_IDW_PANE_FIRST));

      ::user::interaction* pWnd = GetDlgItem(AFX_IDW_PANE_FIRST);
      if(pWnd != NULL)
      {
      pWnd->ModifyStyleEx(
      WS_EX_CLIENTEDGE,
      0,
      SWP_FRAMECHANGED |
      SWP_NOSENDCHANGING);
      }*/
      // TODO: add your specialized creation code here

      m_bSizeEnable = true;


      //   TransparentFrameWndUpdateBars();
      InitializeBars();

      //pcreate->m_bRet = false;
   }

   bool frame_window::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
      return simple_frame_window::_001OnCmdMsg(pcmdmsg) ;

   }

   main_view * frame_window::GetMainView()
   {
      ASSERT(base < main_view >::bases(m_pmainview));
      return dynamic_cast < main_view * > (m_pmainview);
   }


   void frame_window::_001OnDestroy(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
         pbase->m_bRet = true;
   }

   void frame_window::OnUserMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
         if(pbase->m_wparam == 54) // ::view Changed
         {
            layout();
         }
         else if(pbase->m_wparam == 5678)
         {
            string str;
            m_wndStatusBar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
            ///xxx        str.load_string(IDS_ALBUM_SEARCHINGINDICATOR);
            m_wndStatusBar.SetPaneText(0, str);
         }
         else if(pbase->m_wparam == 56789)
         {
            m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH | SBPS_NORMAL, 0);
         }
         else if(pbase->m_wparam == 51678)
         {
            string str((const char *) pbase->m_lparam);
            m_wndStatusBar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
            m_wndStatusBar.SetPaneText(0, str);
         }
         pbase->set_lresult(0);
         pbase->m_bRet = true;
   }

   void frame_window::_001OnMeasureItem(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::measure_item, pmeasureitem, pobj)
   }

   /*bool frame_window::Initialize(db_server *pdbcentral)
   {
   m_pdbcentral = pdbcentral;

   m_pdbcentral->get_db_long_set()->LoadWindowCoordinates(
   "Janelas",
   "Álbum",
   this);
   return true;
   }*/

   void frame_window::_001OnClose(gen::signal_object * pobj) 
   {
      pobj->m_bRet = false;
   }

   bool frame_window::OnToolsOptions() 
   {
      //   if(m_poptionsdlg == NULL)
      //   {
      //      m_poptionsdlg = new CAlbumOptionsDialog;
      //      m_poptionsdlg->create(&m_poptionsdlg);
      //      m_poptionsdlg->ShowWindow(SW_SHOWNORMAL);
      //   }
      return true;
   }

   LRESULT frame_window::OnAppLanguage(WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(lParam);
      if(wParam == gen::application::WPARAM_LANGUAGE_UPDATE)
      {
         //      TransparentFrameWndUpdateBars();
         InitializeBars();
      }
      return 0;

   }

   /*CCommandIdToTextIdMapRow maprowToolBar[] =
   {
   CCommandIdToTextIdMapRow(
   ID_MIXER_SPEAKERSCONTROLS,
   IDS_MIXER_PLAYBACKCONTROL),
   CCommandIdToTextIdMapRow(
   ID_MIXER_WAVEINCONTROLS,
   IDS_MIXER_RECORDINGCONTROL),
   CCommandIdToTextIdMapRow::endRow 
   };
   */

   bool frame_window::InitializeBars()
   {
      bool bResult = true;

      string str;
      rect rectWnd;
      m_wndToolBar.GetWindowRect(rectWnd);
      size size;

      //   while(m_wndToolBar.DeleteButton(0));
      /*    if (!m_wndToolBar.LoadToolBar(IDR_MIXER))
      {
      TRACE0("Failed to create toolbar\n");
      bResult = false;      // fail to create
      }
      else
      {
      /*      CVmsGuiUtil::UpdateToolBarText(
      m_wndToolBar,
      maprowToolBar);
      CVmsGuiUtil::OptimizeToolBarStyleForText(
      m_wndToolBar);*/

      //      CMenuBarV033::CalcSize(m_wndToolBar.GetToolBarCtrl(), size);
      /*      m_wndToolBar.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
      //m_wndToolBar.GetToolBarCtrl().AutoSize();
      m_wndToolBar.GetWindowRect(rectWnd);
      m_wndToolBar.ModifyStyle(0, WS_VISIBLE);
      m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

      m_wndToolBarExport.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);
      }

      */



      stringa straIndicator;
      straIndicator.add("IDS_APP_TITLE");
      straIndicator.add("IDS_APP_TITLE");
      /*    if (!m_wndStatusBar.SetIndicators(straIndicator))
      {
      TRACE0("Failed to create status bar\n");
      return false;      // fail to create
      }
      m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
      m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);*/


      return bResult;
   }

   void frame_window::pre_translate_message(gen::signal_object * pobj) 
   {
      return simple_frame_window::pre_translate_message(pobj);
   }


   void frame_window::OnFrameworkV033Command(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      //   return simple_frame_window::OnFrameworkV033Command(wParam, lParam);
      pbase->set_lresult(0);
      pbase->m_bRet = true;
   }

   bool frame_window::OnMixerExit() 
   {
      PostMessage(WM_CLOSE);
      return true;
   }

   void frame_window::PostNcDestroy() 
   {
      simple_frame_window::PostNcDestroy();
   }


   void frame_window::_001OnNcDestroy(gen::signal_object * pobj) 
   {
      pobj->m_bRet = false;
   }

   void frame_window::UpdateToolBarText(simple_toolbar & toolbar)
   {
      UNREFERENCED_PARAMETER(toolbar);

   }

   bool frame_window::GetToolButtonText(string & str, UINT uiCmd)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(uiCmd);

      return false;

   }


} // namespace mixeruserbase


