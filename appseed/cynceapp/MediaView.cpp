#include "stdafx.h"
#include "MediaView.h"




namespace mediaplay
{


IMPLEMENT_DYNCREATE(MediaView, BaseView)

  
MediaView::MediaView()
{

   m_plinesTitle->InstallMessageHandling(this);
   m_basecontrol.Create(this); 
   m_wndrender.SetWindow(this);
   DISetSection("MusicalPlayerLightView");
}

MediaView::~MediaView()
{
}

void MediaView::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(this);
   MediaViewInterface::_001InstallMessageHandling(this);

	IGUI_WIN_MSG_LINK(WM_DESTROY        , this, this, &MediaView::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE           , this, this, &MediaView::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT          , this, this, &MediaView::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE         , this, this, &MediaView::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , this, this, &MediaView::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR      , this, this, &MediaView::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND     , this, this, &MediaView::_001OnEraseBkgnd);

//	IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &MediaView::_001OnTabClick);
	IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &MediaView::_001OnWavePlayerEvent);
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)

   igui::win::message::connect(
      WM_APP + 111,
      this,
      this, 
      &MediaViewInterface::_001OnMessageX);


   igui::win::message::connect(
      WM_SIZE, 
      this,
      this, 
      &MediaViewInterface::_001OnSize);
   
   igui::win::message::connect(
      WM_TIMER, 
      this,
      this,
      &MediaViewInterface::_001OnTimer);

   igui::win::message::connect(
      APPM_NOTIFY,
      this,
      this,
      &MediaViewInterface::_001OnAppNotify);

}
/////////////////////////////////////////////////////////////////////////////
// MediaView drawing

void MediaView::OnDraw(CDC* pdcScreen)
{
}

/////////////////////////////////////////////////////////////////////////////
// MediaView diagnostics

#ifdef _DEBUG
void MediaView::AssertValid() const
{
	BaseView::AssertValid();
}

void MediaView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaView message handlers

// vmpLightView.cpp : implementation of the MediaView class
//


/////////////////////////////////////////////////////////////////////////////
// MediaView


BOOL MediaView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// MediaView printing

BOOL MediaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void MediaView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void MediaView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
//void MediaView::OnCancelEditSrvr()
//{
//	GetMediaViewData()->OnDeactivateUI(FALSE);
//}

/////////////////////////////////////////////////////////////////////////////
// MediaView message handlers
void MediaView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   BaseView::_001OnInitialUpdate(pobj);


	
}
CWnd * MediaView::KaraokeGetWnd()
{
   return this;
}

CWnd * MediaView::_001GetWnd()
{
   return this;
}

void MediaView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* phint) 
{
	if(lHint == 1000)
   {
      PrepareLyricLines();
      if(GetMediaViewData()->GetMode() == MediaViewData::ModeMidi)
      {
         m_lpbouncingball->SetQuarterNoteDuration(
            GetMidiSequence().GetFile().m_pFileHeader->GetQuarterNoteTicks());
      }
   }

   if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(MediaViewUpdateHint)))
      {
         MediaViewUpdateHint * puh = (MediaViewUpdateHint * ) phint;
         if(puh->IsTypeOf(MediaViewUpdateHint::TypeExecuteStop))
         {
            _ExecuteStop();
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeCloseDevice))
         {
            CloseDevice();
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeDoPlay))
         {
            _ExecutePlay(true);
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypePlayIfNotPlaying))
         {
            if(!GetMidiSequence().IsPlaying())
            {
               _ExecutePlay(true);
            }
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeGetMidiPlayerInterface)
            && puh->m_pmidiplayer == NULL)
         {
            puh->m_pmidiplayer = this;
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeAttachPlaylist)
            && puh->m_pplaylistdoc != NULL)
         {
// xxx            puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
// xxx            m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeFullScreen))
         {
            if(puh->m_bFullScreen)
            {
               ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
            }
            else
            {
               ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
            }
         }
         else if(puh->IsTypeOf(MediaViewUpdateHint::TypeAfterOpenDocument))
         {
            MediaViewData * pviewdata = GetMediaViewData();
            bool bListenMinusOne;
            CString str;
            International::UnicodeToACP(str, pviewdata->GetPathName());
            if(DBListenMinusOne(false, pviewdata->GetPathName(), bListenMinusOne))
            {
              _ExecuteListenMinusOne(bListenMinusOne);
            }
            if(pviewdata->GetMode() == MediaViewData::ModeWave)
            {
               aud::WavePlayerCommand command;
               command.OpenFile(&pviewdata->GetWaveFile());
               /*
               switch(pviewdata->GetType())
               {
               case MediaViewData::TypeAiff:
                  command.OpenAiffFile(&pviewdata->GetWaveFile());
                  break;
               case MediaViewData::TypeCda:
                  command.OpenCdaFile(&pviewdata->GetWaveFile());
                  break;
               case MediaViewData::TypeMpeg:
                  command.OpenMp3File(&pviewdata->GetWaveFile());
                  break;
               case MediaViewData::TypeTwinVQ:
                  command.OpenVqfFile(&pviewdata->GetWaveFile());
                  break;
               case MediaViewData::TypeWav:
                  command.OpenWavFile(&pviewdata->GetWaveFile());
                  break;
               case MediaViewData::TypeWm:
                  command.OpenWmFile(&pviewdata->GetWaveFile());
                  break;
               default:
                  ASSERT(FALSE);
                  break;
               }*/
               m_pwaveplayer->ExecuteCommand(command);



            }
         }

      }
   }
	
	
}
CWnd & MediaView::BackViewGetWnd()
{
   return *this;
}
void MediaView::_001OnDestroy(gen::signal_object * pobj) 
{
	BaseView::OnDestroy();

   if(_ExecuteIsPlaying())
   {
      _ExecuteStop();
   }

   if(m_pwaveplayer != NULL)
   {
      m_pwaveplayer->PostThreadMessage(WM_QUIT, 0, 0);
   }
	
   m_bDestroy = true;	
}



void MediaView::_001OnSize(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

   pobj->previous();

   double d = psize->m_size.cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   GetClientRect(m_rectKaraokeView);


   CRect rectClient;
   _w001GetClientRect(rectClient);
   CRect rect = rectClient;

   rect.top = rect.bottom - 24;
   m_viewlineStatus.SetPlacement(rect);


   m_rectKaraokeView.bottom -= 16;

   LayoutTitleLines();
   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();
}

void MediaView::_001OnPaint(gen::signal_object * pobj) 
{
	CPaintDC dc(this); // device context for painting
   _001OnDraw(&dc);
}

void MediaView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
   m_pwaveplayer->SetCallback(GetSafeHwnd());

/*xxx   m_pplaylistcallback = new CVmpLightPlaylistCallback(
      &musctrl::CMusicalPlayerCentral::AppGetMusicalPlayerCentral(),
      GetMediaViewData());*/


  // m_gdi.m_dc.Attach(GetDC()->GetSafeHdc());
/*   GLuint PixelFormat;			// Holds The Results After Searching For A Match

   CDC * pdc = GetDC();
   HDC hdc = pdc->GetSafeHdc();
	
	if (!(PixelFormat=ChoosePixelFormat(hdc, &m_pixelformatdescriptor)))	// Did Windows Find A Matching Pixel Format?
	{
//		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;								// Return FALSE
	}
	
	if(!SetPixelFormat(hdc, PixelFormat,&m_pixelformatdescriptor))		// Are We Able To Set The Pixel Format?
	{
//		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;								// Return FALSE
	}

	if (!(m_hglrc = wglCreateContext(hdc)))				// Are We Able To Get A Rendering Context?
	{
//		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;								// Return FALSE
	}

	if(!wglMakeCurrent(hdc, m_hglrc))					// Try To Activate The Rendering Context
	{
//		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return -1;								// Return FALSE
	}*/
   m_pdocinterface = dynamic_cast < MediaDocInterface * > (GetDocument());


   int i;
   if(DILoad("GradualFilling", i))
   {
      m_bGradualFilling = i != 0;
   }
   if(DILoad("BouncingBall", i))
   {
      m_bBouncingBall = i != 0;
   }



   GetMediaViewData()->m_karaokeinterface.m_pwaveplayer = m_pwaveplayer;

   MediaViewData * pdoc = GetMediaViewData();
   SetKaraokeData(&pdoc->GetKaraokeData());
   m_lpbouncingball->SetKaraokeData(&pdoc->GetKaraokeData());

   if(GetMidiPlayer() == NULL)
      if(!OpenMidiPlayer())
      {
         ASSERT(FALSE);
         throw 0;
      }

   SetTimer(TimerLyric, 50, NULL); // max. 20 fps
   SetTimer(TimerBackView, 83, NULL);  // max. 12 fps
   //SetTimer(TimerSongInfo, 100, NULL);
   SetTimer(gen::Timer::ID_HOVER, 100, NULL);
   

   m_lyrictemplatelines.RemoveAll();
   m_lyrictemplatelines.SetSize(4);

   PrepareLyricTemplateLines();

   //AfxBeginThread(
     // ThreadProcLyricEvent,
      //(LPVOID) this,
      //THREAD_PRIORITY_NORMAL,
      //0,
      //0,
      //NULL);


}
void MediaView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   CPoint point = pcontextmenu->GetPoint();
   LyricViewLines & lyriclines = GetLyricLines();
   int iLine, iToken, iChar;
   CPoint ptCursor;
   ptCursor = point;
   ScreenToClient(&ptCursor);
   if(m_lyrictemplatelines.HitTest(ptCursor, iLine, iToken, iChar)
      == _lyricView::LineHitTestLink)
   {
      WString wstr;
      lyriclines.GetLink(wstr, iLine, iToken, iChar);
      m_wstrCurrentLink = wstr;
      SimpleMenu menu(BaseMenuCentral::GetMenuCentral());
      if (menu.LoadMenu(m_uiPopupLink))
      {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
   else
   {
      CMenu menu;
      if (menu.LoadMenu(m_uiPopup))
      {
         CMenu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
	
}


void MediaView::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      AfxMessageBox("Playlist");
   }
}

void MediaView::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
   aud::WavePlayer::EEvent eevent = (aud::WavePlayer::EEvent) pbase->m_wparam;
   switch(eevent)
   {
   case aud::WavePlayer::EventOpenDecoder:
      {
         MediaViewData * pviewdata = GetMediaViewData();
         if(pviewdata->GetMode() == MediaViewData::ModeWave)
         {
            AStrArray wstraFormat;
            BaseAStr2DArray wstr2aTitle;
            m_pwaveplayer->FillTitleInfo(wstraFormat, wstr2aTitle);
            if(wstraFormat.GetSize() <= 0)
            {
               wstraFormat.Add(L"%0");
               wstr2aTitle.AddNew();
               wstr2aTitle[wstr2aTitle.GetUpperBound()].Add(GetDocument()->GetTitle());
            }
            pviewdata->GetKaraokeData().GetStaticData().m_straTitleFormat = wstraFormat;
            pviewdata->GetKaraokeData().GetStaticData().m_str2aTitle = wstr2aTitle;
         }
         PrepareLyricTemplateLines();
         PrepareLyricLines();
         SetTitleVisible(true);
      }
      break;
   case aud::WavePlayer::EventPlay:
      OnMediaPlaybackStart();
      break;
   case aud::WavePlayer::EventPlaybackEnd:
      OnMediaPlaybackEnd();
      break;
   }
}

void MediaView::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   DWORD dwCodePage = IdToCodePage(pupdatecmdui->m_pcmdui->m_nID);
   if(GetKaraokeCodePage(NULL) == dwCodePage)
   {
      pupdatecmdui->m_pcmdui->SetCheck(1);
      pupdatecmdui->m_pcmdui->Enable(0);
   }
   else
   {
      pupdatecmdui->m_pcmdui->SetCheck(0);
      pupdatecmdui->m_pcmdui->Enable(1);
   }
}
void MediaView::_001OnViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::command, pcommand, pobj)
   DWORD dwCodePage = IdToCodePage(pcommand->GetId());
   SetKaraokeCodePage(dwCodePage);
}


/*xxxvoid MediaView::VmsDataOnAfterChange(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
{
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
      PrepareLyricLines();
      RedrawWindow();
   }
}*/


void MediaView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void MediaView::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

} // namespace mediaplay
