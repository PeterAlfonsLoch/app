#include "StdAfx.h"
#include "VmsTextFrame.h"

static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

CVmsTextFrame::CVmsTextFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   m_wndToolBarStandard(papp)
{
}

CVmsTextFrame::~CVmsTextFrame()
{
}



int CVmsTextFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   m_dataid = "VmsText";
//   if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
//      return -1;
   

   ::user::interaction* pwnd = GetParent();

    SetDlgCtrlId(AFX_IDW_PANE_FIRST);

    int _db_style = GetStyle();
    ::ca::application * pApp = &System;
   
//    ::userbase::menu * pMenu = GetMenu();

    m_hMenuDefault = NULL;
  //  SetMenu(NULL);
    //::userbase::menu * pmenuDebug =GetMenu();
    /*if(pMenu != NULL)
    {
        pMenu->DestroyMenu();
    }*/



   
//   db_server * pDataCentral = db();
//   db_long_set * plongset = pDataCentral->get_db_long_set();
    ::user::interaction* pParent = GetParent();

    

/*   int iFullScreen = 0;
    plongset->Load("Main Frame", "Full Screen", &iFullScreen);
   int iCompactMode = 1;
   plongset->Load("Main Frame", "Compact Mode", &iCompactMode);

   
    //if(
    
    ViewCompactMode(iCompactMode != 0);
   ViewFullScreen(iFullScreen != 0);*/

//   m_bOnSizeSaving = true;
//   UpdateBars();
   return 0;
   
}




BOOL CVmsTextFrame::OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext) 
{
//   m_uiIDMenuBar = IDR_VMSTEXT;
   if(!simple_frame_window::OnCreateClient(lpcs, pContext))
      return FALSE;
       if (!m_wndToolBarStandard.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST , //|
//        TBSTYLE_WRAPABLE,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        rect(0, 0, 0, 0),
        "IDR_VMSTEXT"))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
/* xxx    if (!m_wndToolBarStandard.LoadToolBar(IDR_VMSTEXT))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }*/
    
    string str;


/*    if (!m_wndToolBarView.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST |
      WS_CHILD, 
        CBRS_ALIGN_TOP, 
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   #define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
   m_wndToolBarView.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);


    if (!m_wndToolBarPlay.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST, //|
//        TBSTYLE_WRAPABLE,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_PLAY) ||
      !m_wndToolBarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if (!m_wndDlgBar.create(this, IDR_MAINFRAME, 
      CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
   {
      TRACE0("Failed to create dialogbar\n");
      return -1;      // fail to create
   }*/


/*   if (
      !m_rebar.AddBar(&m_wndToolBarStandard, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
      //|| !m_rebar.AddBar(&m_wndDlgBar, NULL, NULL,  RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
      //|| !m_rebar.AddBar(&m_wndToolBarView, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
        //|| !m_rebar.AddBar(&m_wndToolBarPlay, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
      )
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }
*/
   /*
   if (!m_wndStatusBar.create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT)))
   {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }
*/

   // TODO: remove this if you don't want tool tips
   m_wndToolBarStandard.SetBarStyle(m_wndToolBarStandard.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

//   simple_edit *pEdit = (simple_edit * ) m_wndDlgBar.GetDlgItem(IDC_EDIT_TIME);
//   simple_edit *pEdit = NULL;
/*   if(pEdit)
   {
      m_pEditFont = new ::ca::font();
      LOGFONT logFont;
      RECT rect;
      pEdit->GetWindowRect(&rect);
      logFont.lfHeight = rect.bottom - rect.top ;
      logFont.lfWidth = 0;
      logFont.lfEscapement = 0;
      logFont.lfWeight = FW_NORMAL;
      logFont.lfItalic = FALSE;
      logFont.lfUnderline = FALSE;
      logFont.lfStrikeOut = FALSE;
      logFont.lfCharSet =   ANSI_CHARSET;
      logFont.lfOutPrecision = OUT_TT_PRECIS;
      logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      logFont.lfQuality = PROOF_QUALITY;
//      logFont.lfPitchAndFamily =  FIXED_PITCH | FF_SWISS;
      logFont.lfPitchAndFamily = 0;
      lstrcpy(logFont.lfFaceName, "Arial");
      m_pEditFont->CreateFontIndirect(&logFont);
      pEdit->SetFont(m_pEditFont);
   }*/

   return TRUE;
}
