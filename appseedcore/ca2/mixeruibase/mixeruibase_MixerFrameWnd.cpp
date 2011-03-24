#include "StdAfx.h"

#include "MixerFrameWnd.h"

MixerFrameWnd::MixerFrameWnd(::ca::application * papp) :
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
   m_pMainView = NULL;
   m_pdbcentral = (db_server *) &System.db();
   m_bSizeEnable = false;
}

MixerFrameWnd::~MixerFrameWnd()
{
}


 // BEGIN_MESSAGE_MAP(MixerFrameWnd, simple_frame_window)
   //{{AFX_MSG_MAP(MixerFrameWnd)
   //ON_WM_CREATE()
   //ON_WM_DESTROY()
   //ON_WM_MEASUREITEM()
   //ON_WM_CLOSE()
   //ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
   //ON_WM_PAINT()
   //ON_WM_SIZE()
   //ON_COMMAND(ID_MIXER_EXIT, OnMixerExit)
   //ON_WM_NCDESTROY()
   //}}AFX_MSG_MAP
    //ON_MESSAGE(WM_USER, OnUserMessage)
   //ON_MESSAGE(UM_FRAMEWORKV033_COMMAND, OnFrameworkV033Command)
 // END_MESSAGE_MAP()

void MixerFrameWnd::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &MixerFrameWnd::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &MixerFrameWnd::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_MEASUREITEM, pinterface, this, &MixerFrameWnd::_001OnMeasureItem);
   IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &MixerFrameWnd::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MixerFrameWnd::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_NCDESTROY, pinterface, this, &MixerFrameWnd::_001OnNcDestroy);
   IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &MixerFrameWnd::OnUserMessage);
   IGUI_WIN_MSG_LINK(UM_FRAMEWORKV033_COMMAND, pinterface, this, &MixerFrameWnd::OnFrameworkV033Command);
//xxx   VMSGEN_WINDOW_ON_COMMAND(ID_TOOLS_OPTIONS, pinterface, this, &MixerFrameWnd::OnToolsOptions);
//xxx   VMSGEN_WINDOW_ON_COMMAND(ID_MIXER_EXIT, pinterface, this, &MixerFrameWnd::OnMixerExit);

}

/////////////////////////////////////////////////////////////////////////////
// MixerFrameWnd message handlers


BOOL MixerFrameWnd::OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext) 
{
   return simple_frame_window::OnCreateClient(lpcs, pContext);
}

void MixerFrameWnd::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::create, pcreate, pobj)
   if(System.GetThread()->GetMainWnd() == this)
      System.GetThread()->SetMainWnd(NULL);


   m_wndframework.SetAppearanceTransparency(window_frame::ClientTransparent);

   //xxx
/*   
if(!m_wndToolBar.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        rect(0, 0, 0, 0),
        120) ||
      !m_wndToolBar.LoadToolBar(IDR_MIXER))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   */
    


    rect rectWnd;
    m_wndToolBar.GetWindowRect(rectWnd);
    size size;
    //CMenuBarV033::CalcSize(m_wndToolBar.GetToolBarCtrl(), size);
    m_wndToolBar.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
    //m_wndToolBar.GetToolBarCtrl().AutoSize();
    m_wndToolBar.GetWindowRect(rectWnd);
    m_wndToolBar.ModifyStyle(0, WS_VISIBLE);

/*  if (!m_rebar.AddBar(
         &m_wndToolBar, 
         NULL, 
         NULL,
         RBBS_BREAK 
         | RBBS_FIXEDBMP))
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }*/

   m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   m_wndToolBarExport.SetBarStyle(m_wndToolBar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   stringa straIndicator;
   straIndicator.add("IDS_APP_TITLE");
   straIndicator.add("IDS_APP_TITLE");
    if (!m_wndStatusBar.create(this) ||
      !m_wndStatusBar.SetIndicators(straIndicator))
   {
      TRACE0("Failed to create status bar\n");
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
   }
    m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
    m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);
      

//    m_pDialog = new CAlbumDialog(this);
  //  m_pDialog->create(IDD_ALBUM, this);
    //m_pDialog->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

    //return TRUE;

    //m_pDialog->create(this);
    
    m_pMainView = dynamic_cast < ::view * > (GetDlgItem(AFX_IDW_PANE_FIRST));

    ::user::interaction* pWnd = GetDlgItem(AFX_IDW_PANE_FIRST);
    if(pWnd != NULL)
    {
        pWnd->ModifyStyleEx(
                   WS_EX_CLIENTEDGE,
         0,
         SWP_FRAMECHANGED |
            SWP_NOSENDCHANGING);
    }
   // TODO: add your specialized creation code here

   m_bSizeEnable = true;


//   TransparentFrameWndUpdateBars();
   InitializeBars();

   pcreate->m_bRet = false;
}

MixerMainView * MixerFrameWnd::GetAlbumView()
{
    return dynamic_cast < MixerMainView * > (GetActiveView());
}

bool MixerFrameWnd::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   return simple_frame_window::_001OnCmdMsg(pcmdmsg) ;

}

MixerMainView * MixerFrameWnd::GetMainView()
{
    ASSERT(base < MixerMainView >::bases(m_pMainView));
    return dynamic_cast < MixerMainView * > (m_pMainView);
}


void MixerFrameWnd::_001OnDestroy(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::base, pbase, pobj)
   pbase->m_bRet = true;
}

void MixerFrameWnd::OnUserMessage(gen::signal_object * pobj)
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

BOOL MixerFrameWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
   if( !simple_frame_window::PreCreateWindow(cs) )
      return FALSE;
    cs.style &= ~WS_CAPTION;
    cs.style &= ~WS_THICKFRAME;
    cs.style |= WS_CLIPCHILDREN;
   return TRUE;
}

void MixerFrameWnd::_001OnMeasureItem(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::measure_item, pmeasureitem, pobj)
}

/*bool MixerFrameWnd::Initialize(db_server *pdbcentral)
{
    m_pdbcentral = pdbcentral;

    m_pdbcentral->get_db_long_set()->LoadWindowCoordinates(
      "Janelas",
      "Álbum",
      this);
    return true;
}*/

void MixerFrameWnd::_001OnClose(gen::signal_object * pobj) 
{
   pobj->m_bRet = false;
}

bool MixerFrameWnd::OnToolsOptions() 
{
//   if(m_poptionsdlg == NULL)
//   {
//      m_poptionsdlg = new CAlbumOptionsDialog;
//      m_poptionsdlg->create(&m_poptionsdlg);
//      m_poptionsdlg->ShowWindow(SW_SHOWNORMAL);
//   }
   return true;
}

LRESULT MixerFrameWnd::OnAppLanguage(WPARAM wParam, LPARAM lParam)
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

bool MixerFrameWnd::InitializeBars()
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
    if (!m_wndStatusBar.SetIndicators(straIndicator))
   {
      TRACE0("Failed to create status bar\n");
      return false;      // fail to create
   }
    m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
    m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);


   return bResult;
}

void MixerFrameWnd::pre_translate_message(gen::signal_object * pobj) 
{
   return simple_frame_window::pre_translate_message(pobj);
}


void MixerFrameWnd::OnFrameworkV033Command(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
//   return simple_frame_window::OnFrameworkV033Command(wParam, lParam);
   pbase->set_lresult(0);
   pbase->m_bRet = true;
}

void MixerFrameWnd::TwiOnDraw(::ca::graphics *pdc)
{
   UNREFERENCED_PARAMETER(pdc);
//   simple_frame_window::TwiOnDraw(pdc);
}

bool MixerFrameWnd::OnMixerExit() 
{
   PostMessage(WM_CLOSE);
   return true;
}

void MixerFrameWnd::PostNcDestroy() 
{
   simple_frame_window::PostNcDestroy();
}


void MixerFrameWnd::_001OnNcDestroy(gen::signal_object * pobj) 
{
   pobj->m_bRet = false;
}

void MixerFrameWnd::UpdateToolBarText(simple_toolbar & toolbar)
{
   UNREFERENCED_PARAMETER(toolbar);
//   UINT uiID;
//   string str;
   //for(int i = 0; i < toolbar.get_count(); i++)
   {
//      uiID = toolbar.GetItemID(i);
   //   if(GetToolButtonText(str, uiID))
   //   {
   //      toolbar.SetButtonText(i, str);
   //   }
   }

}

bool MixerFrameWnd::GetToolButtonText(string & str, UINT uiCmd)
{
   UNREFERENCED_PARAMETER(str);
   UNREFERENCED_PARAMETER(uiCmd);
   /* xxx
   UINT uiText = -1;
   switch(uiCmd)
   {
   case ID_ALBUM_NAVIGATOR:
      uiText = IDS_ALBUM_NAVIGATOR;
      break;
   case ID_ALBUM_FULLLIST:
      uiText = IDS_ALBUM_FULLLIST;
      break;
   case ID_ALBUM_TREELIST:
      uiText = IDS_ALBUM_EXPLORE;
      break;
   case ID_ALBUM_SEARCHLIST:
      uiText = IDS_ALBUM_SEARCH;
      break;
   case ID_ALBUM_DUPLICATESLIST:
      uiText = IDS_ALBUM_DUPLICATESLIST;
      break;
   case ID_VIEW_NOTEPAD:
      uiText = IDS_ALBUM_EXPORTTEXT;
      break;
   case ID_MSWORD9:
      uiText = IDS_ALBUM_EXPORTMSWORD9;
      break;
   case ID_GOBACK:
      uiText = IDS_ALBUM_NAVIGATOR_GOBACK;
      break;
   case ID_GOFORWARD:
      uiText = IDS_ALBUM_NAVIGATOR_GOFORWARD;
      break;
   }
   */

/*   if(uiText == -1)
      return FALSE;
   else
   {
      return str.load_string(uiText) != 0;
   }
*/

   return false;

}

