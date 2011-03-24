#include "stdafx.h"


IMPLEMENT_DYNCREATE(MusicalPlayerLightView, MediaView)

MusicalPlayerLightView::MusicalPlayerLightView()
:m_hglrc(NULL)
{
   m_uiPopup      = IDR_POPUP_LYRICVIEW;
   m_uiPopupLink  = IDR_POPUP_LYRICVIEW_LINK;
   
   m_bOverrideKaraokeCodePage = false;
   m_bFileOverrideKaraokeCodePage = false;

   m_basecontrol.Create(this);
//   m_tab.InstallMessageHandling(this);



   m_wndrender.SetWindow(this);


   BackViewInitialize();
   BackViewGetInterface().Enable(true);




   DISetSection("MusicalPlayerLightView");
   m_bWaitingToPlay = false;
   m_bDestroy = false;

//   m_lpbouncingball->SetIcons(AfxGetApp()->LoadIcon(IDI_BB1), AfxGetApp()->LoadIcon(IDI_BB1_PRESSED1));
   m_lpbouncingball->SetBallType(kar::KaraokeBouncingBall::Ball);

   BackViewGetInterface().SetBackgroundImageChangeInterval(((MusicalPlayerLightApp *) AfxGetApp())->m_iBackgroundUpdateMillis);

//   VmsDataServerInterface & db = ((MusicalPlayerLightApp *) AfxGetApp())->GetVmsDataServerInterface();
//   db.AddClient(this);

}

MusicalPlayerLightView::~MusicalPlayerLightView()
{
}

void MusicalPlayerLightView::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   MediaView::_001InstallMessageHandling(pinterface);

   m_lyrictemplatelines.InstallMessageHandling(this);
   m_gdibuffer.InstallMessageHandling(this);

	IGUI_WIN_MSG_LINK(WM_DESTROY        , this, this, &MusicalPlayerLightView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE           , this, this, &MusicalPlayerLightView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT          , this, this, &MusicalPlayerLightView::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE         , this, this, &MusicalPlayerLightView::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , this, this, &MusicalPlayerLightView::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR      , this, this, &MusicalPlayerLightView::_001OnSetCursor);

   IGUI_WIN_ON_COMMAND(ID_CANCEL_EDIT_SRVR         , this, this, &MusicalPlayerLightView::_001OnCancelEditSrvr);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_PLAY             , this, this, &MusicalPlayerLightView::_001OnExecutePlay);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_PLAY             , this, this, &MusicalPlayerLightView::_001OnUpdateExecutePlay);
	IGUI_WIN_ON_COMMAND(ID_KARAOKE_BOUNCING_BALL    , this, this, &MusicalPlayerLightView::_001OnKaraokeBouncingBall);
	IGUI_WIN_UPD_CMD_UI(ID_KARAOKE_BOUNCING_BALL    , this, this, &MusicalPlayerLightView::_001OnUpdateKaraokeBouncingBall);
	IGUI_WIN_ON_COMMAND(ID_KARAOKE_GRADUAL_FILLING  , this, this, &MusicalPlayerLightView::_001OnKaraokeGradualFilling);
	IGUI_WIN_UPD_CMD_UI(ID_KARAOKE_GRADUAL_FILLING  , this, this, &MusicalPlayerLightView::_001OnUpdateKaraokeGradualFilling);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_STOP             , this, this, &MusicalPlayerLightView::_001OnExecuteStop);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_STOP             , this, this, &MusicalPlayerLightView::_001OnUpdateExecuteStop);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_PAUSE            , this, this, &MusicalPlayerLightView::_001OnExecutePause);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_PAUSE            , this, this, &MusicalPlayerLightView::_001OnUpdateExecutePause);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_MINUS_ONE        , this, this, &MusicalPlayerLightView::_001OnExecuteMinusOne);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_MINUS_ONE        , this, this, &MusicalPlayerLightView::_001OnUpdateExecuteMinusOne);
	IGUI_WIN_ON_COMMAND(ID_OPEN_LINK_IN_NEW_WINDOW  , this, this, &MusicalPlayerLightView::_001OnOpenLinkInNewWindow);
	IGUI_WIN_ON_COMMAND(ID_COPY_LINK_LOCATION       , this, this, &MusicalPlayerLightView::_001OnCopyLinkLocation);
	IGUI_WIN_ON_COMMAND(ID_PLAYLIST_EXECUTE_PLAY    , this, this, &MusicalPlayerLightView::_001OnPlaylistExecutePlay);
	IGUI_WIN_UPD_CMD_UI(ID_PLAYLIST_EXECUTE_PLAY    , this, this, &MusicalPlayerLightView::_001OnUpdatePlaylistExecutePlay);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_PREVIOUS         , this, this, &MusicalPlayerLightView::_001OnExecutePrevious);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_PREVIOUS         , this, this, &MusicalPlayerLightView::_001OnUpdateExecutePrevious);
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_NEXT             , this, this, &MusicalPlayerLightView::_001OnExecuteNext);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_NEXT             , this, this, &MusicalPlayerLightView::_001OnUpdateExecuteNext);
	//}}AFX_MSG_MAP
	// Standard printing commands
//   IGUI_WIN_MSG_LINK(WM_USER + 177              , this, this, &MusicalPlayerLightView::_001OnTabClick);
	/*IGUI_WIN_ON_COMMAND(ID_FILE_PRINT            , this, this, &MediaView::_001OnFilePrint);
	IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_DIRECT     , this, this, &MediaView::_001OnFilePrint);
	IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_PREVIEW    , this, this, &MediaView::_001OnFilePrintPreview);*/
	IGUI_WIN_ON_COMMAND(ID_EXECUTE_AUTO_RECORD   , this, this, &MusicalPlayerLightView::_001OnExecuteAutoRecord);
	IGUI_WIN_UPD_CMD_UI(ID_EXECUTE_AUTO_RECORD   , this, this, &MusicalPlayerLightView::_001OnUpdateExecuteAutoRecord);

   IGUI_WIN_ON_COMMAND_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, this, this, &MusicalPlayerLightView::_001OnViewEncoding);
   IGUI_WIN_UPD_CMD_UI_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, this, this, &MusicalPlayerLightView::_001OnUpdateViewEncoding);
}




BEGIN_MESSAGE_MAP(MusicalPlayerLightView, MediaView)
	//{{AFX_MSG_MAP(MusicalPlayerLightView)
   /*
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PLAY, OnUpdateExecutePlay)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(ID_KARAOKE_BOUNCING_BALL, OnKaraokeBouncingBall)
	ON_UPDATE_COMMAND_UI(ID_KARAOKE_BOUNCING_BALL, OnUpdateKaraokeBouncingBall)
	ON_COMMAND(ID_KARAOKE_GRADUAL_FILLING, OnKaraokeGradualFilling)
	ON_UPDATE_COMMAND_UI(ID_KARAOKE_GRADUAL_FILLING, OnUpdateKaraokeGradualFilling)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_STOP, OnUpdateExecuteStop)
	ON_COMMAND(ID_EXECUTE_PAUSE, OnExecutePause)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PAUSE, OnUpdateExecutePause)
	ON_COMMAND(ID_EXECUTE_MINUS_ONE, OnExecuteMinusOne)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_MINUS_ONE, OnUpdateExecuteMinusOne)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OPEN_LINK_IN_NEW_WINDOW, OnOpenLinkInNewWindow)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_COPY_LINK_LOCATION, OnCopyLinkLocation)
	ON_COMMAND(ID_PLAYLIST_EXECUTE_PLAY, OnPlaylistExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_PLAYLIST_EXECUTE_PLAY, OnUpdatePlaylistExecutePlay)
	ON_COMMAND(ID_EXECUTE_PREVIOUS, OnExecutePrevious)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PREVIOUS, OnUpdateExecutePrevious)
	ON_COMMAND(ID_EXECUTE_NEXT, OnExecuteNext)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_NEXT, OnUpdateExecuteNext)
	//}}AFX_MSG_MAP
	// Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
	ON_COMMAND(ID_FILE_PRINT, MediaView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, MediaView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, MediaView::OnFilePrintPreview)
   ON_COMMAND_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnViewEncoding)
   ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnUpdateViewEncoding)
	ON_COMMAND(ID_EXECUTE_AUTO_RECORD, OnExecuteAutoRecord)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_AUTO_RECORD, OnUpdateExecuteAutoRecord)
   */
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView diagnostics

#ifdef _DEBUG
void MusicalPlayerLightView::AssertValid() const
{
	MediaView::AssertValid();
}

void MusicalPlayerLightView::Dump(CDumpContext& dc) const
{
	MediaView::Dump(dc);
}

MusicalPlayerLightDoc* MusicalPlayerLightView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MusicalPlayerLightDoc)));
	return (MusicalPlayerLightDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView message handlers

// vmpLightView.cpp : implementation of the MusicalPlayerLightView class
//


/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView


BOOL MusicalPlayerLightView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style |= WS_CLIPSIBLINGS;
	return MediaView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView printing

BOOL MusicalPlayerLightView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void MusicalPlayerLightView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void MusicalPlayerLightView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void MusicalPlayerLightView::_001OnCancelEditSrvr(gen::signal_object * pobj)
{
//	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView message handlers


CWinThread * MusicalPlayerLightView::GetMidiPlayerCallbackThread()
{
   return &gen::ThreadContainer::AppGetHighThread();
}

MidiSequence & MusicalPlayerLightView::GetMidiSequence()
{
   return GetDocument()->GetMediaViewData()->GetMidiSequence();
}

/*void MusicalPlayerLightView::ExecutePlay(bool bMakeVisible)
{
   MusicalPlayerLightDoc * pdoc = GetDocument();
   if(pdoc->GetMode() == MusicalPlayerLightDoc::ModeWave)
   {
//      aud::CWavePlayer::CCommand command;
  //    command.OpenDevice();
    //  m_pwaveplayer->ExecuteCommand(command);
      //command.Play();
      //m_pwaveplayer->ExecuteCommand(command);
      return;
   }
   
   
   MidiSequence & midisequence = GetMidiSequence();
   ASSERT(&midisequence != NULL);
   
   ikar::KaraokeData & data = GetKaraokeData();
   ikar::KaraokeStaticData & staticdata = data.GetStaticData();
   CKaraokeDynamicData & dynamicdata = data.GetDynamicData();

   if(midisequence.GetState() != MidiSequence::StatusOpened)
   {
      return;
   }
   ASSERT(midisequence.GetState() == MidiSequence::StatusOpened);
/*   if (midisequence.GetState() == MidiSequence::StatusNoFile)
   {
      CString str;
      WString wstr;
      
      int i3 = sizeof(MidiPlayer);
      CString str3;
      str3.Format(_T("sizeof MidiPlayer %d"), i3);
      
      COleVariant var;
      
      while(pplaylistdoc->PeekNextSongPath(wstr))
      {
         International::UnicodeToOEM(str, wstr);
         int i4 = sizeof(MidiPlayer);
         CString str4;
         str4.Format(_T("sizeof MidiPlayer %d"), i4);
         
         var = wstr.AllocSysString();
         
         if(pdoc->OpenDocumentFile(var))
            break;
         UpdateReserveList();
      }
      
   }*/
   
/*   dynamicdata.m_iPlayingTokenIndex = -1;
   dynamicdata.m_iBufferTokenIndex = 0;
   //m_iBufferingTokenIndex = 0;
   //m_iBufferingOffsetTokenIndex = 0;
   //	pApp->SetPlayingDocument(this);
   
   //GetMidiPlayer()->SetMidiOutDevice(CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);
   
   if(GetMidiSequence().GetState() == MidiSequence::StatusOpened)
   {
      pdoc->m_bPlay = true;
      try
      {
         GetMidiSequence().SetSpecialModeV001Operation(MidiSequence::SPMV001GMReset);
         GetMidiPlayer()->Play();
      }
      catch(CMidiException * pe)
      {
         CErrorDialog ed;
         ed.Initialize(pe);
         ed.DoModal();
         pe->Delete();
         return;
      }
      // execution continues in OnMmmsgDone
   }

}*/

void MusicalPlayerLightView::_001OnExecutePlay(gen::signal_object * pobj) 
{
/*xxx   aud::WaveCentral & wavecentral =
	aud::WaveCentralContainer::AppGetAudioWaveCentral();
   aud::WaveIn * pwavein = wavecentral.GetWaveIn();
   if(pwavein == NULL)
   {
      wavecentral.Initialize();
   }
   pwavein = wavecentral.GetWaveIn();
   if(pwavein != NULL)
   {
      pwavein->AddListener(this);
      pwavein->Open(NULL);
   }*/

	_ExecutePlay(true);
}

void MusicalPlayerLightView::_001OnUpdateExecutePlay(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPlayEnable());
}

void MusicalPlayerLightView::_001OnPlaylistExecutePlay(gen::signal_object * pobj) 
{
	_ExecutePlay(true);
}

void MusicalPlayerLightView::_001OnUpdatePlaylistExecutePlay(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPlayEnable());
}


void MusicalPlayerLightView::_001OnExecuteStop(gen::signal_object * pobj) 
{
   StartFadeOut(ExecuteStop, ExecuteNone);
}

/*void MusicalPlayerLightView::ExecuteStop()
{
   MusicalPlayerLightDoc * pdoc = GetDocument();
   switch(pdoc->GetMode())
   {
   case MusicalPlayerLightDoc::ModeMidi:
      {
         if(ExecuteIsWaitingToPlay())
         {
//            SetWaitingToPlay(false);
            m_bWaitingToPlay = false;
         }
         else
         {
            //CVmpApp *pApp = (CVmpApp *) AfxGetApp();
            //ASSERT(pApp != NULL);	
            //CWaveIn * pWaveIn = pApp->GetWaveIn();
            //m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_STOP, 0, 0);
            m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_COMMAND, m_pmidiplayer->CommandStop, 0);
         }
      }
   break;
   case MusicalPlayerLightDoc::ModeWave:
      {
//         aud::CWavePlayer::CCommand command;
  //       command.Stop();
    //     m_pwaveplayer->ExecuteCommand(command);
      //   command.CloseDevice();
        // m_pwaveplayer->ExecuteCommand(command);
      }
      break;
   default:
      ASSERT(FALSE);
      break;
   }
}*/



void MusicalPlayerLightView::_001OnUpdateExecuteStop(gen::signal_object * pobj) 
{
   /*bool bEnable = false;
   MusicalPlayerLightDoc * pdoc = GetDocument();
   switch(pdoc->GetMediaViewData()->GetMode())
   {
   case mediaplay::MediaViewData::ModeMidi:
      {
         bEnable = GetMidiPlayer() &&
               (GetMidiSequence().GetState() == MidiSequence::StatusPaused ||
               GetMidiSequence().GetState() == MidiSequence::StatusPlaying ||
               ExecuteIsWaitingToPlay());
         break;
      }
   case mediaplay::MediaViewData::ModeWave:
      {
//         bEnable = m_pwaveplayer != NULL
  //          && m_pwaveplayer->IsPlaying();
         break;
      }
   }*/
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)

   pupdatecmdui->m_pcmdui->Enable(_ExecuteGetStopEnable());
}

void MusicalPlayerLightView::_001OnExecutePause(gen::signal_object * pobj) 
{
	_ExecutePause();
}

/*void MusicalPlayerLightView::ExecutePause()
{
   GetMidiPlayer()->Pause();
}*/

void MusicalPlayerLightView::_001OnUpdateExecutePause(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPauseEnable());
   pupdatecmdui->m_pcmdui->SetCheck(_ExecuteIsPaused() ? 1 : 0);
}

/*bool MusicalPlayerLightView::ExecuteIsPaused()
{
   return GetMidiPlayer() &&
      GetMidiSequence().GetState() == MidiSequence::StatusPaused;
}

bool MusicalPlayerLightView::ExecuteGetPauseEnable()
{
   switch(GetDocument()->GetMode())
   {
   case MusicalPlayerLightDoc::ModeNone:
      {
         return false;
      }
   case MusicalPlayerLightDoc::ModeMidi:
      {
         MidiSequence::Status  estatus = (MidiSequence::Status) GetMidiSequence().GetState();
	      return estatus == MidiSequence::StatusPaused ||
		      estatus == MidiSequence::StatusPlaying;
      }
   case MusicalPlayerLightDoc::ModeWave:
      {
         return false;
      }
   default:
      ASSERT(FALSE);
      return false;
   }
}


bool MusicalPlayerLightView::ExecuteGetPlayEnable()
{
   MusicalPlayerLightDoc * pdoc = GetDocument();
   switch(pdoc->GetMode())
   {
   case MusicalPlayerLightDoc::ModeNone:
      return false;
   case MusicalPlayerLightDoc::ModeMidi:
      return GetMidiPlayer()
         && (pdoc->GetMidiSequence().GetState() == MidiSequence::StatusOpened)
         && !ExecuteIsWaitingToPlay();
   case MusicalPlayerLightDoc::ModeWave:
//      return m_pwaveplayer->DecoderIsOpened()
//         && ! m_pwaveplayer->IsPlaying();
   default:
      ASSERT(FALSE);
      return false;
   }
}


void MusicalPlayerLightView::ExecuteListenMinusOne(bool bMinusOne)
{
   ikar::KaraokeData & data = GetKaraokeData();
   MidiPlayer * pplayer = GetMidiPlayer();
   MidiSequence & sequence = pplayer->GetSequence();
   CMidiFile & file = sequence.GetFile();
   int iTrack = data.GetStaticData().GetGuessMelodyTrack();
   file.MuteTrack(
      iTrack,
      bMinusOne);
   //DBListenMinusOne(true, pdoc->GetPathName(), bMinusOne);
   
}

void MusicalPlayerLightView::ExecuteToggleListenMinusOne()
{
   ikar::KaraokeData & data = GetKaraokeData();
   ASSERT(ExecuteGetListenMinusOneEnable());
   if(ExecuteGetListenMinusOneEnable())
   {
      MidiPlayer * pplayer = GetMidiPlayer();
      MidiSequence & sequence = pplayer->GetSequence();
      CMidiFile & file = sequence.GetFile();
      CMidiTracks & tracks = file.GetTracks();
      int iTrack = data.GetStaticData().GetGuessMelodyTrack();
      bool bMute = file.IsTrackMute(iTrack);
      ExecuteListenMinusOne(!bMute);
   }
}


bool MusicalPlayerLightView::ExecuteGetListenMinusOneEnable()
{
   bool bEnable = GetMidiPlayer() != NULL
      && (GetMidiSequence().GetState() == MidiSequence::StatusOpened
      || GetMidiSequence().GetState() == MidiSequence::StatusPlaying);
   return bEnable;
   
}

int MusicalPlayerLightView::GetListenMinusOneCheck()
{
   if(ExecuteGetListenMinusOneEnable())
   {
      return GetMidiPlayer()->GetSequence().GetFile().IsTrackMute(
         GetKaraokeData().GetStaticData().GetGuessMelodyTrack()) ? 1 : 0;
   }
   else
      return 0;
}*/



void MusicalPlayerLightView::OnMidiPlayerNotifyEvent(midi::player::NotifyEvent * pdata)
{
   MediaView::OnMidiPlayerNotifyEvent(pdata);
   MidiSequence & seq = pdata->m_pplayer->GetSequence();
   ASSERT(&seq == &GetMidiSequence());
   MusicalPlayerLightDoc * pdoc = GetDocument();
   
   if(pdata->m_enotifyevent
   == midi::player::NotifyEventPositionSet)
   {
//      OnProgressRateChange(); TODO
   }

//   CVmpApp * papp = (CVmpApp *) AfxGetApp();
//   ASSERT(papp != NULL);
   
   
//   CWinThread * pThreadV2  = papp->GetThreadV2();
//   ASSERT(pThreadV2 != NULL);
   
//   aud::CWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
//   ASSERT(pwavein != NULL);
   if(pdata->m_enotifyevent == midi::player::NotifyEventGenericMmsgDone
      && pdoc->m_bPlay)
   {
      
//      double dRate =	GetProgressSlider()->GetRate();
  
      //if(dRate == 0.0)
      {
         //Show Title
  //       ShowTitle();
         
         // Time to let the title be visible
    //     m_msPlayTimeOut = timeGetTime() + 3000;
         
         //	    Sleep(3000);
      }
//      else
      {
//         m_msPlayTimeOut = timeGetTime();
      }
      m_bWaitingToPlay = true;
      pdoc->m_bPlay = false;
   }
   //	else if(lpmdd->SequenceWasInSpecialModeV001())
   //  {
   //    TRACE(_T("MusicalPlayerLightDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n"));
   //}
//   else if(ExecuteIsSettingNextSong())
  /* {
      TRACE(_T("MusicalPlayerLightDoc::OnMmsgDone IsSettingNextSong()\n"));
      ((CXfplayerThreadV2*)pThreadV2)->EnableWaveInMessageTranslation(false);
      if(pwavein->IsRecording())
      {
         pwavein->Reset();
      }
      seq.CloseFile();
      m_dProgressRate = 0.0;
      ExecutePlay(true);
      m_bSettingNextSong = false;
   }*/
   else if(pdata->m_enotifyevent
      == midi::player::NotifyEventPlaybackEnd)
   {
      //OnMediaPlaybackEnd();
      TRACE(_T("MusicalPlayerLightView::OnMmsgDone NotifyEventPlaybackEnd \n"));
   }
   else if(pdata->m_enotifyevent
      == midi::player::NotifyEventStop)
   {
      TRACE(_T("MusicalPlayerLightView::OnMmsgDone Else if Stopping\n"));
//      pdoc->StartScoring(false);
  //    m_dProgressRate = 0.0;
    //  CXfplayerViewUpdateHint uh;
      //uh.AddType(CXfplayerViewUpdateHint::TypeProgressRateChange);
      //pdoc->UpdateAllViews(NULL, 0, &uh);
      
   }
   else 
   {
      int i = 0;
      i++;
   }
//   pdoc->OnMidiPlayerNotifyEvent(pdata);
   
}



void MusicalPlayerLightView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
	MediaView::_001OnInitialUpdate(pobj);
}


void MusicalPlayerLightView::OnMidiLyricEvent(BaseArray<LyricEventV1, LyricEventV1&> * pevents)
{
   BaseRectArray recta;
   for(int i = 0; i < pevents->GetSize(); i++)
   {
      OnLyricEvent(&pevents->ElementAt(i), true, recta);
   }
}


/*VMSRESULT MusicalPlayerLightView::UpdateScreen(BaseRectArray & recta)
{
   if(recta.GetSize() > 0)
   {
      CRect rect;
      recta.GetArrayBox(rect);
      if(!rect.IsRectEmpty())
      {
         RedrawWindow(rect);
      }
   }
   return 0;
}*/
CWnd * MusicalPlayerLightView::KaraokeGetWnd()
{
   return this;
}

void MusicalPlayerLightView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* phint) 
{
	if(lHint == 1000)
   {
	   DBCentral *pDataCentral = (DBCentral *) DB();
	   DBLongSet *pSet = pDataCentral->GetDBLongSet();
      if(!VmsDataGet(VMSDATAKEY(GlobalLyricsDelay), 0, 0, m_iDelay))
         m_iDelay = 0;
   }

   MediaView::OnUpdate(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(CVmpLightViewUpdateHint)))
      {
         CVmpLightViewUpdateHint * puh = (CVmpLightViewUpdateHint * ) phint;
         if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeAttachPlaylist)
            && puh->m_pplaylistdoc != NULL)
         {
            puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
            m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeGetPlaylistCallback))
         {
            puh->m_pplaylistcallback = m_pplaylistcallback;
         }
      }
      else if(phint->IsKindOf(RUNTIME_CLASS(PaneViewUpdateHint)))
      {
         PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
         if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnShowKaraoke))
         {
            ((BaseFrameWnd *) GetTopLevelFrame())->SetActiveView(this);
         }
         else if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnShowView))
         {
            int iTab;
            if(puh->m_eview == PaneViewContextMenu)
            {
               m_tab._001AddSel(0);
            }
            else
            {
               switch(puh->m_eview)
               {
               case PaneViewKaraoke:
                  iTab = 1;
                  break;
               case PaneViewFileManager:
                  iTab = 2;
                  break;
               case PaneViewPlaylist:
                  iTab = 3;
                  break;
               case PaneViewMediaLibrary:
                  iTab = 4;
                  break;
               case PaneViewAudioControl:
                  iTab = 6;
                  break;
               case PaneViewOptions:
                  iTab = 5;
                  break;
               }
               m_tab._001SetSel(iTab);
            }
            
         }
      }
      else if(phint->IsKindOf(RUNTIME_CLASS(MediaViewUpdateHint)))
      {
         MediaViewUpdateHint * puh = (MediaViewUpdateHint * ) phint;
         if(puh->IsTypeOf(MediaViewUpdateHint::TypeAfterOpenDocument))
         {
            m_bOverrideKaraokeCodePage = true;

            WString wstrKey;
            wstrKey = GetDocument()->GetPathName();
            wstrKey += L".OverrideKaraokeCodePage";
            
            WString wstrValue;
            DB()->WStrToWStr().GetDirect(wstrValue, wstrKey);
            if(wstrKey ==  L"True")
            {
               m_bFileOverrideKaraokeCodePage = true;
      
               wstrKey = GetDocument()->GetPathName();
               wstrKey += L".OverridingKaraokeCodePage";

               DB()->WStrToWStr().GetDirect(wstrValue, wstrKey);

               m_dwFileOverrideKaraokeCodePage = (DWORD) wcstod(wstrKey, NULL);

            }
            else
            {
               m_bFileOverrideKaraokeCodePage = false;
            }
         }
      }
   }


/*	if(lHint == 1000)
   {

      PrepareLyricLines();
      m_lpbouncingball->SetQuarterNoteDuration(
          GetMidiSequence().GetFile().m_pFileHeader->GetQuarterNoteTicks());

   }

   if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(CVmpLightViewUpdateHint)))
      {
         CVmpLightViewUpdateHint * puh = (CVmpLightViewUpdateHint * ) phint;
         if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeDoPlay))
         {
            ExecutePlay(true);
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypePlayIfNotPlaying))
         {
            if(!GetMidiSequence().IsPlaying())
            {
               ExecutePlay(true);
            }
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeGetMidiPlayerInterface)
            && puh->m_pmidiplayer == NULL)
         {
            puh->m_pmidiplayer = this;
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeAttachPlaylist)
            && puh->m_pplaylistdoc != NULL)
         {
            puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
            m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeFullScreen))
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
      }
   }*/
	
	
}

/*CWnd & MusicalPlayerLightView::BackViewGetWnd()
{
   return *this;
}

void MusicalPlayerLightView::BackViewUpdateScreen(LPCRECT lpcrect)
{
   RedrawWindow(lpcrect);
}

void MusicalPlayerLightView::BackViewUpdateScreen()
{
   RedrawWindow();
}

void MusicalPlayerLightView::BackViewGetData(
   gcom::backview::CInterfaceData & data)
{

   if(data.IsSignalized(gcom::backview::InterfaceDataNextImagePath))
   {
      DBCentral * pdb = DB();
      CString str;
      DILoad(_T("Images.CurrentPath"), str);
      WString wstrCurrentImagePath;
      wstrCurrentImagePath.SetOEM(str);
      data.m_wstrNextImagePath = pdb->GetNextImagePath(wstrCurrentImagePath);
   //   data.m_wstrNextImagePath = L"C:\\camilo.jpg";
   }
   if(data.IsSignalized(gcom::backview::InterfaceDataEnhancedMetaFile))
   {
//      data.m_henhmetafile = m_enhmetafile;
      data.m_henhmetafile = NULL;
   }

}

void MusicalPlayerLightView::BackViewSetData(
   gcom::backview::CInterfaceData & data)
{

   if(data.IsSignalized(gcom::backview::InterfaceDataCurrentImagePath))
   {
      DBCentral * pdb = DB();
      CString str;
      International::UnicodeToACP(
         str,
         data.m_wstrCurrentImagePath);
      DISave(_T("Images.CurrentPath"), str);
   }

}

bool MusicalPlayerLightView::BackViewGetDestroy()
{
   return m_bDestroy; 
}*/

/*bool MusicalPlayerLightView::BackViewIsFullScreen()
{
   return false; // TODO
}*/

void MusicalPlayerLightView::_001OnDestroy(gen::signal_object * pobj) 
{
	MediaView::OnDestroy();
	
   m_pplaylistcallback->OnClosePlayer();
   delete m_pplaylistcallback;
   m_pplaylistcallback = NULL;
   m_bDestroy = true;	
}



void MusicalPlayerLightView::_001OnSize(gen::signal_object * pobj) 
{
   pobj->previous();
	//MediaView::_001OnSize(nType, cx, cy);
	
/*   if(m_dcBuffer.GetSafeHdc() != NULL)
   {
      m_dcBuffer.SelectObject(m_pbmpBufferOld);
      m_dcBuffer.DeleteDC();
   }

   if(m_bmpBuffer.GetSafeHandle() != NULL)
   {
      m_bmpBuffer.DeleteObject();
   }

   CDC * pdc = GetDC();

   m_dcBuffer.CreateCompatibleDC(pdc);
   m_bmpBuffer.CreateCompatibleBitmap(pdc, cx, cy);
   m_pbmpBufferOld = m_dcBuffer.SelectObject(&m_bmpBuffer);
   
   ReleaseDC(pdc);*/

   /*double d = cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   SIZE sz;
   sz.cx = d * 24;
   sz.cy = d * 24;
   m_lpbouncingball->SetBallSize(sz);

   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();*/
}

void MusicalPlayerLightView::_001OnPaint(gen::signal_object * pobj) 
{
	CPaintDC dc(this); // device context for painting

   _001OnDraw(&dc);
}


/*void MusicalPlayerLightView::_001OnDraw(CDC * pdcScreen)
{
	CDocument* pDoc = GetDocument();


   CSingleLock sl(m_gdibuffer.GetSemaphore());
   CDC * pdc = m_gdibuffer.GetBuffer();

   int count = 0;


   MidiSequence & seq = GetMidiSequence();
   CMidiFile & file = seq.GetFile();


   ikar::KaraokeData & data = GetKaraokeData();
   if(data.IsNull())
   {
      return;
   }
   CKaraokeDynamicData & dynamicdata = data.GetDynamicData();
   ikar::KaraokeStaticData & staticdata = data.GetStaticData();

   CRect rectClient;
   GetClientRect(rectClient);
   int cx = rectClient.Width();
   int cy = rectClient.Height();

   

   CRect rectClip;

   pdcScreen->GetClipBox(rectClip);
   
   if(rectClip.IsRectNull())
   {
      GetClientRect(rectClip);
      pdc->SelectClipRgn(NULL);
   }
   else
   {
      CRgn rgnClip;
      CRect rect(rectClip);
      rect.OffsetRect(pdc->GetViewportOrg());
      rgnClip.CreateRectRgnIndirect(rect);
      pdc->SelectClipRgn(&rgnClip);
//      TRACE("_ONDRAW (%d, %d)\n", rectClip.Width(), rectClip.Height());
      ASSERT(TRUE);
   }

   // Back View Drawing
   {
      gcom::backview::CInterface & backview = BackViewGetInterface();
      CSingleLock slTransfer(&backview.GetTransferCS(), false);
      slTransfer.Lock();
      pdc->BitBlt(
         rectClip.left, rectClip.top,
         rectClip.Width(), rectClip.Height(),
         &backview.GetTransferDC(),
         rectClip.left, rectClip.top,
         SRCCOPY);
      slTransfer.Unlock();
   }

   gdi::CWinGdi gdi;
   gdi.m_dc.Attach(pdc->GetSafeHdc());
   KaraokeRender(&gdi);
   gdi.m_dc.Detach();
   //_001DrawChildren(pdc);

   pdcScreen->BitBlt(
      rectClip.left,
      rectClip.top,
      rectClip.Width(),
      rectClip.Height(),
      pdc,
      rectClip.left,
      rectClip.top,
      SRCCOPY);

   
}*/

void MusicalPlayerLightView::_001OnKaraokeBouncingBall(gen::signal_object * pobj) 
{
   if(!m_bBouncingBall)
   {
      m_bBouncingBall = true;
      PrepareLyricLines();
      PrepareLyricTemplateLines();
   }
   else
   {
      m_bBouncingBall = false;
      PrepareLyricLines();
      PrepareLyricTemplateLines();
   }
   RedrawWindow();
   DISave("BouncingBall", m_bBouncingBall ? 1 : 0);	
}

void MusicalPlayerLightView::_001OnUpdateKaraokeBouncingBall(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable();
   pupdatecmdui->m_pcmdui->SetCheck(m_bBouncingBall ? 1: 0);
	
}

void MusicalPlayerLightView::_001OnKaraokeGradualFilling(gen::signal_object * pobj) 
{
   if(!m_bGradualFilling)
   {
      m_bGradualFilling = true;
      PrepareLyricLines();
      PrepareLyricTemplateLines();
   }
   else
   {
      m_bGradualFilling = false;
      PrepareLyricLines();
      PrepareLyricTemplateLines();
   }
   RedrawWindow();
   DISave("GradualFilling", m_bGradualFilling ? 1 : 0);	
}

void MusicalPlayerLightView::_001OnUpdateKaraokeGradualFilling(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)

	pupdatecmdui->m_pcmdui->Enable();
   pupdatecmdui->m_pcmdui->SetCheck(m_bGradualFilling ? 1: 0);
	
}



void MusicalPlayerLightView::_001OnExecuteMinusOne(gen::signal_object * pobj) 
{
	_ExecuteToggleListenMinusOne();
}

void MusicalPlayerLightView::_001OnUpdateExecuteMinusOne(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)

   pupdatecmdui->m_pcmdui->Enable(_ExecuteGetListenMinusOneEnable());
   pupdatecmdui->m_pcmdui->SetCheck(GetListenMinusOneCheck());
}



void MusicalPlayerLightView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   m_audiospectrum.Create(this, &m_basecontrol, 1);


   m_audiospectrum.SetWindowPos(NULL, 0,  75, 150, 75, 0);


   m_pplaylistcallback = new MusicalPlayerLightPlaylistCallback(
      &musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(),
      GetDocument());

   SetTimer(gen::Timer::ID_HOVER, 100, NULL);

//   m_tab.SetCreateInterface(this);
   m_tab.Create(&m_basecontrol, 100, 0);

   m_tab.AddIconTab(IDS_KARAOKEVIEW_TAB_MENU, IDI_CONTEXT_MENU);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_KARAOKE);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_OPEN);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_PLAYLIST);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_ALBUM);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_OPTIONS);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_AUDIOCONTROL);

   m_tab._001SetSel(1);

   m_tab.m_pcallback = this;



   m_gdi.m_dc.Attach(GetDC()->GetSafeHdc());
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

   int i;
   if(DILoad("GradualFilling", i))
   {
      m_bGradualFilling = i != 0;
   }
   if(DILoad("BouncingBall", i))
   {
      m_bBouncingBall = i != 0;
   }
   bool bListenMinusOne;
   CString str;
   International::UnicodeToACP(str, GetMediaViewData()->GetPathName());
   if(DBListenMinusOne(false, GetMediaViewData()->GetPathName(), bListenMinusOne))
   {
     _ExecuteListenMinusOne(bListenMinusOne);
   }

   MusicalPlayerLightDoc * pdoc = GetDocument();
   SetKaraokeData(&pdoc->GetMediaViewData()->GetKaraokeData());
   m_lpbouncingball->SetKaraokeData(&pdoc->GetMediaViewData()->GetKaraokeData());

   if(GetMidiPlayer() == NULL)
      if(!OpenMidiPlayer())
      {
         ASSERT(FALSE);
         throw 0;
      }

   //SetTimer(0, 50, NULL);

   m_lyrictemplatelines.RemoveAll();
   m_lyrictemplatelines.SetSize(4);

   PrepareLyricTemplateLines();

/*   aud::WaveCentral & wavecentral =
	aud::WaveCentralContainer::AppGetAudioWaveCentral();
   aud::WaveIn * pwavein = wavecentral.GetWaveIn();

   pwavein->Start();*/

}

int MusicalPlayerLightView::InitGL()
{
/*	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
	glEnable(GL_LIGHTING);								// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);						// Enable Coloring Of Material

	BuildFont();										// Build The Font*/

	return TRUE;										// Initialization Went OK

}

gdi::Gdi * MusicalPlayerLightView::GetGdi()
{
   return &m_gdi;
}

void MusicalPlayerLightView::_001OnContextMenu(gen::signal_object * pobj) 
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
      if (menu.LoadMenu(IDR_POPUP_LYRICVIEW_LINK))
      {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         CFrameWnd * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }
   }
   else if(m_plinesTitle->HitTest(ptCursor, iLine, iChar)
      == igui::LineHitTestLink)
   {
      WString wstr;
      m_plinesTitle->ElementAt(iLine).GetCharLink(wstr, iChar);
      m_wstrCurrentLink = wstr;
      SimpleMenu menu(BaseMenuCentral::GetMenuCentral());
      if (menu.LoadMenu(IDR_POPUP_LYRICVIEW_LINK))
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
      BaseWndMenu menu;
      if(menu.LoadMenu(IDR_POPUP_LYRICVIEW))
      {
         BaseWndMenu menuPopup(menu.GetSubMenu(0));
         CFrameWnd * pframe = GetParentFrame();
         menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (CWnd *) pframe);
      }

      /*
      PaneViewUpdateHint uh;
      uh.SetType(PaneViewUpdateHint::TypeSetView);
      uh.m_eview = PaneViewContextMenu;
      GetDocument()->UpdateAllViews(this, 0, &uh);
      */
   }
	
}

PlaylistCallbackInterface * MusicalPlayerLightView::GetPlaylistCallback()
{
   return m_pplaylistcallback;
}


void MusicalPlayerLightView::_001OnTabClick(int iTab)
{
   PaneView * pview = GetParentPane();
   
   if(pview != NULL)
   {
      EPaneView eview = PaneViewNone;
      switch(iTab)
      {
      case 0:
         eview = PaneViewContextMenu;
         break;
      case 1:
         eview = PaneViewKaraoke;
         break;
      case 2:
         eview = PaneViewFileManager;
         break;
      case 3:
         eview = PaneViewPlaylist;
         break;
      case 4:
         eview = PaneViewMediaLibrary;
         break;
      case 5:
         eview = PaneViewOptions;
         break;
      case 6:
         eview = PaneViewAudioControl;
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      pview->ShowView(eview);
   }
}


void MusicalPlayerLightView::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
   DWORD dwCodePage = papp->CommandToCodePage(pupdatecmdui->m_pcmdui->m_nID);
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
void MusicalPlayerLightView::_001OnViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::command, pcommand, pobj)
   DWORD dwCodePage = CommandToCodePage(pcommand->GetId());
   SetKaraokeCodePage(dwCodePage, true);
}

DWORD MusicalPlayerLightView::CommandToCodePage(UINT uiID)
{
   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
   return papp->CommandToCodePage(uiID);
}

void MusicalPlayerLightView::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
   if(key == VMSDATAKEY(KaraokeEncoding))
   {
      PrepareLyricLines();
      RedrawWindow();
   }
   else if(key == VMSDATAKEY(GlobalLyricsDelay))
   {     
      VmsDataGet(VMSDATAKEY(GlobalLyricsDelay), 0, 0, m_iDelay);
   }
   else if(key == VMSDATAKEY(ImageDirectorySet))
   {
      BackViewGetInterface().ImageChangePostEvent(gcom::backview::EventLoadNow);
   }
}

bool MusicalPlayerLightView::KaraokeDoesOverrideCodePage()
{
   return m_bOverrideKaraokeCodePage ||
      m_bFileOverrideKaraokeCodePage;
}

DWORD MusicalPlayerLightView::KaraokeGetOverridingCodePage(LPCSTR lpsz)
{
	DWORD dwCodePage;

   if(m_bFileOverrideKaraokeCodePage)
   {
      if(77777 == m_dwFileOverrideKaraokeCodePage)
      {
         dwCodePage = LibCharGuess::GuessCodePage(lpsz);
            if(dwCodePage == 0)
               return 1251;
            else
               return dwCodePage;
/*         if(dwCodePage == 0)
         {
            CString str;
            W
            str = GetKaraokeData().GetStaticData().GetLyrics();
            dwCodePage = LibCharGuess::GuessCodePage(str);
            if(dwCodePage == 0)
               return 1251;
            else
               return dwCodePage;
         }
         else
         {
            return dwCodePage;
         }*/
      }
      else
      {
		   return m_dwFileOverrideKaraokeCodePage;
      }
   }

  	VmsDataServerInterface & db = *((MusicalPlayerLightApp *) AfxGetApp())->GetDataServer();

   gen::Variable var;

	//if(db.GetData(_vmsp::CConfiguration::CfgKaraokeEncoding, GetLanguage(), 0, var))
   if(db.GetData(
      VMSDATAKEY(KaraokeEncoding), 
      0,
      0,
      var))
	{
      ASSERT(var.GetType() == gen::VariableInteger);
		dwCodePage = var.m_i;
      if(dwCodePage == 77777)
      {
         dwCodePage = LibCharGuess::GuessCodePage(lpsz);
    
         if(dwCodePage == 0)
            return 1251;
         else
            return dwCodePage;

      }
      else
      {
		   return dwCodePage;
      }
	}
	else
		return CP_OEMCP;

}


void MusicalPlayerLightView::SetKaraokeCodePage(DWORD dw, bool bOverride)
{
  	VmsDataServerInterface & db = *((MusicalPlayerLightApp *) AfxGetApp())->GetDataServer();

   gen::Variable var;
   var.ChangeType(gen::VariableInteger);
   var.m_i = dw;

   if(!GetDocument()->GetPathName().IsEmpty())
   {
      m_bFileOverrideKaraokeCodePage = true;
      m_dwFileOverrideKaraokeCodePage = dw;
   }
   else
   {
      m_bOverrideKaraokeCodePage = true;
   }

/*   db.SetData(
      _vmsp::CConfiguration::CfgKaraokeEncoding,
      GetLanguage(), 
      0,
      var);*/
   db.SetData(
      VMSDATAKEY(KaraokeEncoding),
      0, 
      0,
      var);

}

WndRenderInterface * MusicalPlayerLightView::KaraokeGetWndRender()
{
   return &m_wndrender;
}


LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{

 

    HKEY hkey;

 

    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

 

 

 

    if (retval == ERROR_SUCCESS) {

 

        long datasize = MAX_PATH;

 

        TCHAR data[MAX_PATH];

 

        RegQueryValue(hkey, NULL, data, &datasize);

 

        lstrcpy(retdata,data);

 

        RegCloseKey(hkey);

 

    }

 

 

 

    return retval;

 

}

 

 

void URLOpenNew(LPCTSTR lpcsz)

{

   TCHAR key1[MAX_PATH + MAX_PATH];
   TCHAR key2[MAX_PATH + MAX_PATH];
   TCHAR key3[MAX_PATH + MAX_PATH];

   if(GetRegKey(HKEY_CLASSES_ROOT, _T(".html"), key1) != ERROR_SUCCESS)
      if(GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key1) != ERROR_SUCCESS)
         return;

   lstrcpy(key2, key1);
   lstrcat(key2, _T("\\shell\\opennew\\command"));

   if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
   {
      lstrcpy(key2, key1);
      lstrcat(key2, _T("\\shell\\open\\command"));
      if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
      {
         return;
      }
   }

   CString str(key3);

   str.Replace("%1", lpcsz);

   WinExec(str,SW_SHOW);

        
}

void MusicalPlayerLightView::_001OnOpenLinkInNewWindow(gen::signal_object * pobj) 
{
   ASSERT(!m_wstrCurrentLink.IsEmpty());	
   CString str;
   International::UnicodeToACP(str, m_wstrCurrentLink);
   //::ShellExecute(m_hWnd, _T("opennew"), str, NULL, NULL, SW_RESTORE);
   URLOpenNew(str);
	
}

void MusicalPlayerLightView::OnLinkClick(WString &wstrLink)
{
   ASSERT(!wstrLink.IsEmpty());	
   CString str;
   International::UnicodeToACP(str, wstrLink);
   ::ShellExecute(m_hWnd, _T("open"), str, NULL, NULL, SW_RESTORE);
}

void MusicalPlayerLightView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}

HCURSOR MusicalPlayerLightView::KaraokeGetHandCursor()
{
   return AfxGetApp()->LoadCursor(IDC_HAND_POINTER);
}

void MusicalPlayerLightView::_001OnCopyLinkLocation(gen::signal_object * pobj) 
{
   if (!OpenClipboard())
   {
      AfxMessageBox( "Cannot open the Clipboard" );
      return;
   }
   
   // Remove the current Clipboard contents
   if(!EmptyClipboard())
   {
      AfxMessageBox( "Cannot empty the Clipboard" );
      CloseClipboard();
      return;
   }
   CString str;
   International::UnicodeToACP(str, m_wstrCurrentLink);

   HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 
            (str.GetLength() + 1) * sizeof(TCHAR)); 
        if (hglbCopy == NULL) 
        { 
            CloseClipboard(); 
            return; 
        } 
 
        // Lock the handle and copy the text to the buffer. 
 
        LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy); 
        memcpy(lptstrCopy, (LPCTSTR) str, 
            str.GetLength() * sizeof(TCHAR)); 
        lptstrCopy[str.GetLength()] = (TCHAR) 0;    // null character 
        GlobalUnlock(hglbCopy); 
   // ...
   // Get the currently selected data
   // ...
   // For the appropriate data formats...
   if ( ::SetClipboardData( CF_TEXT, hglbCopy ) == NULL )
   {
      AfxMessageBox( "Unable to set Clipboard data" );
      CloseClipboard();
      return;
   }
   // ...
   CloseClipboard();	
}

int MusicalPlayerLightView::KaraokeGetLyricsDelay()
{
   return m_iDelay;
}

Ex1VirtualGuieContainer * MusicalPlayerLightView::Create(int i)
{
   if(i == 1)
   {
      PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) AfxGetApp())->GetPlaylistCentral().GetCurrentPlaylist(true, true);
      if(pdoc != NULL)
      {
         POSITION pos = pdoc->GetFirstViewPosition();
         BaseView * pview = pdoc->GetNextView(pos);
         return dynamic_cast < Ex1VirtualGuieContainer * > (pview);
      }
   }
   return NULL;
}

PaneView * MusicalPlayerLightView::GetParentPane()
{
   CWnd * pwnd = GetParent();
   if(pwnd->IsKindOf(RUNTIME_CLASS(PaneView)))
   {
      return dynamic_cast < PaneView * > (pwnd);
   }
   return NULL;
}

void MusicalPlayerLightView::OnMediaPlaybackStart()
{
   CFrameWnd * pframewnd = GetTopLevelFrame();

   if(pframewnd->IsKindOf(RUNTIME_CLASS(MainFrame)))
   {
      MainFrame * pframe = (MainFrame *) pframewnd;
      pframe->SetAnimatedStatusBarText(GetMediaViewData()->GetAnimatedTitle());
      
   }

   //WString wstr;
   //wstr.SetACP(GetDocument()->GetPathName());
   mediamanager::GetMediaManager()->OnOpenDocumentFile(GetDocument()->GetPathName());

   MediaView::OnMediaPlaybackStart();
}

bool MusicalPlayerLightView::OnExecuteBeforePlay()
{
   PaneView * pview = GetParentPane();
   if(pview != NULL)
   {
      pview->ShowView(PaneViewKaraoke);
   }
   return true;
}

void MusicalPlayerLightView::OnMediaPlaybackEnd()
{
   StartFadeOut(ExecuteNone, ExecuteNext);
}


void MusicalPlayerLightView::WaveInDataProc(
   aud::WaveIn * pwavein,
   DWORD dwSampleTime, 
   LPWAVEHDR lpwavehdr)
{
	ASSERT(lpwavehdr != NULL);
	
   CCriticalSection & csHandle = pwavein->GetHandleCriticalSection();
     

   ikar::KaraokeData & data = GetKaraokeData();
   ikar::KaraokeInterface * pinterface = data.GetInterface();

   ikar::KaraokeStaticData & staticdata = data.GetStaticData();

   
	aud::WaveBuffer & buffer = pwavein->GetBuffer();
	buffer.FFTProcess(lpwavehdr);

//	DWORD msPosition;
//	DWORD dwPositionTime;
//   ikar::CPosition tkPosition;
//	pinterface->GetPosition(tkPosition);
//	dwPositionTime = timeGetTime();
//	msPosition = pinterface->PositionToTime(tkPosition);
//	msPosition -= dwPositionTime - dwSampleTime;

	// Valor de Correção
//	msPosition -= 100;
	
/*	double dDeltaScore = -100.0;
	CEventsTracksV1 * peventsa = &staticdata.m_eventsTracksForScoring;
	CLyricEventsV2 * pevents;
   if(staticdata.m_str2aRawTokens.GetSize() <= 0)
		pevents = NULL;
	else if(peventsa->GetSize() < staticdata.m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		//pEvents = (CLyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->GetSize());
		pevents = (CLyricEventsV2 *) peventsa->operator [](0);
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}
		
	if(pevents != NULL)
	{
		int i;
		m_iaNotes.RemoveAll();
		pevents->GetMillisIntervalNotes(
			m_iaNotes,
			msPosition  - pwavein->GetAnalysisMillis() - 100,
			msPosition);
		dDeltaScore = 0;
		CDWordArray dwaNotes;
		for(i = 0; i < m_iaNotes.GetSize(); i++)
		{
			dwaNotes.Add(pevents->GetNotePitch(m_iaNotes.ElementAt(i)));
		}
      ikar::CTime timeLength;
      pinterface->GetTimeLength(timeLength);
		Process(&dwaNotes, (double) msPosition / timeLength, &dDeltaScore );
	}*/


}


CString MusicalPlayerLightView::GetNextBackgroundImagePath()
{
   VmpLightDB * plightdb = VmpLightDB::GetLightDB();
   CString wstrCurrentImagePath;
   VmsDataGet(VMSDATAKEY(NextBackgroundImagePath), 0, 0, wstrCurrentImagePath);
   return plightdb->GetNextImagePath(wstrCurrentImagePath);
}

void MusicalPlayerLightView::SetCurrentBackgroundImagePath(CString &wstr)
{
   VmsDataSet(VMSDATAKEY(NextBackgroundImagePath), 0, 0, wstr);
}


void MusicalPlayerLightView::_001OnExecutePrevious(gen::signal_object * pobj) 
{
   StartFadeOut(ExecuteStop, ExecutePrevious);
}

void MusicalPlayerLightView::_001OnUpdateExecutePrevious(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable(true);
}

void MusicalPlayerLightView::_001OnExecuteNext(gen::signal_object * pobj) 
{
   StartFadeOut(ExecuteStop, ExecuteNext);
}

void MusicalPlayerLightView::_001OnUpdateExecuteNext(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
	pupdatecmdui->m_pcmdui->Enable(true);
}

void MusicalPlayerLightView::_001OnExecuteAutoRecord(gen::signal_object * pobj)
{  
   _ToggleAutoRecord();
}

void MusicalPlayerLightView::_001OnUpdateExecuteAutoRecord(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable();
   pupdatecmdui->m_pcmdui->SetCheck(m_bAutoRecord ? 1 : 0);
}
