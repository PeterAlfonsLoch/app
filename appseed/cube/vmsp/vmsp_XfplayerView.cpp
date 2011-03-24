#include "StdAfx.h"
#include "XfplayerDoc.h"
#include "XfplayerView.h"
#include "XfplayerThreadV2.h"
#include "VmspPlaylistCallback.h"

#include "ToolV023Dialog.h"
#include "ErrorDialog.h"


#include "Configuration.h"

#include "XfplayerScoring.h"

#include "VmsTextDoc.h"
#include "KaraokeSDIFrame.h"



// // BEGIN_MESSAGE_MAP(XfplayerView, ::userbase::view)
   //{{AFX_MSG_MAP(XfplayerView)
/*   ON_COMMAND(ID_PLAY, OnPlay)
   ON_WM_SIZE()
   ON_COMMAND(ID_STOP, OnStop)
   ON_COMMAND(ID_PAUSE, OnPause)
   ON_WM_TIMER()
   ON_WM_DESTROY()
   ON_WM_CREATE()
   ON_COMMAND(ID_NEXT_SONG, OnNextSong)
   ON_WM_CONTEXTMENU()
   ON_COMMAND(ID_PLAYPAUSE, OnPlaypause)
   ON_WM_ERASEBKGND()
   ON_WM_MOUSEWHEEL()
   ON_WM_PARENTNOTIFY()
   ON_WM_SETFOCUS()
   ON_COMMAND(ID_VIEW_IMAGE_TILE, OnViewImageTile)
   ON_COMMAND(ID_VIEW_IMAGE_ZOOMALL, OnViewImageZoomall)
   ON_COMMAND(ID_VIEW_IMAGE_STRETCH, OnViewImageStretch)
   ON_COMMAND(ID_VIEW_IMAGE_ZOOMEXTEND, OnViewImageZoomextend)
   ON_WM_KEYDOWN()
   ON_UPDATE_COMMAND_UI(ID_NEXT_SONG, OnUpdateNextSong)
   ON_UPDATE_COMMAND_UI(ID_PLAYPAUSE, OnUpdatePlaypause)
   ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_TILE, OnUpdateViewImageTile)
   ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_ZOOMALL, OnUpdateViewImageZoomall)
   ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_ZOOMEXTEND, OnUpdateViewImageZoomextend)
   ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_STRETCH, OnUpdateViewImageStretch)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SONGINFO, OnUpdateViewSongInfo)
   ON_UPDATE_COMMAND_UI(ID_VIEW_LEVELMETER, OnUpdateViewLevelmeter)
   ON_UPDATE_COMMAND_UI(ID_VIEW_AUDIOSPECTRUM, OnUpdateViewAudiospectrum)
   ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYERCONTROLSETV19, OnUpdateViewPlayercontrolsetv19)
   ON_UPDATE_COMMAND_UI(ID_VIEW_GRADUALFILLING, OnUpdateViewGradualfilling)
   ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNCINGBALL, OnUpdateViewBouncingball)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_LEVELMETER, OnUpdateWindowLevelmeter)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_AUDIOSPECTRUM, OnUpdateWindowAudiospectrum)
   ON_UPDATE_COMMAND_UI(ID_WINDOW_PLAYERCONTROLSETV19, OnUpdateWindowPlayercontrolsetv19)
   ON_WM_HSCROLL()
   ON_COMMAND(ID_VIEW_PLAYLIST, OnViewPlaylist)
   ON_COMMAND(ID_VIEW_SONGINFO, OnViewSongInfo)
   //   ON_COMMAND(ID_VIEW_LYRICVIEW_SPECTRUM, OnViewLyricviewSpectrum)
   //   ON_COMMAND(ID_VIEW_LYRICVIEW_SONGINFO, OnViewLyricviewSonginfo)
   //   ON_UPDATE_COMMAND_UI(ID_VIEW_LYRICVIEW_SPECTRUM, OnUpdateViewLyricviewSpectrum)
   ON_COMMAND(ID_VIEW_NEXT_IMAGE_NOW, OnViewNextImageNow)
   ON_COMMAND(ID_VIEW_SKIP_IMAGE_ALWAYS, OnViewSkipImageAlways)
   ON_COMMAND(ID_VIEW_BOUNCINGBALL, OnViewBouncingball)
   ON_COMMAND(ID_VIEW_GRADUALFILLING, OnViewGradualfilling)
   ON_COMMAND(ID_REFRESH, OnRefresh)
   ON_COMMAND(ID_VIEW_BOUNCE_BALL1, OnViewBounceBall1)
   ON_COMMAND(ID_VIEW_BOUNCE_BALL2, OnViewBounceBall2)
   ON_COMMAND(IDR_XFPLAYER_MENUBAR, OnXfplayerMenubar)
   ON_COMMAND(ID_WINDOW_LEVELMETER, OnWindowLevelmeter)
   ON_COMMAND(ID_VIEW_LEVELMETER, OnViewLevelmeter)
   ON_COMMAND(ID_VIEW_AUDIOSPECTRUM, OnViewAudiospectrum)
   ON_COMMAND(ID_WINDOW_AUDIOSPECTRUM, OnWindowAudiospectrum)
   ON_COMMAND(ID_VIEW_PLAYERCONTROLSETV19, OnViewPlayercontrolsetv19)
   ON_COMMAND(ID_WINDOW_PLAYERCONTROLSETV19, OnWindowPlayercontrolsetv19)
   ON_COMMAND(ID_OPEN_LINK, OnOpenLink)
   ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdateExecutePlay)
   ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdateExecutePause)
   ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateExecuteStop)
   ON_COMMAND(ID_LISTEN_MINUS_ONE, OnListenMinusOne)
   ON_UPDATE_COMMAND_UI(ID_LISTEN_MINUS_ONE, OnUpdateListenMinusOne)
   ON_COMMAND(ID_EXECUTE_TEMPO_MINUS, OnExecuteTempoMinus)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_MINUS, OnUpdateExecuteTempoMinus)
   ON_COMMAND(ID_EXECUTE_TEMPO_PLUS, OnExecuteTempoPlus)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_PLUS, OnUpdateExecuteTempoPlus)
   ON_COMMAND(ID_EXECUTE_TEMPO_RESET, OnExecuteTempoReset)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_RESET, OnUpdateExecuteTempoReset)
   ON_COMMAND(ID_EXECUTE_TRANSPOSE_MINUS, OnExecuteTransposeMinus)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_MINUS, OnUpdateExecuteTransposeMinus)
   ON_COMMAND(ID_EXECUTE_TRANSPOSE_MINUS_TONE, OnExecuteTransposeMinusTone)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_MINUS_TONE, OnUpdateExecuteTransposeMinusTone)
   ON_COMMAND(ID_EXECUTE_TRANSPOSE_PLUS, OnExecuteTransposePlus)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_PLUS, OnUpdateExecuteTransposePlus)
   ON_COMMAND(ID_EXECUTE_TRANSPOSE_PLUS_TONE, OnExecuteTransposePlusTone)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_PLUS_TONE, OnUpdateExecuteTransposePlusTone)
   ON_COMMAND(ID_EXECUTE_TRANSPOSE_RESET, OnExecuteTransposeReset)
   ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_RESET, OnUpdateExecuteTransposeReset)
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_COMMAND(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
   ON_MESSAGE(VMSM_ECONOMODECHANGE, OnEconoModeChange)
   ON_MESSAGE(VMSM_NOTIFY, OnVMSNotify)
   ON_MESSAGE(WM_USER, OnUserMessage)
   ON_MESSAGE(WM_APP, OnAppMessage)
   //ON_MESSAGE(VMSPM_XFVIEW, OnXfplayerViewMessage)
   ON_MESSAGE(VMSM_TIMER, OnVMSTimer)
   ON_MESSAGE(APPM_NOTIFY, OnAppNotify)
   ON_MESSAGE(CVmsGenApp::APPM_LANGUAGE, OnAppLanguage)
   ON_MESSAGE(MMSG_DONE, OnMmsgDone)
   //    ON_MESSAGE(WM_USER + 100, OnRenderTransparent)
   //   ON_MESSAGE(WM_APP_TRANSPARENT_PAINT, CTransparentWndInterface::OnTwiPaint)*/
// // END_MESSAGE_MAP()


XfplayerView::XfplayerView(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   gcom::backview::Interface(papp),
   gcom::backview::user::interaction(papp),
   KaraokeView(papp),
   mediaplay::view_interface(papp),
   MidiPlayerInterface(papp),
   audio::WavePlayerInterface(papp),
   audio::WaveRecorderInterface(papp),
   mplite::view(papp),
   m_extraLines(papp),
   m_titleLines(papp),
   m_lineSongLabel(papp),
   m_lineScore(papp),
   m_spgraphics(papp),
   m_penLeft(papp),
   m_penRight(papp),
   m_penLeftSmall(papp),
   m_penRightSmall(papp),
   m_penTitle(papp),
   m_penSubTitle(papp),
   m_penScore(papp),
   m_rgnChildren(papp)
{
   m_spgraphics->CreateCompatibleDC(NULL);
   m_ptemplateTab = NULL;
   m_bWaitingToPlay = false;
   m_bSettingNextSong = false;

   m_pscoring = AfxBeginThread < XfplayerScoring > (papp);

//   InstallTimerCallbackHook();
   m_dwTimerProcLastTime = 0;
   m_dwVMSTimerLastTime = 0;
   
   //m_pbackviewinterface = new _vmsgcom::CBackViewInterface(*(_vmsgcom::CBackViewWndInterface *) this);
   
//   _000HookWndProc((gcom::backview::Interface *) &BackViewGetInterface());
//   _000HookBeforeWndProc((C001TransparentWndInterface *) this);
//   _000HookWndProc((C001TransparentWndInterface *) this);
   
   //BackViewGetInterface().SetBackgroundImageChangeInterval(p())->m_iBackgroundUpdateMillis);
   
   
   m_evTransitionEffectRunStep.ResetEvent();
//   m_sliderProgress.m_bPresenceOnHover = true;
   m_bDestroy = false;
   m_pvmstextdocHelper = NULL;
   m_iRightVerticalShift = 0;
   m_bHoverTimer = false;
   
   m_uiTimer = 0;
   m_dwBackgroundLastUpdateTime = 0;
   m_dwSliderLastUpdateTime = 0;
   m_dwTimeLastUpdateTime = 0;
   m_bLastLoadImageSynch = true;
   m_cnt = 0L; 
   
   LOGBRUSH lb;
   
   memset(&lb, 0, sizeof(lb));
   
   m_penLeft->delete_object();
   m_penLeft->CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
   
   m_penRight->delete_object();
   m_penRight->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
   
   m_penLeftSmall->delete_object();
   m_penLeftSmall->CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
   
   m_penRightSmall->delete_object();
   m_penRightSmall->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
   m_bOnDraw = false;
   m_penTitle->delete_object();
   m_penTitle->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
   m_penSubTitle->delete_object();
   m_penSubTitle->CreatePen(PS_SOLID, 0, RGB(64, 64, 0));
   m_crLeft = RGB(255, 127, 0);
   m_crRight = RGB(255, 255, 0);
   m_crTitle = RGB(0, 255, 255);
   m_crSubTitle = RGB(255, 255, 192);
   m_dwScoreLastUpdateTime = 0;
   m_penScore->CreatePen(PS_SOLID, 3, RGB(255, 127, 0));
   m_bTitleVisible = false;
   m_bOnSizeEnabled = false;
   m_dwAdvancingTime = 0;
   m_bInitialized = false;
   
   m_pplaylistframe = NULL;
   //    m_pplaylistipwnd = NULL;
   m_pplaylistdoc = NULL;
   //   m_pfiBitmap = NULL;
   m_rgnChildren->CreateRectRgn(0 ,0 ,0 , 0);
   ///m_psliderProgress = new CSliderV017();
   //    m_pedit = new simple_edit();
   //    m_bDirectDrawPresenceChecked = false;
   //  m_bDirectDrawPresent = false;
   //m_bDirectDrawActive = false;
   
   m_lpbouncingball = new kar::KaraokeBouncingBall(get_app());
   //throw not_implemented_exception();
   //m_lpbouncingball->SetIcons(System.LoadIcon(IDI_BB1), System.LoadIcon(IDI_BB1_PRESSED1));
   
   m_dProgressRate = 0.0;
   
   m_dScoreRate = 0.0;
   
   m_enhmetafile = NULL;
   memset(&m_emh, 00, sizeof(m_emh));
   
   m_rcLastBkImage.set(0, 0, 0, 0);
   m_bScoring = false;

   ::ca::font_sp font(get_app());
   LOGFONT lf;
   memset(&lf, 0, sizeof(LOGFONT));
   lf.lfUnderline = FALSE;
   lf.lfWeight = FW_BOLD;
   strcpy(lf.lfFaceName, "Arial Black");
   lf.lfHeight = 120;
   font->CreateFontIndirect(&lf);
   m_lineScore.SetFont(font);

   // Xf Player ::view wishes and is prepared for
   // Timer Window object Queue Model timer message posts.
//   m_bQueueModel = true;
}

XfplayerView::~XfplayerView()
{
   
   if(m_pplaylistcallback != NULL)
   {
      delete m_pplaylistcallback;
   }
   if(m_lpbouncingball != NULL)
   {
      delete m_lpbouncingball;
      m_lpbouncingball = NULL;
   }
   delete m_pscoring;
}

BOOL XfplayerView::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   cs.lpszClass = pApp->m_XFViewClassName;
   //cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
   //cs.style &= ~WS_CLIPCHILDREN;
   if(!::userbase::view::PreCreateWindow(cs))
      return FALSE;
   cs.style |= WS_CLIPCHILDREN;
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   //cs.style |= WS_CLIPCHILDREN;
   return TRUE;
}

#ifdef _DEBUG
void XfplayerView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void XfplayerView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}

XfplayerDoc* XfplayerView::get_document() // non-debug version is inline
{
   ASSERT(base < XfplayerDoc >::bases(::view::get_document()));
   return dynamic_cast < XfplayerDoc * > (::view::get_document());
}
#endif //_DEBUG


void XfplayerView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   view::_001OnInitialUpdate(pobj);
   
   
   m_lineScore.SetAutoSize(true);
   m_lineScore.SetAlign(XfplayerViewLine::AlignRight);
   
   
//   m_lpbouncingball->SetTwi(this);


   GetScoring()->Enable(true);
   
   
   
   OnScoringEnable(GetScoring()->IsEnabled());
   
}

void XfplayerView::_001OnSize(gen::signal_object * pobj) 
{
   
   UNREFERENCED_PARAMETER(pobj);

   layout();
   
   gcom::backview::Interface::ImageChangePostEvent(gcom::backview::EventResize);
   
}

void XfplayerView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{
//   XfplayerDoc * pDoc = get_document();
//   XfplayerDoc * pdoc = pDoc;
   frame_window * pframe = GetParentFrame();
   KaraokeSDIFrame * psdiframe = NULL;
   if(base < KaraokeSDIFrame >::bases(pframe))
   {
      psdiframe = dynamic_cast < KaraokeSDIFrame * > (pframe);
   }
   if(psdiframe == NULL)
   {
      m_bFullScreen = false;
      m_bCompactMode = false;
   }
   else
   {
      m_bCompactMode = psdiframe->IsCompactMode();
      m_bFullScreen = psdiframe->IsFullScreen();
   }
   
   view::on_update(pSender, lHint, pHint);
   if(base < ::mediaplay::view_update_hint > :: bases(pHint))
   {
      ::mediaplay::view_update_hint * puh = (::mediaplay::view_update_hint * ) pHint;
      if(puh->is_type_of(::mediaplay::view_update_hint::TypeAfterOpenDocument))
      {
         m_bOverrideKaraokeCodePage = true;

         /*string wstrKey;
         wstrKey = get_document()->mediaplay::data::get_path_name();
         wstrKey += L".OverrideKaraokeCodePage";
         
         string strValue;
         db()->WStrToWStr().GetDirect(strValue, wstrKey);
         if(wstrKey ==  L"True")
         {
            m_bFileOverrideKaraokeCodePage = true;
   
            wstrKey = get_document()->mediaplay::data::get_path_name();
            wstrKey += L".OverridingKaraokeCodePage";

            db()->WStrToWStr().GetDirect(strValue, wstrKey);

            m_dwFileOverrideKaraokeCodePage = (DWORD) wcstod(wstrKey, NULL);

         }
         else
         {
            m_bFileOverrideKaraokeCodePage = false;
         }*/
      }
      else if(puh->is_type_of(::mediaplay::view_update_hint::TypeBeforeOpenDocument))
      {
         mediaplay::data * pdata = view_interface::get_data();
         m_pscoring->SetKaraokeData(&pdata->GetKaraokeData());
      }
   }
}
/*
void XfplayerView::OnLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents, bool bRepaint)
{
   //   for(int i = 0; i < pevents->get_size(); i++)
   //   {
   //      OnLyricEvent(&pevents->get_at(i), bRepaint);
   
   //   }
   if(pevents->get_size() > 0)
   {
      OnLyricEvent(&pevents->last_element(), bRepaint);
   }
}*/
/*
void XfplayerView::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   if(pevents->get_size() > 0)
   {
      OnLyricEvent(&pevents->last_element(), true);
   }
}*/


afx_msg LRESULT XfplayerView::OnAppMessage(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   switch(wParam)
   {
   case 178:
      {
         LayoutDynamicChild();
      }
      break;
   case 179:
      {
         LayoutDynamicChild(true);
      }
   default:
      break;
   }
   return 0;
}

afx_msg LRESULT XfplayerView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);;
   ASSERT(papp != NULL);
/*   if(wParam == USERMESSAGE_WPARAM_UPDATESCREEN_LPCRECT)
   {
      LPCRECT lpcrect = (LPRECT) lParam;
      rect rect(lpcrect);
      _001RedrawWindow(rect);
   }
   else if(wParam == USERMESSAGE_WPARAM_UPDATESCREEN_NEWRECT)
   {
      LPRECT lprect = (LPRECT) lParam;
      _001RedrawWindow(lprect);
      delete lprect;
   }
   else if(wParam == USERMESSAGE_WPARAM_RAND_LPINT)
   {
      LPINT lpint = (LPINT) lParam;
      *lpint = rand();
   }*/
   if(wParam == 4)
   {
//      Scoring::UpdateMessage * lpsum = (Scoring::UpdateMessage *) lParam ;
      //TRACE("CVmpHighThread::TranslateUserMessage 2 slGdi.Lock\n");
      /*      if(m_paudiospectrumwnd != NULL)
      {
      m_paudiospectrumwnd->Update(
      papp->WaveCentralGetWaveIn()->GetFormatEx(),
      lpsum->dDeltaScore,
      lpsum->dScoreAddUp);
   }*/
      //      rect rect;
      //      m_voiceSpectrum.GetPlacement(rect);
      //      TwiRedraw(rect);
      
      //      CSingleLock slGdi(&m_csGdi, TRUE);
      
      //      m_voiceSpectrum.to(pApp->GetWaveIn()->GetFormatEx(), lpSum->dDeltaScore, lpSum->dScoreAddUp);
      //      rect rect;
      //      m_voiceSpectrum.GetPlacement(rect);
      //pview->ClientToScreen(rect);
      //InvalidateRect(&rect, FALSE);
      //TRACE("CVmpHighThread::TranslateUserMessage 2 slGdi.UnLock\n");
      
      //      pview->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
      //        pview->RenderTransparent(pview, rect, NULL, true);
      //        _001RedrawWindow(rect, true);
      //        slGdi.Unlock();
      
      
   }
   else if(wParam == 16384)
   {
//      BackViewChangeBackgroundImage(true);
   }
   else if(wParam == 3377)
   {
      ASSERT(FALSE);
//      OnLyricEvent((LyricEventV1 *) lParam, true);
      delete (LyricEventV1 *)lParam;
   }
   else if(wParam == 3388)
   {
      // Lyric ::view Event 
//      OnLyricEvent((base_array<LyricEventV1, LyricEventV1&> *) lParam, true);
      //      delete (base_array<LyricEventV1, LyricEventV1&> *)lParam;
   }
   else if(wParam == 3389)
   {
      TRACE("XfplayerView::OnUserMessage 1 slGdi.Lock\n");
      rect rect;
      ASSERT(FALSE);
      //      if(m_paudiospectrumwnd != NULL)
      //      {
      //         m_paudiospectrumwnd->TwiRedraw();
      //      }
      //m_voiceSpectrum.GetPlacement(rect);
      //TwiRedraw(rect);
      //      CSingleLock slGdi(&m_csGdi, TRUE);
      //      m_voiceSpectrum.to(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
      //      RECT rect;
      //      m_voiceSpectrum.GetPlacement(&rect);
      //InvalidateRect(&rect, FALSE);
      //      TRACE("XfplayerView::OnUserMessage 1 slGdi.UnLock\n");
      
      //        pview->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
      //    _001RedrawWindow(&rect, true);
      //  slGdi.Unlock();
   }
   else if(wParam == 7788)
   {
      ASSERT(FALSE);
      TRACE("XfplayerView::OnUserMessage slGdi.Lock\n");
      //      CSingleLock slGdi(&m_csGdi, TRUE);
      //      m_voiceSpectrum.to(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
      //      RECT rect;
      //      m_voiceSpectrum.GetPlacement(&rect);
      //InvalidateRect(&rect, FALSE);
      //      TRACE("XfplayerView::OnUserMessage slGdi.UnLock\n");
      //    slGdi.Unlock();
      //to(&rect, TRUE);
      //  RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
      
      
   }
   
   //   else if(wParam == XFM_RETURN_LOADED_IMAGE)
   //   {
   //      LPXFLOADIMAGESTRUCTURE lpLi = (LPXFLOADIMAGESTRUCTURE) lParam;
   //      m_hBitmap = lpLi->m_hBitmap;
   //      BkImageChangeStateMachine(BkImageChangeEventLoaded);
   //      delete lpLi;
   //   }
   
   else if(wParam == 33)
   {
      //      m_freeImage = (LPVOID) lParam;
      //      m_eventBkImageReady.PulseEvent();
      //      m_pFreeImage = (FIBITMAP *) lParam;
      //      BkImageChangeStateMachine(BkImageChangeEventLoaded);
      SynchronizeLyrics((imedia::position) lParam);
   }
   else if(wParam == 1)
   {
   }
   else if(wParam == 17)
   {
      gcom::backview::Interface::ImageChangePostEvent((gcom::backview::e_event) lParam);
   }
   else if(wParam == 5)
   {
//      bool bMakeVisible = lParam != 0;
   }
   else if(wParam == 201)
   {
      OnUpdateProgress(NULL);
   }
   else if(wParam == 121314)
   {
      LPLYRICVIEWLINESHIFTEVENT plvlse = 
         (LPLYRICVIEWLINESHIFTEVENT) lParam;
      
      LyricEventV1 event;


      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();
      
      event.m_iType = 12;
      event.m_iCurrentToken = dynamicdata.m_iPlayingTokenIndex;
      event.m_iCurrentNote  = dynamicdata.m_iPlayingNoteIndex;
      event.m_iCurrentLine  = plvlse->nLine;
      
      m_dTextOffsetRate = plvlse->dRate;
      
/*      OnLyricEvent(&event, true); // cut proccessing*/
      
   }
   else if(wParam == 1213145)
   {
/*      LPLYRICVIEWLINESHIFTEVENT plvlse = 
         (LPLYRICVIEWLINESHIFTEVENT) lParam;
      LyricEventV1 event;

      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();
      
      event.m_iType = 71;
      event.m_iCurrentToken = dynamicdata.m_iPlayingTokenIndex;
      event.m_iCurrentNote  = dynamicdata.m_iPlayingNoteIndex;
      event.m_iCurrentLine  = plvlse->nLine;
      
      m_dTextOffsetRate = plvlse->dRate;*/
      
//      OnLyricEvent(&event, true); // cut proccessing
      
   }
   else if(wParam == 1213146)
   {
/*      LPLYRICVIEWLINESHIFTEVENT plvlse = 
         (LPLYRICVIEWLINESHIFTEVENT) lParam;
      LyricEventV1 event;

      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();

      event.m_iType = 72;
      event.m_iCurrentToken = dynamicdata.m_iPlayingTokenIndex;
      event.m_iCurrentNote  = dynamicdata.m_iPlayingNoteIndex;
      event.m_iCurrentLine  = plvlse->nLine;
      
      m_dTextOffsetRate = plvlse->dRate;
      
      OnLyricEvent(&event, true); // cut proccessing*/
      
   }
   
   
   else if(wParam == 12131415)
   {
      LyricEventV1 event;

      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();
      
      event.m_iType = 14;
      event.m_iCurrentToken = dynamicdata.m_iPlayingTokenIndex;
      event.m_iCurrentNote  = dynamicdata.m_iPlayingNoteIndex;
      //event.m_iCurrentLine  = lParam;
      
/*      OnLyricEvent(&event, true); // cut proccessing*/
      
   }
   else if(wParam == 1945)
   {
      string * pwstr = (string *) lParam;
      TextDocHelperAdd(*pwstr);
      delete pwstr;
   }
   
   return 0;
}

void XfplayerView::OnStop() 
{
   LyricViewLines & lyriclines = GetLyricLines();
   // TODO: add your command handler code here
   if(m_lyrictemplatelines.get_size() > 0)
   {
      //XfplayerViewLine objViewLine ;
      //XfplayerViewLine & refViewLine = objViewLine;
      //        XfplayerViewLine * pviewline = NULL;
      //      int i, iLineIndex;
      //      for(i = 0; i < m_lyrictemplatelines.get_size() ; i++)
      //      {
      //           if(0 <= (iLineIndex = lyriclines.get_at(
      //              &pviewline,
      //            m_lyrictemplatelines,
      //          i)))
      //    {
      //      pviewline->SetStatus(XfplayerViewLine::StatusEmpty);
      //}
      
      //}
      
      // Apaga todas as linhas visíveis
      int iStartIndex, iEndIndex;
      iStartIndex = lyriclines.GetFirstVisibleLine();
      if(iStartIndex < 0)
         iStartIndex = 0;
      if(iStartIndex >= lyriclines.GetLineCount())
         iStartIndex = lyriclines.GetLineCount() - 1;
      iEndIndex = lyriclines.GetLastVisibleLine();
      if(iEndIndex < iStartIndex)
         iEndIndex = iStartIndex;
      if(iEndIndex >= lyriclines.GetLineCount())
         iEndIndex = lyriclines.GetLineCount() - 1;
      
      //TRACE("lyriclines.GetFirstVisibleLineIndex() = %d\n", iStartIndex);
//      bool bClear = false;
      for(int i = iEndIndex; i >= iStartIndex; i--)
      {
         if(i >= 0 &&
            i < lyriclines.GetLineCount())
         {
            LyricViewLine * pviewline = &lyriclines.get(i);
            if(pviewline->IsVisible())
            {
               pviewline->Show(false);
            }
         }
      }
      
   }
   
   UpdateTime();
   
   
}

void XfplayerView::OnMainTimer()
{
   
   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   ::mus::midi::sequence & seq = pDoc->::mediaplay::document::get_data()->GetMidiSequence();
   
   DWORD dwTime = timeGetTime();
   
   if(dwTime - m_dwLastTime1 < 75)
      return;
   
   if(!seq.IsNull() &&
      !pDoc->IsOpening() &&
      !pDoc->IsClosing() &&
      (seq.GetState() == ::mus::midi::sequence::StatusPlaying ||
      seq.GetState() == ::mus::midi::sequence::StatusStopping))
   {
      ikar::data & data = GetKaraokeData();
      ikar::dynamic_data & dynamicdata = data.GetDynamicData();

      LyricEventV1 event;
      event.m_iType = ikar::event_timer;
      event.m_iCurrentToken = dynamicdata.m_iPlayingTokenIndex;
      event.m_iCurrentNote  = dynamicdata.m_iPlayingNoteIndex;
//      OnLyricEvent(&event, true); // cut proccessing
      if(dwTime >= (DWORD) (m_dwTimeLastUpdateTime + 1000) &&
         m_dwTimeLastUpdateTime >= 0)
      {
         UpdateTime(); //cut processing
         m_dwTimeLastUpdateTime = dwTime;
         
      }
      if(dwTime >= (DWORD) (m_dwSliderLastUpdateTime + 500))
      {
         SendMessage(WM_USER, 201);//cut processing
      }
      
   }
   
   if(dwTime - m_dwLastTime1 >= 100)
   {
      if(m_bHoverTimer
         && timeGetTime() > m_dwHoverTimer + 1000)
      {
         m_bHoverTimer = false;
      }

      m_dwLastTime1 = dwTime;
      
      m_dwLastTimer1 = dwTime;
      
      
      if(dwTime >= (DWORD) (m_dwScoreLastUpdateTime + 1000))
      {
         double dScoreRate = GetScoreRate();
         if(dScoreRate != m_dScoreRate)
         {
            m_dScoreRate = dScoreRate;
            RedrawScore(false);
         }
         
         
         m_dwScoreLastUpdateTime = dwTime;
      }
      if(_ExecuteIsWaitingToPlay())
      {
         if(timeGetTime() > GetPlayTimeOut())
         {
            StartMusicRendering();
            
         }
      }
   }
   
}

void XfplayerView::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   TimerMachine((ETimer) ptimer->m_nIDEvent);
}


void XfplayerView::OnCentiTimer()
{
   gcom::backview::Interface::ImageChangePostEvent(gcom::backview::event_timer);
   
//  ::ca::graphics * pdScreen = m_spgraphics;
  // rect_array recta;
/*   m_lineSongLabel.OnTimerAnimate(
      m_spgraphics,
      NULL,
      recta);*/
   
   //_001RedrawWindow(recta);
   
}

void XfplayerView::OnKiloTimer()
{
   
}



void XfplayerView::TimerMachine(ETimer etimer) 
{
   UINT nIDEvent = (UINT) etimer;
   CSingleLock slTimer(&m_csTimer, TRUE);
   if(!m_bInitialized)
      return;
   
   if(!IsWindow())
      return;
   
   
   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
//   ::mus::midi::sequence & seq = pDoc->::mediaplay::document::get_data()->GetMidiSequence();
   
   DWORD dwTime = timeGetTime();
   
   if(dwTime - m_dwCentiTimerLastTime > TimeOutCenti)
   {
      OnCentiTimer();
      m_dwCentiTimerLastTime = dwTime;
      if(dwTime - m_dwKiloTimerLastTime > TimeOutKilo)
      {
         OnKiloTimer();
         m_dwKiloTimerLastTime = dwTime;
      }
   }
   
   
   
   
   
   if(TimerMain == etimer)
   {
      OnMainTimer();
   }
   else if(nIDEvent == 12345)
   {
      m_dwHoverTimer = timeGetTime();
   }
}


void XfplayerView::_001OnDestroy(gen::signal_object * pobj) 
{
/*   if(m_pthreadTransitionEffectRunStep != NULL)
{
::TerminateThread(m_pthreadTransitionEffectRunStep->m_hThread, -1);
m_pthreadTransitionEffectRunStep = NULL;
}*/
   
   m_bDestroy = true;
   
//   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
//   XfplayerThreadV3 * pthreadv3 = (XfplayerThreadV3 *) papp->GetThreadV3();
   //pthreadv3->m_bBkImageEnable = false;
   
   //if(m_pkcs1wndAudioSpectrum != NULL)
   //{
   //   ShowAudioSpectrum(false);
   //}
   
   
   
   if(m_pplaylistframe != NULL)
      m_pplaylistframe->PostMessage(WM_CLOSE);
   
   TRACE("XfplayerView::OnDestroy");
   gen::TimerCallback::Enable(false);
   //if(!((TimerCallback *)this)->m_pTimerWnd->m_evFree.Lock();
   
   ::userbase::view::_001OnDestroy(pobj);
   
   // TODO: add your specialized code here and/or call the base class
//   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
//   gen::CHighThread & highthread = gen::CHighThreadContainer::AppGetHighThread();
   //if(GetCurrentThread() == pThreadV1->m_hThread)
   //{
  // highthread.DeleteTimerWnd(m_ptimerwnd);
   //}
   //else
   //{
   //  pThreadV1->PostThreadMessage(VMSM_V001, NOTIFY_TIMERCALLBACKDELETETIMER, (LPARAM) m_pTimerWnd);
   //}
   
   gcom::backview::Interface::OnDestroy();
   
   // TODO: add your message handler code here
   //   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
//   string str;
  // gen::international::UnicodeToOEM(str, BackViewGetInterface().GetImageChange().m_wstrCurrentImagePath);
   //DISave("Images.CurrentPath", str);
   
   //    pApp->GetThreadV1()->PostThreadMessage(
   //      WM_NULL,
   //    0,
   //  0);
   //pApp->GetThreadV1()->EnableTimers(false);
   
   //    pApp->GetThreadV1()->PostThreadMessage(
   //      WM_USER_NOTIFY,
   //    NOTIFY_TIMERCALLBACKDELETETIMER,
   //  (LPARAM) m_pTimerWnd);
   //    m_pTimerWnd->SendMessage(WM_CLOSE);
   //  while(!m_evTimerWndDeleted.Lock(0))
   //    ::Sleep(0);
   
   if(m_uiTimer)
   {
      KillTimer(m_uiTimer);
      m_uiTimer = 0;
   }
}

void XfplayerView::UpdateTime()
{
//   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   frame_window *pframe = GetParentFrame();
   if(!base < KaraokeSDIFrame >::bases(pframe))
      return;
   KaraokeSDIFrame * psdiframe = dynamic_cast < KaraokeSDIFrame * > (pframe);
   //KaraokeSDIFrame *pframe = (KaraokeSDIFrame *) AfxGetMGetParentFrame();
   if(!psdiframe)
      return;
/*   SimpleDialogBar * lpDialogBar = psdiframe->GetDialogBar();
   if(!IsWindow(lpDialogBar->get_os_data()))
      return;*/
/*   simple_edit *pEdit = (simple_edit *) lpDialogBar->GetDlgItem(IDC_EDIT_TIME);
   if(!pEdit)
      return;*/
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   ::mus::midi::sequence & seq = pDoc->::mediaplay::document::get_data()->GetMidiSequence();
   ASSERT(!seq.IsNull());
   if(seq.IsPlaying())
   {
      string str;
      imedia::position tkTime;
      if(MMSYSERR_NOERROR != seq.get_time(tkTime))
         return;
      int millis = seq.TicksToMillisecs(tkTime);
      int centis = millis / 10;
      int seconds = centis / 100;
      int minutes = seconds / 60;
      int hours = minutes / 60;
      centis %= 100;
      seconds %= 60;
      minutes %= 60;
      //str.Format(_T("%02d:%02d:%02d %02d\""), hours, minutes, seconds, centis);
      str.Format("%02d:%02d:%02d", hours, minutes, seconds);
// linux     pEdit->SetWindowText((const char *) str);
   }
   else if(seq.GetState() == ::mus::midi::sequence::StatusOpened)
   {
      string str;
      imedia::position tkTime = seq.m_tkEnd;
      int millis = seq.TicksToMillisecs(tkTime);
      int centis = millis / 10;
      int seconds = centis / 100;
      int minutes = seconds / 60;
      int hours = minutes / 60;
      centis %= 100;
      seconds %= 60;
      minutes %= 60;
      //str.Format(_T("%02d:%02d:%02d %02d\""), hours, minutes, seconds, centis);
      str.Format("%02d:%02d:%02d", hours, minutes, seconds);
// linux     pEdit->SetWindowText((const char *) str);
   }
   
}

/*void XfplayerView::UpdateSlider()
{
vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
KaraokeSDIFrame *pframe = (KaraokeSDIFrame *) pApp->GetMainWnd();
ASSERT(pframe != NULL);
XfplayerDoc *pDoc = get_document();
ASSERT(pDoc != NULL);
::mus::midi::sequence * pSeq = pDoc->GetMidiSequence();
ASSERT(!seq.IsNull());
imedia::position   tkTime;
if(MMSYSERR_NOERROR != seq.get_time(&tkTime))
return;
double rate = ((double) tkTime) / seq.GetFile().m_tkLength;
pDoc
//   XfplayerDialogBar * lpDialogBar = pframe->GetDialogBar();
//pDialogBar->SetSliderPos(rate);
m_dwSliderLastUpdateTime = timeGetTime();

} */

void XfplayerView::SynchronizeLyrics(double dRate)
{
   System.math().MaxClip(&dRate, 1.0);
   System.math().MinClip(&dRate,  0.0);
   if(!get_document()->::mediaplay::document::get_data()->GetMidiSequence().IsNull())
   {
      SynchronizeLyrics((imedia::position) (int) (get_document()->::mediaplay::document::get_data()->GetMidiSequence().m_tkLength * dRate));
   }
   
}

void XfplayerView::SynchronizeLyrics(imedia::position tkPosition)
{
//   LyricViewLines & lyriclines = GetLyricLines();
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   //primitive_array < visual::font *> * pFonts = GetLyricFonts();
   //ASSERT(pFonts != NULL);
   visual::font * pfont = GetLyricFont();
   ASSERT(pfont != NULL);
   ::mus::midi::sequence & seq = pDoc->::mediaplay::document::get_data()->GetMidiSequence();
   ASSERT(!seq.IsNull());
   ::mus::midi::file & file = seq.GetFile();
   ASSERT(!file.IsNull());

   ikar::data & data = GetKaraokeData();
   ikar::static_data & staticdata = data.GetStaticData();

   EventsTracksV1 * peventsarray = &staticdata.m_eventstracksV002;
   ASSERT(peventsarray != NULL);
   LyricEventsV2 * pevents;
   //   if(pDoc->m_p2DTokens == NULL)
   //      pevents = NULL;
   //   else if(pDoc->m_p2DTokens->get_size() <= 0)
   if(staticdata.m_str2aRawTokens.get_size() <= 0)
      pevents = NULL;
   else if(peventsarray->get_size() < staticdata.m_str2aRawTokens.get_size())
      pevents = NULL;
   else
   {
      //pevents = (LyricEventsV2 *) peventsarray->operator [](file.m_str2aRawTokens.get_size());
      //        pevents = (LyricEventsV2 *) peventsarray->operator [](peventsarray->get_size() / 2);
      pevents = (LyricEventsV2 *) peventsarray->operator [](0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   
   int i;
   
   rect_array recta;
   rect rectClient;
   GetClientRect(rectClient);
   TRACE("XfplayerView::SetPlayingPosition 1 slGdi.Lock\n");
//   ::ca::graphics * pdcScreen = m_spgraphics;
   // Prepara todos System aparatos para se desenhar
   
   LyricEventsV1 * pEventsV1;
   LyricEventsV2 * pEventsV2;
   int iTokenIndex = -1;
   int iNoteIndex = -1;
   
   for(i = 0; i < staticdata.m_eventsTracksForPositionCB.get_size(); i++)
   {
      pEventsV1 =   staticdata.m_eventsTracksForPositionCB.get_at(i);
      if(pEventsV1->GetClassOrder() == 2)
      {
         pEventsV2 = (LyricEventsV2 *) pEventsV1;
         iNoteIndex = pEventsV2->GetPositionNote(tkPosition);
         if(iNoteIndex >= 0)
         {
            iTokenIndex = pEventsV2->GetNoteFirstToken(iNoteIndex);
            break;
         }
         iTokenIndex = pEventsV2->GetPositionToken(tkPosition);
         if(iTokenIndex >= 0)
         {
            iNoteIndex = pEventsV2->GetTokenFirstNote(iTokenIndex);
            break;
         }
      }
   }
   LyricEventV1 event;
   event.m_iCurrentToken = iTokenIndex;
   event.m_iCurrentNote = iNoteIndex;
   event.m_iType = ikar::EventSetElement;
   event.m_tkPosition = tkPosition;
//   OnLyricEvent(&event, true);
   
}

void XfplayerView::Reset()
{
   LyricViewLines & lyriclines = GetLyricLines();
   int iSize = lyriclines.GetLineCount();
   int i;
   LyricViewLine * pviewline = NULL;
   for(i = 0; i < iSize; i++)
   {
      pviewline = &lyriclines.get(i);
      pviewline->Reset();
   }
   
}

void XfplayerView::UpdateReserveList()
{
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   //   primitive_array < visual::font *> * pFonts = GetLyricFonts();
   //   ASSERT(pFonts != NULL);
   //visual::font * pfont = GetLyricFont();
   //ASSERT(pfont != NULL);
   db_server * pDataCentral = dynamic_cast < db_server * > (&System.db());
   ASSERT(pDataCentral != NULL);
   ::ca::rgn rgn;
   rgn.CreateRectRgn(0, 0, 0, 0);
   
   RECT clientRect;
   GetClientRect(&clientRect);
   TRACE("XfplayerView::UpdateReserveList 1 slGdi.Lock\n");
   if(!m_spgraphics->SetMapMode(MM_TEXT))
   {
      TRACE0("Could not set ::collection::map mode to MM_TEXT.\n");
   }
//   frame_window *pframe = GetParentFrame();
   TRACE("XfplayerView::UpdateReserveList 1 slGdi.UnLock\n");
   rect rgnBox;
   rgn.GetRgnBox(rgnBox);
   if(!rgnBox.is_null())
   {
//      TwiRedraw(NULL, &rgn);
   }
   //InvalidateRgn(&rgn, FALSE);
   
}


void XfplayerView::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);

   m_lyrictemplatelines.relay_event(pobj);
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   
   ASSERT(pApp != NULL);
   if(pApp->GetMainWnd() != NULL)
   {
      if(base < KaraokeSDIFrame >::bases(pApp->GetMainWnd()))
      {
         //((KaraokeSDIFrame *) pApp->GetMainWnd())->m_ReserveList.m_ToolTip.relay_event(pMsg);
      }
   }
   switch(pbase->m_uiMessage)
   {
   case WM_DISPLAYCHANGE:
      OnDisplayChange(pbase->m_wparam, size(LOWORD(pbase->m_lparam), HIWORD(pbase->m_lparam)));
      pbase->m_bRet = true;
      return;
   case WM_USER:
      //         if(OnUserMessage(pMsg->wParam, pMsg->lParam))
      //             return TRUE;
      break;
   case WM_USER + 3:
      ASSERT(FALSE);
      switch(pbase->m_wparam)
      {
      case 201:
         OnUpdateProgress(NULL);
         //                UpdateProgress(); // cut processing
         pbase->m_bRet = true;
         return;
      default:
         break;
      }
      break;
      case WM_USER + 8:
         break;
      case MMSG_DONE:
         //OnMmsgDone((::mus::midi::sequence *) pMsg->wParam, (LPMIDIDONEDATA) pMsg->lParam);
         //delete (LPMIDIDONEDATA) pMsg->lParam;
         return;
      case VMSM_RENDER_RECT:
         //            to((LPRECT) pMsg->wParam);
         break;
      case VMSM_RENDER_RGN:
         //          to((::ca::rgn *) pMsg->wParam);
         break;
      case WM_USER + 100:
         ASSERT(FALSE);
         break;
         //            RenderTransparent(pdcScreen, (::ca::window *) pMsg->wParam, (LPRECT) pMsg->lParam, NULL, false);
         break;
      case WM_MOUSEMOVE:
         if(!m_bHoverTimer)
         {
            m_bHoverTimer = true;
            SetTimer(12345, 100, NULL);
         }
      default:
         break;
   }
   
   ::userbase::view::pre_translate_message(pobj);
}







void XfplayerView::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::create, pcreate, pobj);
   vmsp::application * papp = dynamic_cast < vmsp::application * > (get_app());
   m_pcentral = &(dynamic_cast < vmsp::application * > (get_app()))->GetMidiCentral();
   pobj->previous();


   /*if(!Initialize(&System.GetMidiCentral()))
   {
      pcreate->set_lresult(0);
      pcreate->m_bRet = true;
      return;
   }*/

   if(!::mediaplay::view::Initialize(&papp->GetMidiCentral()))
   {
      return;
   }

//  db()->AddListener(this);


   

   


   m_pwaveplayer = AfxBeginThread < audWavePlayer >(get_app());

   m_pplaylistcallback = new MusicalPlayerPlaylistCallback(
      &papp->GetMusicalPlayerCentral(),
      get_document());

   m_dataid = "KaraokeMainView";
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
///  if (::userbase::view::OnCreate(lpCreateStruct) == -1)
   //   return -1;
   
/*   ca77::application * papp = (ca77::application *) &System;
   
   papp->TwfInitializeDescendants(GetSafeHwnd(), true);*/
   
   //XfplayerDoc * pDoc = get_document();
   
  
   //db()->UpdateImagePaths();
//   m_sliderProgress.CreateEx(WS_EX_TRANSPARENT,NULL, NULL, WS_CHILD | WS_VISIBLE , rect(0, 0, 0, 0), this, "slider_progress");
//   m_sliderProgress.SetRange(0, 4096);
   
//   db_server * pdb = db();
//   CDBStringSet * pStringSet = pdb->get_db_str_set();
//   string str;
//   data_get("Images.CurrentPath", str);fOn
//   BackViewGetInterface().GetImageChange().m_wstrCurrentImagePath.SetOEM(str);
   
   //simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (GetParentFrame());
   //pframe->SetActiveView(this);

   //m_sliderProgress.SetStreamingVelocityMode(&m_dscalarVelocity, 10,
     // &m_dscalarPosition, 10);
   //m_spgraphics->Attach(GetDC()->get_os_data());
   //m_gdi.m_spgraphics->Attach(GetDC()->get_os_data());
   //return 0;

   
}


void XfplayerView::ClearLyricLines(bool bRender)
{
   m_lyrictemplatelines.clear_lines();
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   visual::font * pfont = GetLyricFont();
   ASSERT(pfont != NULL);
   
/*   ::ca::rgn_sp rgn;
   rgn.CreateRectRgn(0, 0, 0, 0);
   RECT clientRect;
   GetClientRect(&clientRect);
   if(bRender)
   {
      rect rgnBox;
      rgn.GetRgnBox(rgnBox);
      if(!rgnBox.is_null())
      {
//         TwiRedraw(NULL, &rgn);
      }
   }
   rgn.delete_object();*/

   //get_document()->::mediaplay::document::get_data()->GetKaraokeData().SetInterface(&get_document()->::mediaplay::document::get_data()->m_karaokeinterface);
}






void XfplayerView::RenderScore(::ca::graphics * pdc, bool bClearBackground)
{
   UNREFERENCED_PARAMETER(bClearBackground);
   //CSingleLock slGdi(&m_csGdi, TRUE);
   
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   //   primitive_array < visual::font *> * pFonts = GetLyricFonts();
   //   ASSERT(pFonts != NULL);
   visual::font * pfont = GetLyricFont();
   ASSERT(pfont != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   
   
   double dScoreRate = m_dScoreRate;
   if(dScoreRate > 1.0)
      dScoreRate = 1.0;
   else if(dScoreRate < 0.0)
      dScoreRate = 0.0;
   string str;
   str.Format("%0.0f", dScoreRate * 100.0);
   rect rect;
   GetClientRect(&rect);
   
   //ASSERT(pdc != NULL);
   //point ptViewport = pdc->GetViewportOrg();
   
   //rect rectClipBox;
//   pdc->GetClipBox(rectClipBox);
   
   //rect rectClipBoxClient = rectClipBox;
   //rectClipBoxClient.offset(-ptViewport);
   
   class rect rectPlacement;
  // m_lineScore.GetPlacement(rectPlacement);
   
   //rect rectIntersect;
/*   if(!rectIntersect.intersect(
      rectPlacement,
      rectClipBoxClient))
   {
      return;
   }*/
   
   //gcom::backview::Interface & backview = BackViewGetInterface();
   
   //CSingleLock sl1Back(&backview.GetBackCS(), TRUE);
   
//   m_lineScore.SetTwi(this);
   m_lineScore.SetTextEffect(XfplayerViewLine::EffectEmbossed);
   
   m_lineScore.PrepareLine(
      pdc,
      str,
      0,
      &rect);

   m_lineScore.Invalidate();
   m_lineScore.to(
      get_app(),
      pdc,
      true,
      &rect,
      *((rect_array *) NULL),
      &count,
      false,
      RGB(0, 255, 255),
      m_penScore);
   
   //   m_dwScoreLastUpdateTime = timeGetTime();
   //   slGdi.Unlock();
   
}

void XfplayerView::RedrawScore(bool bBackRedraw)
{
   UNREFERENCED_PARAMETER(bBackRedraw);
   _001RedrawWindow();
}


void XfplayerView::_001OnContextMenu(gen::signal_object * pobj) 
{
   //SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   LyricViewLines & lyriclines = GetLyricLines();
   int iLine, iToken, iChar;
   class point ptCursor;
   ptCursor = pmouse->m_pt;
   if(m_lyrictemplatelines.hit_test(ptCursor, iLine, iToken, iChar)
      == ::user::line_hit_link)
   {
      string str;
      lyriclines.GetLink(str, iLine, iToken, iChar);
      m_strCurrentLink = str;
      ::userbase::menu menu(get_app());
   }
   else
   {
      ::userbase::menu menu(get_app());
      //if (menu.LoadMenu(IDR_POPUP_LYRICVIEW))
      if(menu.LoadXmlMenu("vmp/popup_lyricview.xml"))
      {
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         frame_window * pframe = GetParentFrame();
         menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptCursor.x, ptCursor.y, pframe);
      }
   }
}

void XfplayerView::PrepareTitle()
{
   XfplayerDoc * pDoc = get_document();
//   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   XFInfoHeader * pInfoHeader = pDoc->::mediaplay::document::get_data()->HelperGetXFInfoHeader();
   const char * lpSongName = pDoc->::mediaplay::document::get_data()->HelperGetXFInfoHeaderSet()->m_strSongName;
   //XFInfoHeaderLS *pInfoHeaderLS = pDoc->m_pInfoHeaderLS;
   
   string str;
   string wstrFormat;
   stringa wstrArray;
   //bool bHasTitle;
   
   /*   if(pInfoHeaderLS == NULL)
   //   { */
   if(lpSongName != NULL)
   {
      str = lpSongName;
      str.trim_left();
      str.trim_right();
      pDoc->m_bHasTitle = !str.is_empty();
      if(pDoc->m_bHasTitle)
      {
         wstrArray.add(str);
      }
   }
   if(pInfoHeader != NULL)
   {
      pInfoHeader->m_straComposer.get_format_string(str, "/");
      str.trim_left();
      str.trim_right();
      if(!str.is_empty())
      {
         throw not_implemented_exception();
         //wstrFormat.Format(IDS_FORMAT001_COMPOSER, str);
         wstrArray.add(wstrFormat);
      }
      
      pInfoHeader->m_straLyricist.get_format_string(str, "/");
      str.trim_left();
      str.trim_right();
      if(!str.is_empty())
      {
         throw not_implemented_exception();
         //wstrFormat.Format(IDS_FORMAT001_LYRICIST, str);
         wstrArray.add(wstrFormat);
      }
      
      pInfoHeader->m_straArranger.get_format_string(str, "/");
      str.trim_left();
      str.trim_right();
      if(!str.is_empty())
      {
         throw not_implemented_exception();
         //wstrFormat.Format(IDS_FORMAT001_ARRANGER, str);
         wstrArray.add(wstrFormat);
      }
      
      pInfoHeader->m_straPerformer.get_format_string(str, "/");
      str.trim_left();
      str.trim_right();
      if(!str.is_empty())
      {
         throw not_implemented_exception();
         //wstrFormat.Format(IDS_FORMAT001_PERFORMER, str);
         wstrArray.add(wstrFormat);
      }
      
      pInfoHeader->m_straProgrammer.get_format_string(str, "/");
      str.trim_left();
      str.trim_right();
      if(!str.is_empty())
      {
         throw not_implemented_exception();
         //wstrFormat.Format(IDS_FORMAT001_PROGRAMMER, str);
         wstrArray.add(wstrFormat);
      }
      
   }
   XfplayerViewLine * pviewline;
   XfplayerViewLine objViewLine(get_app());
   //    XfplayerViewLine & refViewLine = objViewLine;
   
   while(wstrArray.get_size() > m_titleLines.get_size())
   {
      //refViewLine = new XfplayerViewLine();
      m_titleLines.add(objViewLine);
      pviewline = &m_titleLines.element_at(m_titleLines.get_size() - 1);
      pviewline->SetAutoSize(true);
      pviewline->m_iLeft = 0;
      //        pviewline->SetRenderWindow(this);
      //        pviewline->SetRenderCriticalSection(&m_csGdi);
   }
//   m_titleLines.SetTwi(this);
   m_titleLines.SetEffect(XfplayerViewLine::EffectEmbossed);
   int i;
   RECT rect;
   GetClientRect(&rect);
   if(pDoc->m_bHasTitle)
   {
      //      UpdateTitleFonts(strArray[0]);
      /*m_titleLines[0].PrepareLine(
         m_spgraphics,
         wstrArray.element_at(0),
         0,
         System.font_central().GetTitleFonts(),
         &rect);*/
      i = 1;
   }
   else
      i = 0;
   for(; i < wstrArray.get_size(); i++)
   {
      //      UpdateSubTitleFonts(strArray[i]);
      /*m_titleLines[i].PrepareLine(
         m_spgraphics,
         wstrArray.element_at(i),
         0,
         System.font_central().GetSubTitleFonts(),
         &rect);*/
   }
   
   for(i = wstrArray.get_size(); i < m_titleLines.get_size(); i++)
   {
      //m_titleLines[i].Reset();
   }
   
   //int i;
   //for(i = 0; i < m_titleLines.get_size(); i++)
   //{
   //   delete m_titleLines[i];
   //}
   //m_titleLines.remove_all();
   
   
   
   
}

void XfplayerView::ShowTitle(bool bShow, bool bRedraw)
{
   m_bTitleVisible = bShow;

//   XfplayerDoc * pDoc = (XfplayerDoc *) get_document();

   XfplayerViewLine * pviewline;
   
   for(int i = 0; i < m_titleLines.get_size() ; i++)
   {
      pviewline = &m_titleLines[i];
      pviewline->Show(bShow);
   }

   if(bRedraw)
   {
      RedrawTitle();
   }
   
}

void XfplayerView::RedrawTitle()
{
   if(m_titleLines.get_size() <= 0)
      return;
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   XfplayerDoc * pDoc = (XfplayerDoc *) get_document();
   ASSERT(pDoc != NULL);
   frame_window *pframe = GetParentFrame();
   if(pframe == NULL)
      return;
   if(!base < KaraokeSDIFrame >::bases(pframe))
      return;
   ASSERT(pframe != NULL);
   rect_array recta;
   
   RECT rect;
   GetClientRect(&rect);
   XfplayerViewLine * pviewline;
   int i;
   TRACE("XfplayerView::update_title 1 slGdi.Lock\n");
//   ::ca::graphics * pdcScreen = m_spgraphics;
   
//   gcom::backview::Interface::CGraphics & graphics = BackViewGetInterface().GetGraphics();
//   CSingleLock sl1Back(&BackViewGetInterface().GetBackCS(), TRUE);
   
   if(pDoc->m_bHasTitle)
   {
      pviewline = &m_titleLines[0];
/*      pviewline->to(
         pdcScreen,
         NULL,         
         true,
         &rect,
         recta,
         &count,
         System.font_central().GetTitleFonts(), 
         false,
         m_crTitle,
         m_penTitle);*/
      //      }
      i = 1;
   }
   else 
      i = 0;
   for(; i < m_titleLines.get_size() ; i++)
   {
      pviewline = &m_titleLines[i];
      
      /*pviewline->to(
         pdcScreen,
         NULL,
         true,
         &rect,
         recta,
         &count,
         System.font_central().GetSubTitleFonts(), 
         false,
         m_crSubTitle,
         m_penSubTitle);*/
   }
   int iStartTop = 100;
   if(m_bTitleVisible)
   {
      TEXTMETRIC textMetric;
      int yPos;
      if(m_titleLines.get_size() >= 1)
      {
         m_spgraphics->SelectObject(System.font_central().GetTitleFonts()->operator [](0)->GetFont());
         pviewline = &m_titleLines[0];
         pviewline->m_iTop = iStartTop;
      }
      if(m_titleLines.get_size() >= 2)
      {
         if(pDoc->m_bHasTitle)
         {
            m_spgraphics->SelectObject(System.font_central().GetTitleFonts()->operator [](0)->GetFont());
            m_spgraphics->GetTextMetrics(&textMetric);
            yPos = pviewline->m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
         m_spgraphics->SelectObject(System.font_central().GetSubTitleFonts()->operator [](0)->GetFont());
         m_spgraphics->GetTextMetrics(&textMetric);
         if(!pDoc->m_bHasTitle)
         {
            yPos = pviewline->m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
         int pos;
         for(pos = yPos, i = 1; i < m_titleLines.get_size() ; i++)
         {
            pviewline = &m_titleLines[i];
            //            if(pViewLine)
            //            {
            pviewline->m_iTop = pos;
            //            }
            pos += textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
      }
      
      RECT clientRect;
      GetClientRect(&clientRect);
      
      if(!m_spgraphics->SetMapMode(MM_TEXT))
      {
         TRACE0("Could not set ::collection::map mode to MM_TEXT.\n");
      }
      if(pDoc->m_bHasTitle)
      {
         pviewline = &m_titleLines[0];
         //         if(pViewLine)
         //         {
         /*pviewline->to(
            pdcScreen,
            NULL,
            true,
            &rect,
            recta,
            &count,
            System.font_central().GetTitleFonts(), 
            true,
            m_crTitle,
            m_penTitle);*/
         //         }
         i = 1;
      }
      else 
         i = 0;
      for(; i < m_titleLines.get_size() ; i++)
      {
         pviewline = &m_titleLines[i];
         //         if(pViewLine)
         //         {
         
         //if
         //pViewLine->m_dFillRate = (0.8 * (double) (timeGetTime() - m_iPlayStartTime)) / pDoc->m_TokensMillis.get_at(dynamicdata.m_iPlayingTokenIndex) +0.2;
         //if(pViewLine->m_dFillRate > 1.0)
         //   pViewLine->m_dFillRate = 1.0;
         
/*         pviewline->to(
            pdcScreen,
            NULL,
            true,
            &rect,
            recta,
            &count,
            System.font_central().GetSubTitleFonts(), 
            true,
            m_crSubTitle,
            m_penSubTitle);*/
         //         }
      }
      
   }
   _001RedrawWindow();
   
}


void XfplayerView::UpdateTitleFonts(const char * lpStr)
{
   UNREFERENCED_PARAMETER(lpStr);
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   primitive_array < visual::font *> * pFonts = System.font_central().GetTitleFonts();
   ASSERT(pFonts != NULL);
   visual::font * pFont;
   int i, iSize;
   iSize = pFonts->get_size();
   for(i = 0; i < iSize; i++)
   {
      pFont = pFonts->operator [](i);
      pFont->SetDC(m_spgraphics);
      //      pFont->AddGlyphs(lpStr);
      pFont->ClearDC();
   }
   
}

void XfplayerView::UpdateSubTitleFonts(const char * lpStr)
{
   
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   primitive_array < visual::font *> * pFonts = System.font_central().GetSubTitleFonts();
   ASSERT(pFonts != NULL);
   visual::font * pFont;
   int i, iSize;
   iSize = pFonts->get_size();
   for(i = 0; i < iSize; i++)
   {
      pFont = pFonts->operator [](i);
      pFont->SetDC(m_spgraphics);
      pFont->AddGlyphs(lpStr);
      pFont->ClearDC();
   }
   
}


void XfplayerView::SetOnSizeEnabled(bool bEnabled)
{
   m_bOnSizeEnabled = bEnabled;
}




void XfplayerView::PostPlayMessage()
{
   PostMessage(WM_USER, 1, ID_PLAY);
}

string XfplayerView::GetPlainTextV001()
{
   string str;
   string wstrPlainTextV001;
   string wstrText;
   XfplayerDoc * pDoc = get_document();
   
   string wstrPathName;
   wstrPathName = pDoc->::mediaplay::document::get_data()->get_path_name();
 
   // throw not_implemented_exception
   //str.load_string(IDS_FILENAME);
   wstrText += str;
   wstrText += L": ";
   wstrText += wstrPathName;
   wstrText += L"\r\n";
   wstrText += L"\r\n";
   
   wstrPlainTextV001 += wstrText;
   wstrText.Empty();
   int i;
   for(i = 0; i < m_titleLines.get_size(); i++)
   {
      //if(!m_titleLines[i].m_chars.is_empty())
      //{
      wstrText += m_titleLines[i].m_str;
      wstrText += L"\r\n";
      //}
   }
   if(!wstrText.is_empty())
   {
      wstrPlainTextV001 += wstrText;
      wstrPlainTextV001 += L"\r\n";
   }
   wstrText.Empty();
   string wstrMain;
   LyricViewLines & lyriclines = GetLyricLines();
   for(i = 0; i < lyriclines.GetLineCount(); i++)
   {
      wstrMain = lyriclines.get(i).GetMainString();
      wstrText += wstrMain;
      wstrText += L"\r\n";
   }
   if(!wstrText.is_empty())
   {
      wstrPlainTextV001 += wstrText;
   }
   return wstrPlainTextV001;
}

//BOOL XfplayerView::OnHelpInfo(HELPINFO* pHelpInfo) 
//{
// TODO: add your message handler code here and/or call default
//   
//   return ::userbase::view::OnHelpInfo(pHelpInfo);
//}

void XfplayerView::OnPlaypause() 
{
   
}


void XfplayerView::TimerProc(UINT nID)
{
   if(m_bDestroy)
      return;
   
   DWORD dwTime = GetTickCount();
   if(dwTime - m_dwTimerProcLastTime < TimeOutResolution)
   {
      return;
   }
   m_dwTimerProcLastTime = dwTime;
   

   // Mudei na hora 2003-03-19 23, de SendMessage
   // para PostMessage, confiando que essa função
   // possa receber eventos encavalados de Timer,
   // e que a condição logo acima seja satisfeita
   // a fim de que as chamadas do PostMessage abaixo
   // obedecam a resolução de estouro de temporização.
   // 
   PostMessage(VMSM_TIMER, nID);
}

BOOL XfplayerView::DestroyWindow() 
{
   
   return ::userbase::view::DestroyWindow();
}

void XfplayerView::PrepareSongLabelLine()
{
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   frame_window * pframe = GetParentFrame();
   ASSERT(pframe != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   
   
//   db_server * pDataCentral = dynamic_cast < db_server * > (&System.db());
   if(!IsWindow())
      return;
   TRACE("XfplayerView::PrepareSongLabeLine 1 slGdi.Lock\n");
   rect clientRect;
   GetClientRect(&clientRect);
   visual::font * lpFont = System.font_central().GetSongLabelFont();
   TEXTMETRIC textMetric;
   m_spgraphics->SelectObject(lpFont->GetFont());
   m_spgraphics->GetTextMetrics(&textMetric);
   rect rectWindow;
//   m_sliderProgress.GetWindowRect(rectWindow);
  // ScreenToClient(rectWindow);
//   m_lineSongLabel.m_iRight = clientRect.right;
//   m_lineSongLabel.m_iTop = rectWindow.top - (textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading);
   //m_lineSongLabel.SetTwi(this);
//   m_lineSongLabel.SetEmbossPen(&m_penSubTitle);
  // m_lineSongLabel.SetForegroundColor(RGB(0,0,0));
//   m_lineSongLabel.m_bAutoSizeY = true;
  // m_lineSongLabel.SetAnimateIncrement(2.0);
/*   if(m_lineSongLabel.GetVmsFontCount() <= 0)
   {
      m_lineSongLabel.AddVmsFont(System.font_central().GetSongLabelFont());
   }*/
   string str;
//   pDoc->HelperGetXFInfoHeader()->GetFormatV001(pDoc->HelperGetXFInfoHeaderSet()->m_strSongName, str);
  // m_lineSongLabel.PrepareLine(m_spgraphics, str,0, m_lineSongLabel.GetFonts(), clientRect);
   //m_lineSongLabel.SetAnimateType(XfplayerViewLine::AnimateRHL);
   //m_lineSongLabel.SetTextEffect(XfplayerViewLine::EffectSimple);
   TRACE("XfplayerView::PrepareSongLabeLine 1 slGdi.UnLock\n");
   
}

void XfplayerView::DefaultLayoutPlaylist()
{
   if(m_pplaylistframe == NULL)
      return;
   rect rect;
   GetClientRect(rect);
   m_pplaylistframe->SetWindowPos(
      ZORDER_TOP,
      rect.width() / 4,
      0,
      rect.width() / 2,
      rect.height() / 5,
      SWP_SHOWWINDOW);
//   bool bVisible = m_pplaylistframe->IsWindowVisible() != 0;
   //PlaylistView * m_pplaylistipwnd = GetPlaylistView();
   //return;
   /*    if(m_pplaylistipwnd == NULL)
   return;
   rect rect;
   GetClientRect(rect);
   m_pplaylistipwnd->MoveWindow(rect.width() / 4,
   0,
   rect.width() / 2,
   rect.height() / 5);
   */
}


::view *  XfplayerView:: GetPlaylistView()
{
   //    if(m_pplaylistipwnd == NULL)
   if(m_pplaylistframe == NULL)
      return NULL;
   else
      //        return m_pplaylistipwnd->GetPlaylistView();
      return m_pplaylistframe->GetActiveView();
}


bool XfplayerView::OnAttachPlaylistDoc()
{
   AttachPlaylistView();
   return true;
}

bool XfplayerView::OnDetachPlaylistDoc()
{
   DetachPlaylistView();
   return true;
}

bool XfplayerView::AttachPlaylistView()
{
   XfplayerFrameWndInterface * pframeinterface = GetParentFrameInterface();
//   frame_window * pframe = GetParentFrame();
   if(pframeinterface != NULL)
   {
      if(pframeinterface->IsCompactMode())
      {
         return true;
      }
   }
   PlaylistDoc * lpPlaylistDoc = get_document()->GetPlaylistDoc();
   ASSERT(lpPlaylistDoc != NULL);
   
   ::userbase::view * lpPlaylistView = lpPlaylistDoc->GetFirstAttachableView();
   if(lpPlaylistView == NULL)
      return false;

   m_pplaylistframe = dynamic_cast < PlaylistFrame * > (lpPlaylistView->GetParentFrame());
   //   m_pplaylistframe = (PlaylistFrame *) lpPlaylistDoc->::view->GetParentFrame();
   m_pplaylistframe->ShowWindow(SW_HIDE);
   
//   m_pplaylistframe->TransparentFrameWndChild(GetSafeHwnd());
   
   DefaultLayoutPlaylist();
   
//   m_transparentframewnda.Update(this);
//   m_transparentframewnda.layout();
   
//   BackViewUpdateBuffer(false);
  // _001RedrawWindow();
   
   return true;
}


::view * XfplayerView::DetachPlaylistView()
{
   ::view  * lpplaylistview = GetPlaylistView();
   //if(lpPlaylistView == NULL)
   //{
   //  return NULL;
   //}
   if(m_pplaylistframe == NULL)
   {
      return NULL;
   }
   ASSERT(m_pplaylistframe != NULL);
   //    m_pplaylistframe->OnAttachWnd();
//   m_pplaylistframe->TransparentFrameWndFrame();
   m_pplaylistframe = NULL;
   //m_pplaylistipwnd = NULL;
   //    PlaylistDoc * lpPlaylistDoc = lpPlaylistView->get_document();
   //  ASSERT(lpPlaylistDoc != NULL);
   //    to(FALSE);
//   m_transparentframewnda.Update(this);
   
//   BackViewUpdateBuffer(false);
  // _001RedrawWindow();
   
   return lpplaylistview;
}


/*CPlaylistInPlaceWnd * XfplayerView::GetPlaylistInPlaceWnd()
{
return m_pplaylistipwnd;
}*/


int XfplayerView::GetChildrenClip()
{
   ::user::interaction* pWndChild  = GetTopWindow();
   ::user::interaction* pWndFirstChild = pWndChild;
   ::ca::rgn_sp rgnChild(get_app());
   rect rectClient;
   rect rectChild;
   GetClientRect(rectClient);
   m_rgnChildren->SetRectRgn(rectClient);
   rgnChild->CreateRectRgn(0, 0, 0, 0);
   return TRUE;
   while(pWndChild != NULL)
   {
      
      //        CPlaylistInPlaceWnd * pPlaylistWnd;
      //        if(base < CSliderV008 >::bases(pWndChild))
      //      {
      //                rgnChild.SetRectRgn(rectChild);
      //              m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
      //    }
      //  else
      //{
      if(pWndChild->IsWindowVisible())
      {
         if(pWndChild->GetWindowRgn((HRGN)rgnChild->get_os_data()) != ERROR)
         {
            pWndChild->GetWindowRect(rectChild);
            ScreenToClient(rectChild);
            rgnChild->OffsetRgn(rectChild.top_left());
            m_rgnChildren->CombineRgn(m_rgnChildren, rgnChild, RGN_DIFF);
         }
         else
         {
            pWndChild->GetWindowRect(rectChild);
            ScreenToClient(rectChild);
            //TRACE("XfplayerView::GetChildrenClip\n");
            //TRACE("rectClipBox.left  : %d, ", rectChild.left);
            //TRACE("rectClipBox.top   : %d, ", rectChild.top);
            //TRACE("rectClipBox.right : %d, ", rectChild.right);
            //TRACE("rectClipBox.bottom: %d\n", rectChild.bottom);
            
            rgnChild->SetRectRgn(rectChild);
            m_rgnChildren->CombineRgn(m_rgnChildren, rgnChild, RGN_DIFF);
         }
      }
      //        }
      pWndChild = pWndChild->GetNextWindow();
      if(pWndChild  == NULL || pWndChild->_get_handle() == pWndFirstChild->_get_handle())
         break;
   }
   return TRUE;
}

void XfplayerView::OnDisplayChange(int iBitsPerPixel, size sizeScreen)
{
   UNREFERENCED_PARAMETER(iBitsPerPixel);
   UNREFERENCED_PARAMETER(sizeScreen);
}


BOOL XfplayerView::OnMouseWheel(UINT nFlags, short zDelta, point pt) 
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(zDelta);
   UNREFERENCED_PARAMETER(pt);
   // TODO: add your message handler code here and/or call default
   
//  return ::userbase::view::OnMouseWheel(nFlags, zDelta, pt);
   return TRUE;
}




void XfplayerView::OnViewImageTile() 
{
   SetBkImageFlags(gcom::backview::ImagePlacementTile);
}

void XfplayerView::OnViewImageZoomall() 
{
   SetBkImageFlags(gcom::backview::ImagePlacementZoomAll);
}

void XfplayerView::OnViewImageStretch() 
{
   SetBkImageFlags(gcom::backview::ImagePlacementStretch);
   
}

void XfplayerView::OnViewImageZoomextend() 
{
   SetBkImageFlags(gcom::backview::ImagePlacementZoomExtend);
}


void XfplayerView::OnUpdateViewImageTile(cmd_ui * pcmdui) 
{
   bool bSelected = gcom::backview::Interface::GetCurrentImagePlacement() == gcom::backview::ImagePlacementTile;
   pcmdui->Enable(!bSelected);
   pcmdui->_001SetCheck(bSelected);
   
}

void XfplayerView::OnUpdateViewImageZoomall(cmd_ui * pcmdui) 
{
   bool bSelected = gcom::backview::Interface::GetCurrentImagePlacement() == gcom::backview::ImagePlacementZoomAll;
   pcmdui->Enable(!bSelected);
   pcmdui->_001SetCheck(bSelected);
   
}

void XfplayerView::OnUpdateViewImageZoomextend(cmd_ui * pcmdui) 
{
   bool bSelected = gcom::backview::Interface::GetCurrentImagePlacement() == gcom::backview::ImagePlacementZoomExtend;
   pcmdui->Enable(!bSelected);
   pcmdui->_001SetCheck(bSelected);
   
}

VMSRESULT XfplayerView::SetBkImageFlags(int iFlags)
{
   gcom::backview::Interface::SetCurrentImagePlacement((gcom::backview::EImagePlacement) iFlags);
   string str;
   gcom::backview::Interface::GetCurrentImagePath(str);
   str.Format("Images.%us.flags", str);
   data_set(str, gcom::backview::Interface::GetCurrentImagePlacement());
   gcom::backview::Interface::ImageChangePostEvent(gcom::backview::EventFlagChanged);
   return VMSR_SUCCESS;
}

void XfplayerView::OnUpdateViewImageStretch(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   bool bSelected = gcom::backview::Interface::GetCurrentImagePlacement() == gcom::backview::ImagePlacementStretch;
   pcmdui->Enable(!bSelected);
   pcmdui->_001SetCheck(bSelected);
   
}

void XfplayerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   UNREFERENCED_PARAMETER(nRepCnt);
   UNREFERENCED_PARAMETER(nFlags);
   // TODO: add your message handler code here and/or call default
   BOOL bAlpha = false;
   int iValue;
   switch(nChar)
   {
   case VK_NUMPAD0:
   case '0':
      iValue = 0;
      break;
   case VK_NUMPAD1:
   case '1':
      iValue = 1;
      break;
   case VK_NUMPAD2:
   case '2':
      iValue = 2;
      break;
   case VK_NUMPAD3:
   case '3':
      iValue = 3;
      break;
   case VK_NUMPAD4:
   case '4':
      iValue = 4;
      break;
   case VK_NUMPAD5:
   case '5':
      iValue = 5;
      break;
   case VK_NUMPAD6:
   case '6':
      iValue = 6;
      break;
   case VK_NUMPAD7:
   case '7':
      iValue = 7;
      break;
   case VK_NUMPAD8:
   case '8':
      iValue = 8;
      break;
   case VK_NUMPAD9:
   case '9':
      iValue = 9;
      break;
   default:
      {
         iValue = -1;
         bAlpha = isalpha(nChar);
      }
      break;
   }
   
   
   
   if(iValue >= 0 ||
      bAlpha)
   {
/*      CToolV023Dialog * pdlg = new CToolV023Dialog();
      pdlg->m_pobjSource = get_document();
      pdlg->create(pdlg->IDD);
      simple_edit * pEdit = (simple_edit *) &pdlg->m_edit;
      string str;
      if(bAlpha)
      {
         str = (char) nChar;
      }
      else
      {
         str.Format("%d", iValue);
      }
      pEdit->SetWindowText(str);
      int iLen = str.get_length();
      pEdit->SetSel(iLen, iLen);
      rect rectWindow;
      GetWindowRect(rectWindow);
      pdlg->SetWindowPos(
         &wndTop,
         rectWindow.center().x,
         rectWindow.center().y,
         0, 0,
         SWP_SHOWWINDOW |
         SWP_NOSIZE);
      pEdit->SetFocus(); */
      
   }
   else
   {
      KaraokeSDIFrame * pframe = GetKaraokeSDIFrame();
      if(pframe != NULL
         && nChar == VK_ESCAPE
         && pframe->IsFullScreen())
      {
         pframe->WfiFullScreen(false, true);
      }
      else
      {
//        ::userbase::view::OnKeyDown(nChar, nRepCnt, nFlags);
      }
   }
   
   
}

void XfplayerView::PrepareProgressSlider()
{
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
   frame_window * pframe = GetParentFrame();
   ASSERT(pframe != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL);
   //   primitive_array < visual::font *> * pFonts = GetLyricFonts();
   //   ASSERT(pFonts != NULL);
   //TRACE("Entered in XfplayerView::UpdateBackgroundImage(int, int)\n");
//   db_server * pDataCentral = dynamic_cast <db_server * > (&System.db());
   if(!IsWindow())
      return;
   TRACE("XfplayerView::PrepareProgressSlider 1 slGdi.Lock\n");
   rect clientRect;
   GetClientRect(&clientRect);
   visual::font * lpFont = System.font_central().GetSongLabelFont();
   TEXTMETRIC textMetric;
   m_spgraphics->SelectObject(lpFont->GetFont());
   m_spgraphics->GetTextMetrics(&textMetric);
   
   TRACE("XfplayerView::PrepareProgressSlider 1 slGdi.UnLock\n");
   
   rect rectWindow;
   rectWindow.left = clientRect.left;
   rectWindow.right = clientRect.right;
   rectWindow.bottom = clientRect.bottom - 3;
   rectWindow.top = clientRect.bottom - (textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading);
/*   m_sliderProgress.MoveWindow(
      rectWindow.left, rectWindow.top,
      rectWindow.width(), rectWindow.height(),
      true);*/
   
   
   
   
   
}

void XfplayerView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   UNREFERENCED_PARAMETER(nSBCode);
   UNREFERENCED_PARAMETER(nPos);
   UNREFERENCED_PARAMETER(pScrollBar);
/*  if(pScrollBar->GetDlgCtrlId() == IDC_SLIDER_PROGRESS)
   {
//      ExecuteSetProgressRate(m_sliderProgress.GetRate(), NULL);
   }*/

//  ::userbase::view::OnHScroll(nSBCode, nPos, pScrollBar);
}

void XfplayerView::UpdateDrawingObjects()
{
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(pApp != NULL);
//   gen::savings & savings = System.savings();
   
   
   gcom::backview::Interface::UpdateDrawingObjects();
   
   
   
   m_enhmetafile = GetEnhMetaFile(pApp->m_strModuleFolder + "vmp447cv.emf");
   if(m_enhmetafile == NULL)
   {
      pApp->RestoreEnhancedMetaFiles();
   }
   m_enhmetafile = GetEnhMetaFile(pApp->m_strModuleFolder + "vmp447cv.emf");
   if(m_enhmetafile != NULL)
   {
      GetEnhMetaFileHeader(
         m_enhmetafile,
         sizeof(m_emh),
         &m_emh);
   }
   rect rectClient;
   GetClientRect(rectClient);
//   int cx = rectClient.width();
//   int cy = rectClient.height();
   //    ::ca::graphics * pdcScreen = TwiGetDC();
//   ::ca::graphics * pdcScreen = m_spgraphics;
   //    m_voiceSpectrum.SetDC(pdcScreen, &GetBackDC());
   //    TwiReleaseDC(pdcScreen);
   
}


afx_msg LRESULT XfplayerView::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   UpdateDrawingObjects();
//   TwiRedraw();
   return true;
}



void XfplayerView::OnViewPlaylist() 
{
   // TODO: add your command handler code here
   PlaylistDoc * pplaylistdoc = get_document()->GetPlaylistDoc();
   if(pplaylistdoc == NULL)
   {
      PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral(get_app());
      playlistcentral.OpenDefaultPlaylist(true);
      get_document()->Attach(playlistcentral.GetCurrentPlaylist());
   }
   else if(GetPlaylistView() != pplaylistdoc->GetFirstAttachableView())
   {
      AttachPlaylistView();
   }
   
}


afx_msg LRESULT XfplayerView::OnVMSNotify(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   //LRESULT lresult;
/*   _vmsgui::NMHDR * lpnmhdr = (_vmsgui::NMHDR *) lParam;
   if(wParam == IDC_EDIT)
   {
      if(lpnmhdr->code == E17N_KEYDOWN)
      {
         OnKeyDownEdit(lpnmhdr, &lresult);
         return lresult;
      }
      else if(lpnmhdr->code == E17N_SYSKEYDOWN)
      {
         OnSysKeyDownEdit(lpnmhdr, &lresult);
         return lresult;
      }
      
   }
   else
   {
      ASSERT(FALSE);
   }
    */  
   return -1;
}
/*afx_msg void XfplayerView::OnKeyDownEdit( _vmsgui::NMHDR * pNotifyStruct, LRESULT * result )
{
   ASSERT(FALSE);
   _vmsgui::EDIT_KEYINFO  & nmkey = *(_vmsgui::EDIT_KEYINFO*)pNotifyStruct;
   if(nmkey.wVKey == VK_RETURN)
   {
      simple_edit * pEdit = (simple_edit *) pEdit->from_handle(nmkey.hdr.hwndFrom);
      string str;
      pEdit->GetWindowText(str);
      const char * lpcsz = str;
      LPTSTR lpend;
      long lValue = _tcstol(lpcsz, &lpend, 10);
      if(lpend != lpcsz)
      {
         pEdit->ShowWindow(SW_HIDE);
         pEdit->clear();
         vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
         XfplayerDoc * pPlayerDoc  = get_document();
         if(pPlayerDoc != NULL)
         {
            XfplayerView * pLyricView = pPlayerDoc->GetLyricView();
            if(pLyricView != NULL)
            {
               PlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
               if(pPlaylistDoc == NULL)
               {
                  PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral();
                  playlistcentral.OpenDefaultPlaylist();
                  pPlayerDoc->Attach(pPlaylistDoc);
               }
               pPlaylistDoc->AddSong(lValue, true, true, true);
               pPlaylistDoc->update_all_views(NULL);
               //                     KaraokeSDIFrame *pframe = (KaraokeSDIFrame *) pApp->GetMainWnd();
               //                   pframe->UpdateReserveList();
            }
         }
      }
      *result = -1;
   }
   else if(nmkey.wVKey == VK_ESCAPE)
   {
      simple_edit * pEdit = (simple_edit *) pEdit->from_handle(nmkey.hdr.hwndFrom);
      pEdit->ShowWindow(SW_HIDE);
      *result = -1;
   }
   else if(nmkey.wVKey == VK_NUMPAD0 ||
      nmkey.wVKey == VK_NUMPAD1 ||
      nmkey.wVKey == VK_NUMPAD2 ||
      nmkey.wVKey == VK_NUMPAD3 ||
      nmkey.wVKey == VK_NUMPAD4 ||
      nmkey.wVKey == VK_NUMPAD5 ||
      nmkey.wVKey == VK_NUMPAD6 ||
      nmkey.wVKey == VK_NUMPAD7 ||
      nmkey.wVKey == VK_NUMPAD8 ||
      nmkey.wVKey == VK_NUMPAD9 ||
      nmkey.wVKey == '0' ||
      nmkey.wVKey == '1' ||
      nmkey.wVKey == '2' ||
      nmkey.wVKey == '3' ||
      nmkey.wVKey == '4' ||
      nmkey.wVKey == '5' ||
      nmkey.wVKey == '6' ||
      nmkey.wVKey == '7' ||
      nmkey.wVKey == '8' ||
      nmkey.wVKey == '9')
   {
      *result = 0;
   }
   else
   {
      //        MessageBeep(MB_OK);
      *result = -1;
   }
}*/
/*afx_msg void XfplayerView::OnSysKeyDownEdit( _vmsgui::NMHDR * pNotifyStruct, LRESULT * result )
{
   _vmsgui::EDIT_KEYINFO  & nmkey = *(_vmsgui::EDIT_KEYINFO*)pNotifyStruct;
   if(nmkey.wVKey == VK_ESCAPE)
   {
      simple_edit * pEdit = (simple_edit *) pEdit->from_handle(nmkey.hdr.hwndFrom);
      pEdit->ShowWindow(SW_HIDE);
      *result = -1;
   }
   else
   {
      *result = -1;
   }
}
*/
void XfplayerView::OnViewLyricviewSpectrum() 
{
   //   m_voiceSpectrum.SetVisible(!m_voiceSpectrum.GetVisible());
   //    if(!m_voiceSpectrum.GetVisible())
   //  {
   //    m_voiceSpectrum.to(NULL, 0, 0);
   //}
}

void XfplayerView::OnUpdateViewLyricviewSpectrum(cmd_ui * pcmdui) 
{
   UNREFERENCED_PARAMETER(pcmdui);
   //    pcmdui->SetCheck(m_voiceSpectrum.GetVisible() ? 1 : 0);
   
}

void XfplayerView::OnViewSongInfo() 
{
//   m_lineSongLabel.Show(!m_lineSongLabel.IsVisible());
}

void XfplayerView::OnUpdateViewSongInfo(cmd_ui * pcmdui) 
{
//   pcmdui->SetCheck(m_lineSongLabel.IsVisible() ? 1 : 0);
   pcmdui->Enable();
}


void XfplayerView::OnViewNextImageNow() 
{
   gcom::backview::Interface::ImageChangePostEvent(gcom::backview::EventLoadNow);
}

void XfplayerView::OnViewSkipImageAlways() 
{
   TRACE("XfplayerView::OnViewSkipImageAlways In");
//   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
//   db_server * pDataCentral = dynamic_cast < db_server * > (&System.db());
/*   CDBTableV004 * pTable = pDataCentral->GetExcludedImageTable();
   TRACE("XfplayerView::OnViewSkipImageAlways Middle 1");
   string str;
   string str;
   BackViewGetInterface().GetCurrentImagePath(str);
   gen::international::UnicodeToOEM(str, str);
   pTable->AddText(str);
   TRACE("XfplayerView::OnViewSkipImageAlways Middle 2");
   pDataCentral->OnImagesDirsModified();
   TRACE("XfplayerView::OnViewSkipImageAlways Middle 3");
   //PostMessage(WM_USER, 17, BkImageChangeEventLoadNow);
   BackViewGetInterface().ImageChangePostEvent(gcom::backview::EventLoadNow);
   TRACE("XfplayerView::OnViewSkipImageAlways Out");*/
}

/*BOOL XfplayerView::RedrawWindow(string str)
{

  }
*/
VMSRESULT XfplayerView::to(::ca::graphics * pdc, LPRECT lprect)
{
   rect rectClient = *lprect;
   if(lprect == NULL)
   {
      GetClientRect(rectClient);
   }
   else
   {
      rectClient = *lprect;
   }
   rect rectScreen = rectClient;
   ClientToScreen(rectScreen);
   RenderView(pdc, rectClient, NULL);
   return VMSR_SUCCESS;
}


VMSRESULT XfplayerView::to(::ca::graphics * pdc, ::ca::rgn *lprgn)
{
   ASSERT(FALSE);
   ASSERT(lprgn != NULL);
   
   point ptOffset(0, 0);
   ClientToScreen(&ptOffset);
   
   ::ca::rgn rgnScreen;
   rgnScreen.CreateRectRgn(0, 0, 0, 0);
   rgnScreen.CopyRgn(lprgn);
   rgnScreen.OffsetRgn(ptOffset);
   
   RenderView(pdc, NULL, lprgn);
   return VMSR_SUCCESS;
}


// lprect in client coordinates
VMSRESULT XfplayerView::RenderView(
                                    ::ca::graphics * pdc,
                                    LPRECT lprect,
                                    ::ca::rgn * lprgn)
{
   
   ASSERT(pdc != NULL);
   point ptViewport = pdc->GetViewportOrg();
   rect rect;
   
   ::ca::application * papp = &System;
   if(papp == NULL)
   {
      // if main application is null, there's no reason
      // for painting anything...
      return VMSR_SUCCESS;
   }
   ASSERT(papp != NULL);
   
//   gen::savings & savings = System.savings();
   
   
   //   KaraokeSDIFrame * pframe = (KaraokeSDIFrame *) GetParentFrame();
   frame_window * pframe = GetParentFrame();
   if(pframe == NULL)
   {
      // if main frame is null, there's no reason
      // for painting anything...
      return VMSR_SUCCESS;
   }
   ASSERT(pframe != NULL);
   //ASSERT_KINDOF(KaraokeSDIFrame, pframe);
   
   XfplayerDoc *pdoc = get_document();
   ASSERT(pdoc != NULL); // if document is null, there's something wrong
   
   ::mus::midi::sequence & seq = pdoc->::mediaplay::document::get_data()->GetMidiSequence();
   
   
   ::mus::midi::file  & file = seq.GetFile();
   ikar::data & data = GetKaraokeData();
   ikar::static_data & staticdata = data.GetStaticData();
   
   EventsTracksV1 * peventsarray = NULL;
   if(!file.IsNull())
   {
      peventsarray = &staticdata.m_eventsTracksForPositionCB;
   }
   
   
   
   //    primitive_array < visual::font *> *
   //      pFonts = GetLyricFonts();
   //visual::font *
//      pfont = GetLyricFont();
   
//   db_server * pDataCentral = dynamic_cast < db_server * > (&System.db());
   
   class rect rectPlaylist;
   if(m_pplaylistframe != NULL)
   {
      m_pplaylistframe->GetWindowRect(rectPlaylist);
      ScreenToClient(rectPlaylist);
   }
   /*    if(m_pplaylistipwnd != NULL)
   {
   m_pplaylistipwnd->GetWindowRect(rectPlaylist);
   ScreenToClient(rectPlaylist);
}*/
   
   if(!IsWindow())
      return VMSR_SUCCESS;
   
   class rect rectClient;
   GetClientRect(rectClient);
//   int cx = rectClient.width();
//   int cy = rectClient.height();
   
   LyricEventsV2 * pevents;
   if(peventsarray == NULL ||
      peventsarray->get_size() <= staticdata.m_str2aRawTokens.get_size())
      pevents = NULL;
   else
   {
      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.get_size());
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   
   LyricEventsV2 * peventsBB = NULL;
   if(!file.IsNull() && staticdata.m_eventsTracksForBouncingBall.get_size() > 0)
   {
      peventsBB = (LyricEventsV2 *) staticdata.m_eventsTracksForBouncingBall.operator [](0);
      ASSERT(peventsBB != NULL);
      ASSERT(peventsBB->GetClassOrder() == 2);
   }
   
//   TEXTMETRIC & textMetric = pfont->m_tm;
   
   
   
   ::ca::rgn_sp rgnOld(get_app());
   class rect rectParam;
   if(lprgn != NULL)
   {
      rgnOld->CreateRectRgn(0, 0, 0, 0);
      GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnOld->get_os_data());
      ::ca::rgn rgn;
      rgn.CopyRgn(lprgn);
      rgn.OffsetRgn(ptViewport);
      pdc->SelectClipRgn(&rgn);
      lprgn->GetRgnBox(rectParam);
   }
   else if (lprect != NULL)
   {
      rgnOld->CreateRectRgn(0, 0, 0, 0);
      GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnOld->get_os_data());
      
      rectParam = *lprect;
      ::ca::rgn rgn;
      rgn.CreateRectRgnIndirect(rectParam);
      rgn.OffsetRgn(ptViewport);
      pdc->SelectClipRgn(&rgn);
   }
   else
   {
      ASSERT(FALSE);
   }
   
   if(rectParam.width() <= 0 || rectParam.height() <= 0)
      return VMSR_SUCCESS;
   
   return RenderView(pdc);
}

VMSRESULT XfplayerView::RenderView(::ca::graphics * pdc)
{
   
   /*ASSERT(pdc != NULL);
   point ptViewport = pdc->GetViewportOrg();
   
   ::ca::application * papp = get_app();
   if(papp == NULL)
   {
      // if main application is null, there's no reason
      // for painting anything...
      return VMSR_SUCCESS;
   }
   ASSERT(papp != NULL);
   
//   gen::savings & savings = System.savings();
   
   XfplayerDoc *pdoc = get_document();
   ASSERT(pdoc != NULL); // if document is null, there's something wrong
   
   ::mus::midi::sequence & seq = pdoc->::mediaplay::document::get_data()->GetMidiSequence();
   ::mus::midi::file & file = seq.GetFile();
   ikar::data & data = GetKaraokeData();
//   ikar::dynamic_data & dynamicdata = data.GetDynamicData();
   ikar::static_data & staticdata = data.GetStaticData();
   
   EventsTracksV1 * peventsarray = NULL;
   if(!file.IsNull())
   {
      peventsarray = &staticdata.m_eventsTracksForPositionCB;
   }
   
   
   
//   visual::font *
//      pfont = GetLyricFont();
   
   //db_server * pDataCentral = db();
   
   rect rectPlaylist;
   if(m_pplaylistframe != NULL)
   {
      m_pplaylistframe->GetWindowRect(rectPlaylist);
      ScreenToClient(rectPlaylist);
   }
   
   
   if(!IsWindow())
      return VMSR_SUCCESS;
   
   rect rectClient;
   GetClientRect(rectClient);
//   int cx = rectClient.width();
//   int cy = rectClient.height();
   
   LyricEventsV2 * pevents;
   if(peventsarray == NULL ||
      peventsarray->get_size() <= staticdata.m_str2aRawTokens.get_size())
      pevents = NULL;
   else
   {
      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.get_size());
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   
   LyricEventsV2 * peventsBB = NULL;
   if(!file.IsNull() && staticdata.m_eventsTracksForBouncingBall.get_size() > 0)
   {
      peventsBB = (LyricEventsV2 *) staticdata.m_eventsTracksForBouncingBall.operator [](0);
      ASSERT(peventsBB != NULL);
      ASSERT(peventsBB->GetClassOrder() == 2);
   }
   
//   TEXTMETRIC & textMetric = pfont->m_tm;
   
   
   // get clip region
   ::ca::rgn_sp rgnClip(get_app());
   rgnClip->CreateRectRgn(0, 0, 0, 0);
   int iClip = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnClip->get_os_data());
   
   // get clip region box in client coordinates
   rect rectClip;
   if(iClip == 1)
   {
      rgnClip->GetRgnBox(rectClip);
      rectClip.offset(-pdc->GetViewportOrg());
   }
   else
   {
      GetClientRect(rectClip);
   }*/
   
   mediaplay::view::_001OnDraw(pdc);   
   
   return VMSR_SUCCESS;
}




void XfplayerView::OnParentNotify(UINT message, LPARAM lParam) 
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(lParam);
//  ::userbase::view::OnParentNotify(message, lParam);
   
}


afx_msg LRESULT XfplayerView::OnVMSTimer(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   DWORD dwTime = GetTickCount();
   
   if(dwTime - m_dwVMSTimerLastTime < TimeOutResolution)
   {
      return 0;
   }
   m_dwVMSTimerLastTime = dwTime;
   
   TimerMachine((ETimer) wParam);
   
   return 0;
}


void XfplayerView::OnProgressRateChange()
{
//   XfplayerDoc * pdoc = get_document();

   OnProgressRateChange(GetProgressRate());
   
}


void XfplayerView::OnProgressRateChange(double dRate)
{
   m_dProgressRate = dRate;
//   m_sliderProgress.SetRate(dRate);

}

void XfplayerView::_001OnDraw(::ca::graphics * pdc)
{
   RenderView(pdc);
}

void XfplayerView::_001OnTopDraw(::ca::graphics * pdc)
{
   RenderScore(pdc, false);
}



/*primitive_array < visual::font *> *
XfplayerView::GetLyricFonts()
{
KaraokeSDIFrame * pframe = (KaraokeSDIFrame *) GetParentFrame();

  if(pframe->m_bCompactSize)
  return System.font_central().GetLyricViewCompactFonts_();
  else
  return System.font_central().GetLyricViewFonts_();
    }*/

bool XfplayerView::IsPlaylistViewAttached()
{
   //    return m_pplaylistipwnd != NULL;
   return m_pplaylistframe != NULL;
}

void XfplayerView::OnXfplayerMenubar() 
{
   // TODO: add your command handler code here
/*   CMenuV033 menu(BaseMenuCentral::GetMenuCentral());
   if (menu.LoadMenu(IDR_XFPLAYER_MENUBAR))
   {
      point point = GetCurrentMessage()->pt;
          CMenuV033* pPopup = (CMenuV033 *) menu.GetSubMenu(0);
          ASSERT(pPopup != NULL);
          simple_frame_window * pframe = GetParentFrame();
          pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
             point.x, point.y,
             (::ca::window *) pframe);
   }   */
}


bool XfplayerView::SetCompactMode(bool bCompact)
{
   bool b = m_bCompactMode;
   m_bCompactMode = bCompact;
   return b;
   
}

bool XfplayerView::SetFullScreen(bool bFullScreen)
{
   bool b = m_bFullScreen;
   m_bFullScreen = bFullScreen;
   return b;
   
}

void XfplayerView::layout()
{
   
   if(m_ptemplateTab != NULL)
   {
      document * pdoc = m_ptemplateTab->get_document(0);
      if(pdoc != NULL)
      {
         ::userex::pane_tab_view * pview = pdoc->get_typed_view < ::userex::pane_tab_view > ();
         if(pview != NULL)
         {
            //pview->GetParentFrame()->SetWindowPos(NULL, 23, 23, 800, 300, SWP_NOZORDER);
         }
      }
   }
      

   
   if(!m_bInitialized)
      return;
   
   
   rect rectClient;
   GetClientRect(rectClient);
   
   int cx = rectClient.width();
   int cy = rectClient.height();
   
   
   
   
   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   if(pApp == NULL)
   {
      // if main application is null, there's no reason
      // for painting anything...
      return;
   }
   ASSERT(pApp != NULL);
   
//   gen::savings & savings = System.savings();
   
   frame_window * pframe = GetParentFrame();
   if(pframe == NULL)
   {
      // if main frame is null, there's no reason
      // for painting anything...
      return;
   }
   
   //    rect rectClient;
   //  GetClientRect(rectClient);
   
   
   //    int cx = rectClient.width();
   //  int cy = rectClient.height();
   
   
   if(cx <= 0 || cy <= 0)
      return;
   
   
   
   ASSERT(pframe != NULL);
   XfplayerDoc *pDoc = get_document();
   ASSERT(pDoc != NULL); // if document is null, there's something wrong
   
   
   ::mus::midi::sequence & seq = pDoc->::mediaplay::document::get_data()->GetMidiSequence();
   ::mus::midi::file & file = seq.GetFile();
   ikar::data & data = GetKaraokeData();
   ikar::static_data & staticdata = data.GetStaticData();
   
   EventsTracksV1 * peventsarray = NULL;
   if(!file.IsNull())
   {
      peventsarray = &staticdata.m_eventsTracksForPositionCB;
   }
   
   //    primitive_array < visual::font *> * pFonts = NULL;
   //  if(pApp)
   //{
   //  pFonts = GetLyricFonts();
   //}
   visual::font * pfont = NULL;
   if(pApp)
   {
      pfont = GetLyricFont();
   }
   
//   db_server * pDataCentral = dynamic_cast < db_server * > (&System.db());
   
   rect rectPlaylist;
   if(m_pplaylistframe != NULL)
   {
      m_pplaylistframe->GetWindowRect(rectPlaylist);
      ScreenToClient(rectPlaylist);
   }
   /*    if(m_pplaylistipwnd != NULL)
   {
   m_pplaylistipwnd->GetWindowRect(rectPlaylist);
   ScreenToClient(rectPlaylist);
    }*/
   
   if(!IsWindow())
      return;
   
   
   PrepareProgressSlider();
   
   PrepareSongLabelLine();
   
   LayoutLyricTemplateLines();
   
   LayoutLyricLines();
   
   LayoutKaraokeBouncingBall();
   
   
   LyricEventsV2 * pevents;
   if(peventsarray == NULL ||
-      peventsarray->get_size() <= staticdata.m_str2aRawTokens.get_size())
      pevents = NULL;
   else
   {
      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.get_size());
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
   }
   m_lineScore.m_iRight = cx;
   m_lineScore.m_iTop = m_iRightVerticalShift;
   m_lineScore.m_iLeft = cx - 200;
   m_lineScore.m_iBottom = m_iRightVerticalShift + 100;
   
   m_lineScore.PrepareLine(
      m_spgraphics,
      "0",
      0,
      rectClient);
   
   int iBottom;
   if(m_lineScore.IsVisible())
   {
      iBottom = m_lineScore.m_iBottom;
   }
   else
   {
      iBottom = m_iRightVerticalShift;
   }
   
   
   
   TEXTMETRIC textMetric;
   //   if(pFonts->get_size() > 0)
   //   {
   //      m_spgraphics->SelectObject(pFonts->operator [](0)->GetFont());
   m_spgraphics->SelectObject(pfont->GetFont());
   m_spgraphics->GetTextMetrics(&textMetric);
   //   }
   //   m_voiceSpectrum.SetPlacement(
   //      m_spgraphics,
   //      cx / 100,
   //      cx / 100,
   //      cx / 6,
   //      cy / 7);
   
   string str;
   
//   visual::font * lpFontSongLabel = System.font_central().GetSongLabelFont();
   
   
   
   m_spgraphics->SelectObject(m_font);
   m_spgraphics->GetTextMetrics(&textMetric);
   
   int iStartTop = 100;
   if(m_titleLines.get_size() > 0)
   {
      XfplayerViewLine objViewLine(get_app());
      XfplayerViewLine &refViewLine = objViewLine;
      int i, yPos;
      if(m_titleLines.get_size() >= 1)
      {
         m_spgraphics->SelectObject(pfont->GetFont());
         refViewLine = m_titleLines[0];
         //            if(m_pplaylistipwnd != NULL)
         if(m_pplaylistframe != NULL)
         {
            //refViewLine.m_iTop = max(max(rectPlaylist.bottom, m_voiceSpectrum.GetBottom()), rectSliderKeyShift.bottom);
            //refViewLine.m_iTop = max(max(rectPlaylist.bottom, iStartTop), rectSliderKeyShift.bottom);
            refViewLine.m_iTop = max(rectPlaylist.bottom, iStartTop);
         }
         else
         {
            //refViewLine.m_iTop = m_voiceSpectrum.GetBottom();
            refViewLine.m_iTop = iStartTop;
         }
      }
      if(m_titleLines.get_size() >= 2)
      {
         if(pDoc->m_bHasTitle)
         {
            m_spgraphics->SelectObject(System.font_central().GetTitleFonts()->operator [](0)->GetFont());
            m_spgraphics->GetTextMetrics(&textMetric);
            yPos = refViewLine.m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
         m_spgraphics->SelectObject(System.font_central().GetSubTitleFonts()->operator [](0)->GetFont());
         m_spgraphics->GetTextMetrics(&textMetric);
         if(!pDoc->m_bHasTitle)
         {
            yPos = refViewLine.m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
         int pos;
         for(pos = yPos, i = 1; i < m_titleLines.get_size() ; i++)
         {
            refViewLine = m_titleLines[i];
            refViewLine.m_iTop = pos;
            pos += textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
         }
      }
   }

   ::ca::graphics * pdc = GetDC();
   m_lineScore.GetFont()->delete_object();
   m_lineScore.GetFont()->CreatePointFont(120, "Geneva Bold", pdc);
   ReleaseDC(pdc);
   
//   m_transparentframewnda.Update(this);
  // m_transparentframewnda.layout();
   
}

void XfplayerView::OnTwiInitialize()
{
   UpdateDrawingObjects();
   
   
}



bool XfplayerView::CreateBitmap(::ca::graphics *pdc, ::ca::bitmap *pbitmapOld, ::ca::bitmap *pbitmap, BITMAP * pbmp, int cx, int cy)
{
   int cxout = cx + 30;
   int cyout = cy + 30;
   
   pdc->SelectObject(pbitmapOld);
   bool bCreate = true;
   if(pbitmap->get_os_data() != NULL)
   {
      if(!pbitmap->GetBitmap(pbmp))
      {
         return false;
      }
      if(pbmp->bmWidth >= cx &&
         pbmp->bmHeight >= cy)
      {
         bCreate = false;
      }
      
   }
   if(bCreate)
   {
      pbitmap->delete_object();
      if(!pbitmap->CreateCompatibleBitmap(m_spgraphics, cxout, cyout))
      {
         return false;
      }
   }
   if(!pdc->SelectObject(pbitmap))
   {
      return false;
   }
   if(bCreate)
   {
      pdc->FillSolidRect(rect(0, 0, cxout, cyout), RGB (0, 0, 0));
   }
   return true;
   
}


void XfplayerView::PrepareBouncingBall()
{
   m_lpbouncingball->Prepare();
}

void XfplayerView::OnChangeCompactMode(XfplayerViewUpdateHint * puh)
{

   UNREFERENCED_PARAMETER(puh);

   keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
   PrepareLyricTemplateLines();
   PrepareLyricLines();
   PrepareBouncingBall();
   rect rectClient;
   GetClientRect(rectClient);
//   TwiRedraw(rectClient);
   XfplayerFrameWndInterface * pframeinterface = GetParentFrameInterface();
   if(pframeinterface != NULL)
   {
      if(pframeinterface->IsCompactMode())
      {
         if(IsPlaylistViewAttached())
         {
            DetachPlaylistView();
         }
      }
   }

   
}

void XfplayerView::OnChangeFullScreen(XfplayerViewUpdateHint *puh)
{
   
   UNREFERENCED_PARAMETER(puh);
   keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
   PrepareLyricTemplateLines();
   PrepareLyricLines();
   PrepareBouncingBall();
}

bool XfplayerView::ShowAudioSpectrum(bool bShow)
{
   if(bShow)
   {
      XfplayerDoc * pdoc = get_document();
      ::userbase::document * pdocNew = (::userbase::document *) pdoc->OpenAudioSpectrumDoc(this, true);
      if(pdocNew != NULL)
      {
/*         CTransparentFrameWndV8 * pframe = pdoc->GetAudioSpectrumFrame();
         pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
         pframe->SetMaxSize(&size(400, 200), true);
         pframe->SetMinSize(&size(50, 50), true);
         pframe->GetWndFramework()->AddListener(this);*/
      }
      int iShow = 1;
      data_set("AudioSpectrum.Show", iShow);
//      GetParentFrame()->SetActiveView(this);
   }
   else
   {
      XfplayerDoc * pdoc = get_document();
      pdoc->CloseAllAudioSpectrumDocuments();
      int iShow = 0;
      data_set("AudioSpectrum.Show", iShow);
   }
//   m_transparentframewnda.Update(this);
   return true;
   
}
/*bool XfplayerView::ShowLevelMeter(bool bShow)
{
   if(bShow)
   {
      XfplayerDoc * pdoc = get_document();
      ::userbase::document * pdocNew = (::userbase::document *) pdoc->OpenLevelMeterDoc(true);
      if(pdocNew != NULL)
      {
         CTransparentFrameWndV8 * pframe = (CTransparentFrameWndV8 *) pdoc->GetLevelMeterFrame();
         pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
         pframe->SetMaxSize(&size(800, 600), true);
         pframe->SetMinSize(&size(50, 50), true);
         pframe->ShowWindow(SW_SHOWNORMAL);
         pframe->GetWndFramework()->AddListener(this);
      }
      
      int iShow = 1;
      data_set("LevelMeter.Show", iShow);
      GetParentFrame()->SetActiveView(this);   
   }
   else
   {
      
      XfplayerDoc * pdoc = get_document();
      pdoc->CloseAllLevelMeterDocuments();
      int iShow = 0;
      data_set("LevelMeter.Show", iShow);
   }
   m_transparentframewnda.Update(this);
   return true;
}*/

afx_msg LRESULT  XfplayerView::OnAppLanguage(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   if(wParam == gen::application::WPARAM_LANGUAGE_UPDATE)
   {
      layout();
   }
   else if(wParam == vmsp::Configuration::WPARAM_LANGUAGE_KARAOKEENCODING_UPDATE)
   {
      XfplayerDoc * pdoc = get_document();
      pdoc->OnKaraokeEncodingChange();
   }
   return 0;
}
afx_msg LRESULT XfplayerView::OnAppNotify(WPARAM wParam, LPARAM lParam)
{
   switch(wParam)
   {
   case APPN_CHILDDELETE:
      {
         ASSERT(FALSE);
         /*void * lpvoid = (void *) lParam;
         if(lpvoid == m_pkcs1wndLevelMeter)
         {
         m_pkcs1wndLevelMeter = NULL;
         }
         else if(lpvoid == m_plevelmeterwnd)
         {
         m_plevelmeterwnd = NULL;
         }
         else if(lpvoid == m_pkcs1wndAudioSpectrum)
         {
         m_pkcs1wndAudioSpectrum = NULL;
         }
         else if(lpvoid == m_paudiospectrumwnd)
         {
         m_paudiospectrumwnd = NULL;
      }*/
         
      }
      break;
   case APPN_OPENLINK:
      {
         const wchar_t * lpcsz = (const wchar_t *) lParam;
         string str;
         gen::international::UnicodeToOEM(str, lpcsz);
         ::ShellExecute(GetTopLevelParent()->_get_handle(), "open", str, NULL, NULL, SW_RESTORE);
      }
      break;
      
   }
   return 0;
}

/*void XfplayerView::OnWindowLevelmeter() 
{
   XfplayerDoc * pdoc = get_document();
   ShowLevelMeter(!pdoc->IsLevelMeterOpened());
   CTransparentFrameWndV8 * pframe = pdoc->GetLevelMeterFrame();
   if(pframe != NULL)
   {
      pframe->TransparentFrameWndFrame();
   }
   
}

void XfplayerView::OnViewLevelmeter() 
{
   XfplayerDoc * pdoc = get_document();
   ShowLevelMeter(!pdoc->IsLevelMeterOpened());
   CTransparentFrameWndV8 * pframe = pdoc->GetLevelMeterFrame();
   if(pframe != NULL)
   {
      pframe->TransparentFrameWndChild();
   }
}*/

void XfplayerView::OnScoringEnable(bool bEnable)
{
   m_lineScore.Show(bEnable);
   layout();
}


void XfplayerView::_001OnViewAudioSpectrum(gen::signal_object * pobj) 
{
   
   UNREFERENCED_PARAMETER(pobj);

   XfplayerDoc * pdoc = get_document();
   ShowAudioSpectrum(!pdoc->IsAudioSpectrumOpened());
   simple_frame_window * pframe = pdoc->GetAudioSpectrumFrame();
   if(pframe != NULL)
   {
//      pframe->TransparentFrameWndChild();
   }
   
}

void XfplayerView::OnWindowAudiospectrum() 
{
   XfplayerDoc * pdoc = get_document();
   ShowAudioSpectrum(!pdoc->IsAudioSpectrumOpened());
/*   CTransparentFrameWndV8 * pframe = pdoc->GetAudioSpectrumFrame();
   if(pframe != NULL)
   {
      pframe->TransparentFrameWndFrame();
   }*/
   
}

/*void XfplayerView::OnViewPlayercontrolsetv19() 
{
   XfplayerDoc * pdoc = get_document();
   ShowPlayerControlSetV19(!pdoc->IsPlayerControlSetV19ViewOpened());
   CTransparentFrameWndV8 * pframe = pdoc->GetPlayerControlSetV19Frame();
   if(pframe != NULL)
   {
      pframe->TransparentFrameWndChild();
   }
}

void XfplayerView::OnUpdateViewPlayercontrolsetv19(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsPlayerControlSetV19ViewOpened());
}

void XfplayerView::OnWindowPlayercontrolsetv19() 
{
   XfplayerDoc * pdoc = get_document();
   ShowPlayerControlSetV19(!pdoc->IsPlayerControlSetV19ViewOpened());
   CTransparentFrameWndV8 * pframe = pdoc->GetPlayerControlSetV19Frame();
   if(pframe != NULL)
   {
      pframe->TransparentFrameWndFrame();
   }
   
}

void XfplayerView::OnUpdateWindowPlayercontrolsetv19(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsPlayerControlSetV19ViewOpened());
   
}
*/

/*

void XfplayerView::OnUpdateWindowLevelmeter(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsLevelMeterOpened());
}

void XfplayerView::OnUpdateWindowAudiospectrum(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsAudioSpectrumOpened());
   
}

void XfplayerView::OnUpdateViewLevelmeter(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsLevelMeterOpened());
   
}

void XfplayerView::OnUpdateViewAudiospectrum(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   XfplayerDoc * pdoc = get_document();
   pcmdui->SetCheck(
      pdoc->IsAudioSpectrumOpened());
   
   
}

*/
bool XfplayerView::TextDocHelperAdd(string &str)
{
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   if(m_pvmstextdocHelper == NULL)
   {
      m_pvmstextdocHelper = papp->OpenTextFile(NULL);
   }
   if(m_pvmstextdocHelper == NULL)
      return false;
// linux   m_pvmstextdocHelper->GetView()->GetRichEditCtrl().ReplaceSel(str);
   return true;
}

bool XfplayerView::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   simple_frame_window * pframewnd = m_pplaylistframe;
   ::user::interaction* pwndFocus = System.get_focus_guie();
   if(pwndFocus != NULL)
   {
      pwndFocus = System.window_from_os_data(pwndFocus->_get_handle());
   }
   if(pframewnd != NULL 
      && (pframewnd = dynamic_cast < simple_frame_window * > ( System.window_from_os_data(pframewnd->_get_handle()))) != NULL 
      && pframewnd != NULL
      &&
      (pwndFocus == NULL
      ||   pframewnd == pwndFocus
      || 
      (pframewnd->GetActiveView() != NULL &&
      pframewnd->GetActiveView() == pwndFocus
      )
      )
      )
   {
      if(pframewnd->_001OnCmdMsg(pcmdmsg))
         return TRUE;
   }
   
   return ::userbase::view::_001OnCmdMsg(pcmdmsg);
}

/*
void XfplayerView::OnPointerClear(PlaylistDoc *pdoc)
{
   
}
*/


bool XfplayerView::IsCompactMode()
{
   XfplayerFrameWndInterface * pframeinterface = GetParentFrameInterface();
   if(pframeinterface != NULL)
   {
      return pframeinterface->IsCompactMode();
   }
   else
   {
      return false;
   }
}

KaraokeSDIFrame * XfplayerView::GetKaraokeSDIFrame()
{
   frame_window * pframe = GetParentFrame();
   if(base < KaraokeSDIFrame >::bases(pframe))
      return dynamic_cast < KaraokeSDIFrame * > (pframe);
   else
      return NULL;
   
}

void XfplayerView::LayoutDynamicChild(bool bMakeVisible)
{
   UNREFERENCED_PARAMETER(bMakeVisible);
   //m_transparentframewnda.Update(this);
   //m_transparentframewnda.layout();
   return;
   
   
   
   
   
   rect rectClient;
   rect rectFrame;
   GetClientRect(rectClient);
   ::user::interaction* pwnd = GetTopWindow();
   while(pwnd != NULL)
   {
/*      if(base < CTransparentFrameWndV4 >::bases(pwnd))
      {
         CTransparentFrameWndV4 * pframe = (CTransparentFrameWndV4 *) pwnd;
         pframe->GetWindowRect(rectFrame);
         ScreenToClient(rectFrame);
         rectFrame.ConstraintV5(rectClient, size(30, 30));
         UINT nFlags;
         if(pframe->IsWindowVisible()
            || bMakeVisible)
            nFlags = SWP_SHOWWINDOW
            | SWP_NOZORDER;
         else
            nFlags = SWP_HIDEWINDOW
            | SWP_NOZORDER;
         pframe->SetWindowPos(
            0,
            rectFrame.left,
            rectFrame.top,
            rectFrame.width(),
            rectFrame.height(),
            nFlags);
      }*/
      pwnd = pwnd->GetNextWindow();
   }
   
}

/*bool XfplayerView::ShowPlayerControlSetV19(bool bShow)
{
   if(bShow)
   {
      XfplayerDoc * pdoc = get_document();
      ::userbase::document * pdocNew = (::userbase::document *) pdoc->OpenPlayerDoc(true);
      if(pdocNew != NULL)
      {
         CPlayerControlSetV19Frame * pframe = pdoc->GetPlayerControlSetV19Frame();
         pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
         pframe->GetWndFramework()->AddListener(this);
         pframe->ShowWindow(SW_SHOWNORMAL);
      }
      int iShow = 1;
      data_set("PlayerControlSetV19.Show", iShow);
   }
   else
   {
      XfplayerDoc * pdoc = get_document();
      CPlayerDoc * pplayerdoc = pdoc->GetPlayerDoc();
      if(pplayerdoc != NULL)
      {
         POSITION pos = pplayerdoc->get_view_count();
         ::userbase::view * pview;
         while(pos != NULL)
         {
            pview = pplayerdoc->get_view(pos);
            if(base < CPlayerControlSetV19View >::bases(pview))
            {
               pplayerdoc->remove_view(pview);
            }
         }
      }
      int iShow = 0;
      data_set("PlayerControlSetV19.Show", iShow);
   }
   m_transparentframewnda.Update(this);
   return true;
   
}*/




void XfplayerView::WFLOnDock(window_frame::WorkSet *pwf, ::user::interaction *pwnd)
{
   UNREFERENCED_PARAMETER(pwf);
   UNREFERENCED_PARAMETER(pwnd);
   //m_transparentframewnda.Update(this);
   //m_transparentframewnda.layout();
}

void XfplayerView::OnOpenLink() 
{
   ASSERT(!m_strCurrentLink.is_empty());   
   ::ShellExecute(GetTopLevelParent()->_get_handle(), "open", m_strCurrentLink, NULL, NULL, SW_RESTORE);
}

bool XfplayerView::Initialize(midi_central * pmidicentral)
{

   if(mediaplay::view::Initialize(pmidicentral))
      return false;

   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   
   XfplayerDoc * pdoc = get_document();
   SetKaraokeData(&pdoc->::mediaplay::document::get_data()->GetKaraokeData());
   
   simple_frame_window     * pframe = dynamic_cast < simple_frame_window * > (
      dynamic_cast < ::ca::window * > (GetParentFrame()));
   
   pframe->SetActiveView(this);
   
   RECT rect;
   GetClientRect(&rect);

   
   
   if(papp->command_line().m_nShellCommand !=
      gen::command_line::FileDDE)
   {
      if(!m_bInitialized)
      {
         
         int iShow = 0;
         data_get("LevelMeter.Show", iShow);
//         ShowLevelMeter(iShow != 0);
         
         iShow = 0;
         data_get("AudioSpectrum.Show", iShow);
         ShowAudioSpectrum(iShow != 0);
         
         iShow = 0;
         data_get("PlayerControlSetV19.Show", iShow);
//         ShowPlayerControlSetV19(iShow != 0);
      }
   }
   
   SetOnSizeEnabled();
   if(!m_bInitialized)
   {
      int iShow = m_bBouncingBall ? 1 : 0;
      data_get("Karaoke.Bouncing Ball", iShow);
      ShowBouncingBall(iShow != 0);
      
   }
   
   
   m_dwLastShiftUpdate = 0;
   ::userbase::view::_001OnInitialUpdate(NULL);
   XfplayerViewUpdateHint uh;
   uh.AddType(XfplayerViewUpdateHint::UpdateStart);
   pdoc->update_all_views(NULL, 0, &uh);
   UpdateDrawingObjects();
   m_bInitialized = true;
   
   layout();
   
   if(m_ptimerwnd == NULL)
   {
/*      gen::CHighThreadContainer::AppGetHighThread().PostCreateTimer(
         5,
         TimerMain,
         this);*/
   }
   
   gcom::backview::Interface::Enable(true);

   EnableScoring(true);
   
   SetTimer(100, 23, NULL);

   return true;
}


void XfplayerView::WFLOnClose(
                               window_frame::WorkSet * pwf,
                               ::user::interaction * pwnd)
{
   UNREFERENCED_PARAMETER(pwf);
   UNREFERENCED_PARAMETER(pwnd);
/*   if(base < CTransparentFrameWndV8 >::bases(pwnd))
   {
      CTransparentFrameWndV8 * pframe = (CTransparentFrameWndV8 *) pwnd;
      ::userbase::view * pview = pframe->GetActiveView();
      if(base < CLevelMeterView >::bases(pview))
      {
         data_set("LevelMeter.Show", 0);
      }
      else if(base < AudioSpectrumView >::bases(pview))
      {
         data_set("AudioSpectrum.Show", 0);
      }
   }
   else if(base < CPlayerControlSetV19Frame >::bases(pwnd))
   {
      CPlayerControlSetV19Frame * pframe = (CPlayerControlSetV19Frame *) pwnd;
      ::userbase::view * pview = pframe->GetActiveView();
      if(base < CPlayerControlSetV19View >::bases(pview))
      {
         data_set("PlayerControlSetV19.Show", 0);
      }
   }*/
   
}

bool XfplayerView::TwiHasTranslucency()
{
   return false;
}


void XfplayerView::TransitionEffectRunStepAsync()
{
   m_evTransitionEffectRunStep.SetEvent();
}







/*
LyricViewLines & XfplayerView::GetLyricLines()
{
   return m_lyrictemplatelines.GetLines();
}
*/
void XfplayerView::OnImageDirectoriesChange()
{
   gcom::backview::Interface::ImageChangePostEvent(gcom::backview::EventLoadNow);
   TRACE("CDataCentral::OnImagesDirsModified Out");
}



XfplayerFrameWndInterface * XfplayerView::GetParentFrameInterface()
{
   return dynamic_cast < XfplayerFrameWndInterface * > ( GetParentFrame());
}








bool XfplayerView::DBListenMinusOne(bool bSave, const char * lpcszPathName, bool &bMinusOne)
{
   string strListenMinusOne;
   strListenMinusOne.Format("%s.ListenMinusOne", lpcszPathName);
   if(bSave)
   {
      data_set(strListenMinusOne, bMinusOne ? 1 : 0);
      return true;
   }
   else
   {
      int i;
      if(!data_get(strListenMinusOne, i))
      {
         return false;
      }
      bMinusOne = (i == 0) ? false : true;
      return true;
   }
   
}


/*
void XfplayerView::OnEvent(_vmsdb::EDBEvent eevent)
{
   if(eevent == _vmsdb::DBEventImageDirectorySetChange)
   {
      OnImageDirectoryChange();
   }
}
*/
/*
thread * XfplayerView::GetMidiPlayerCallbackThread()
{
   return &gen::CHighThreadContainer::AppGetHighThread();
}
*/
/*::mus::midi::sequence & XfplayerView::GetMidiSequence()
{
   return get_document()->GetMidiSequence();
}
*/
/*void XfplayerView::_001OnMmsgDone(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   ::mus::midi::player::NotifyEvent * pdata = (::mus::midi::player::NotifyEvent *) pbase->m_lparam;
   OnMmsgDone(pdata);
}

void XfplayerView::OnMmsgDone(::mus::midi::player::NotifyEvent * pdata)
{
   //MidiPlayerInterface::OnMmsgDone(pseq, lpmdd);
//  ASSERT(pseq == &get_document()->HelperGetMidiSequence());

   XfplayerDoc * pdoc = get_document();
   
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(papp != NULL);
   
   //   CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
   //   ASSERT(pFrame != NULL);
   
   XfplayerThreadV2 * pThreadV2  = papp->GetThreadV2();
   ASSERT(pThreadV2 != NULL);
      /*if(pseq->IsSettingPosition())
      {
         OnProgressRateChange();
      }*/

      //if(IsScoringEnabled() && !GetScoring()->IsEnabled())
  /* if(pdata->m_enotifyevent == ::mus::midi::player::NotifyEventPlaybackStart)
   {
      if(IsScoringEnabled())
      {
         StartScoring(true);
      }
   }
   /*audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   ASSERT(pwavein != NULL);
   if(pdoc->m_bPlay)
   {
      
      double dRate =   GetProgressSlider()->CalcScalar();
      if(dRate == 0.0)
      {
         //Show Title
         ShowTitle();
         
         // time to let the title be visible
         m_msPlayTimeOut = timeGetTime() + 3000;
         
         //       Sleep(3000);
      }
      else
      {
         m_msPlayTimeOut = timeGetTime();
      }
      m_bWaitingToPlay = true;
      pdoc->m_bPlay = false;
      
   }
   else if(pseq->IsChangingTempo())
   {
      TRACE("XfplayerDoc::OnMmsgDone pseq->IsChangingSettingPosition()\n");
   }
   else if(lpmdd->SequenceWasInSpecialModeV001())
   {
      TRACE("XfplayerDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n");
   }
   else if(lpmdd->SequenceGetPreviousState() != ::mus::midi::sequence::StatusStopping
      && !pseq->IsSettingPosition())
   {
      TRACE("XfplayerDoc::OnMmsgDone \n");
      m_dProgressRate = 0.0;
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->update_all_views(NULL, 0, &uh);
   }
   else if(pseq->IsSettingPosition() ||
      pseq->WasInSpecialModeV001())
   {
   }
   else if(lpmdd->SequenceGetPreviousState() == ::mus::midi::sequence::StatusStopping)
   {
      TRACE("XfplayerDoc::OnMmsgDone Else if Stopping\n");
      m_dProgressRate = 0.0;
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->update_all_views(NULL, 0, &uh);
      
   }
   else //if(uPreviousState != ::mus::midi::sequence::StatusStopping)
   {
      TRACE("XfplayerDoc::OnMmsgDone Else\n");
      m_dProgressRate = 0.0;
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->update_all_views(NULL, 0, &uh);
      
   }
   
   pdoc->OnMmsgDone(pseq, lpmdd);*/
   
//}


void XfplayerView::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   MidiPlayerInterface::OnMidiPlayerNotifyEvent(pdata);
   ::mus::midi::sequence & seq = pdata->m_pplayer->GetSequence();
   ASSERT(&seq == &GetMidiSequence());
   XfplayerDoc * pdoc = get_document();
   
   if(pdata->m_enotifyevent
      == ::mus::midi::player::NotifyEventPositionSet)
   {
      OnProgressRateChange();
   }

   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   ASSERT(papp != NULL);
   
   
   ::radix::thread * pThreadV2  = papp->GetThreadV2();
   ASSERT(pThreadV2 != NULL);
   
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   ASSERT(pwavein != NULL);
   if(pdata->m_enotifyevent == ::mus::midi::player::NotifyEventGenericMmsgDone
      && pdoc->m_bPlay)
   {
      
      double dRate =   m_elasticslider.CalcScalar();
      if(dRate == 0.0)
      {
         //Show Title
         ShowTitle();
         
         // time to let the title be visible
         m_msPlayTimeOut = timeGetTime() + 3000;
         
         //       Sleep(3000);
      }
      else
      {
         m_msPlayTimeOut = timeGetTime();
      }
      m_bWaitingToPlay = true;
      pdoc->m_bPlay = false;
   }
   //   else if(lpmdd->SequenceWasInSpecialModeV001())
   //  {
   //    TRACE("XfplayerDoc::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n");
   //}
   /*else if(ExecuteIsSettingNextSong())
   {
      TRACE("XfplayerDoc::OnMmsgDone IsSettingNextSong()\n");
      ((XfplayerThreadV2*)pThreadV2)->EnableWaveInMessageTranslation(false);
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
      == ::mus::midi::player::NotifyEventPlaybackEnd)
   {
      pdoc->DBSaveSongEncoding(pdoc->::mediaplay::document::get_data()->get_path_name());
      m_dProgressRate = 0.0;
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->update_all_views(NULL, 0, &uh);
      TRACE("XfplayerDoc::OnMmsgDone NotifyEventPlaybackEnd \n");
   }
   else if(pdata->m_enotifyevent
      == ::mus::midi::player::NotifyEventStop)
   {
      TRACE("XfplayerDoc::OnMmsgDone Else if Stopping\n");
      StartScoring(false);
      m_dProgressRate = 0.0;
      XfplayerViewUpdateHint uh;
      uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
      pdoc->update_all_views(NULL, 0, &uh);
      
   }
   else 
   {
      int i = 0;
      i++;
   }
   pdoc->OnMidiPlayerNotifyEvent(pdata);
   
}

double XfplayerView::GetProgressRate()
{
   return m_dProgressRate;
}


void XfplayerView::OnUpdateProgress(double dRate, ::userbase::view * pview)
{
   m_dProgressRate = dRate;
   
   XfplayerViewUpdateHint uh;
   uh.AddType(XfplayerViewUpdateHint::TypeProgressRateChange);
   get_document()->update_all_views(pview, 0, &uh);

}

void XfplayerView::OnUpdateProgress(::userbase::view *pview)
{
   if(GetMidiPlayer())
   {
      ::mus::midi::sequence & seq = GetMidiSequence();
      imedia::position tkTime;
      if(MMSYSERR_NOERROR == seq.get_time(tkTime))
      {
         double dRate = ((double) tkTime) / seq.GetFile().m_tkLength;
         OnUpdateProgress(dRate, pview);
      }
   }
   else
   {
      OnUpdateProgress(0.0, pview);
   }
   
}








DWORD XfplayerView::GetPlayTimeOut()
{
   return m_msPlayTimeOut;
}


void XfplayerView::SetWaitingToPlay(bool bWaitingToPlay)
{
   m_bWaitingToPlay = bWaitingToPlay;
}

void XfplayerView::OnImageDirectoryChange()
{

}

bool XfplayerView::OnOpenMidiPlayer()
{
   if(!MidiPlayerInterface::OnOpenMidiPlayer())
      return false;
   return true;
}

void XfplayerView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   mediaplay::view::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &XfplayerView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &XfplayerView::_001OnSize);
   //IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &XfplayerView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &XfplayerView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &XfplayerView::_001OnTimer);
   connect_command("view_audio_spectrum", &XfplayerView::_001OnViewAudioSpectrum);
//   connect_update_cmd_ui("view_audio_spectrum", &XfplayerView::_001OnUpdateViewAudioSpectrum);
}

VMSRESULT XfplayerView::EnableScoring(bool bEnable)
{
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   if(bEnable)
   {
      data_set("Scoring", 1);
      
      if(!m_bScoring)
      {
         m_bScoring = true;
         pwavein->AddRef();
      }
      if(_ExecuteIsPlaying())
      {
         StartScoring(true);
      }
   }
   else
   {
      data_set("Scoring", 0);
      if(m_bScoring)
      {
         m_bScoring = false;
         pwavein->Release();
      }
      if(_ExecuteIsPlaying())
      {
         StartScoring(false);
      }
   }
   OnScoringEnable(bEnable);
   return VMSR_SUCCESS;
}

VMSRESULT XfplayerView::StartScoring(bool bStart)
{
   vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);;
   ASSERT(papp != NULL);
   
   audWaveIn * pwavein = papp->GetAudioWaveCentral().GetWaveIn();
   if(pwavein == NULL)
      return VMSR_SUCCESS;

//   ikar::static_data & staticdata = get_data()->GetKaraokeData().GetStaticData();
   
   audWaveBuffer & buffer = pwavein->GetBuffer();
   
   LPWAVEFORMATEX lpformatex = pwavein->GetFormatEx();
   ASSERT(lpformatex != NULL);
   
   if(IsScoringEnabled() && bStart)
   {
      if(!pwavein->IsOpened())
      {
         if(pwavein->open(8, 48 * 1024) != MMSYSERR_NOERROR)
            return MMSYSERR_NOERROR;
         pwavein->Start();
      }

      GetScoring()->Initialize(
         440.0,
         lpformatex->nSamplesPerSec / buffer.m_uiSkippedSamplesCount,
         &buffer);
         EventsTracksV1 * peventsa = &::mediaplay::view::get_data()->GetKaraokeData().GetStaticData().m_eventsTracksForScoring;
         ASSERT(peventsa != NULL);
         LyricEventsV2 * pevents;
       ikar::data & data = GetKaraokeData();
        ikar::static_data & staticdata = data.GetStaticData();
         if(staticdata.m_str2aRawTokens.get_size() <= 0)
            pevents = NULL;
         else if(peventsa->get_size() < staticdata.m_str2aRawTokens.get_size())
            pevents = NULL;
         else
         {
            //pEvents = (LyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->get_size());
            pevents = (LyricEventsV2 *) peventsa->operator [](0);
            ASSERT(pevents != NULL);
            ASSERT(pevents->GetClassOrder() == 2);
         }
         if(pevents != NULL)
         {
            m_pscoring->Start(pevents->GetTotalNotesMillis());
         }
         else
         {
            m_pscoring->Start(0);
         }
      m_lineScore.Show(true);
      layout();
   }
   else if(!bStart)
   {
     if(pwavein->IsRecording())
      {
         pwavein->Stop();
         pwavein->Reset();
      }
      if(pwavein->IsOpened())
      {
         pwavein->close();
      }
   }
   return VMSR_SUCCESS;
}

bool XfplayerView::IsScoringEnabled()
{
   return m_bScoring;
}


void XfplayerView::OnScoringEnable() 
{
   // TODO: add your command handler code here
   
   if(m_bScoring)
   {
      EnableScoring(false);
   }
   else
   {
      EnableScoring(true);
      
   }
   
}
void XfplayerView::OnUpdateScoringEnable(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   //CWaveCentral * pcentral = CWaveCentral::AppGetWaveCentral();
   //CWaveIn * pwavein = pcentral->GetAudioWaveCentral().GetWaveIn();
   pcmdui->Enable();
   pcmdui->_001SetCheck(IsScoringEnabled());
}


XfplayerScoring * XfplayerView::GetScoring()
{
   return m_pscoring;
}


double XfplayerView::GetScoreRate()
{
   return m_pscoring->GetScore();
}



void XfplayerView::Attach(window_frame::CWorkSetDownUpInterface * pupdown)
{
   if(pupdown->m_iType == vmsp::ViewAudioSpectrum)
   {
      simple_frame_window * pwnd = dynamic_cast < simple_frame_window * > (pupdown);
      pwnd->SetParent(this);
      pwnd->ModifyStyle(0, WS_CHILD, 0);
      rect rectClient;
      GetClientRect(rectClient);
      pwnd->SetWindowPos(NULL, rectClient.right - 300, rectClient.top + 300, 200, 100, SWP_NOZORDER);
   }
   else if(pupdown->m_iType == vmsp::ViewFileManager)
   {
      tabfy("File Manager", pupdown);
   }
   else if(pupdown->m_iType == vmsp::ViewPlaylist)
   {
      tabfy("Play list", pupdown);
   }
}

void XfplayerView::Detach(window_frame::CWorkSetDownUpInterface * pupdown)
{
   if(pupdown->m_iType == vmsp::ViewAudioSpectrum)
   {
      simple_frame_window * pwnd = dynamic_cast < simple_frame_window * > (pupdown);
      pwnd->ModifyStyle(WS_CHILD, 0, 0);
      pwnd->SetParent(NULL);
   }
}

void XfplayerView::tabfy(const char * pszTitle, window_frame::CWorkSetDownUpInterface * pupdown)
{
      if(m_ptemplateTab == NULL)
      {
         m_ptemplateTab = new userbase::single_document_template(
            get_app(),
            "mplite/mainframe",
            &typeid(::userbase::document),
            &typeid(simple_frame_window),
            &typeid(::userex::pane_tab_view));

         m_ptemplateTab->open_document_file(NULL);
      }
      document * pdoc = m_ptemplateTab->get_document(0);
      ::userex::pane_tab_view * pview = pdoc->get_typed_view < ::userex::pane_tab_view > ();
      if(pview->get_create_view() == NULL)
      {
         pview->set_create_view(new ::user::create_view);
      }
      POSITION posView = pview->get_create_view()->m_viewmap.get_start_position();
      int iId;
      int iIdMax = -1;
      ::user::create_view::view_data * pdata;
      id id;
      while(posView != NULL)
      {
         iId = id;
         pview->get_create_view()->m_viewmap.get_next_assoc(posView, id, pdata);
         if(iId > iIdMax)
            iIdMax = iId;
      }
      iId = iIdMax + 1;
      simple_frame_window * pwnd = dynamic_cast < simple_frame_window * > (pupdown);
      pdata = new ::user::create_view::view_data;
      pdata->m_id = iId;
      pdata->m_pwnd = pwnd;
      pdata->m_pdoc = dynamic_cast < ::userbase::document * > (pwnd->GetActiveDocument());
      string strSetId;
      strSetId.Format("%d", iId);
      pview->get_create_view()->m_viewmap.set_at(iId, pdata);
      pview->add_tab(pszTitle, iId);
      pview->m_etranslucency = TranslucencyTotal;
      pwnd->SetParent(pview);
      pwnd->ModifyStyle(0, WS_CHILD, 0);
      rect rectClient;
      GetClientRect(rectClient);
      pview->GetParentFrame()->SetParent(this);
      pview->GetParentFrame()->ModifyStyle(0, WS_CHILD, 0);
      pview->GetParentFrame()->SetWindowPos(NULL, 23, 23, 800, 300, SWP_NOZORDER);
      pview->set_cur_tab_by_id(iId);
//     pview->Show(pdata);
      simple_frame_window * pwnd2 = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
      pwnd2->m_etranslucency = ::user::window_interface::TranslucencyTotal;
      pwnd2->m_wndframework.SetAppearanceTransparency(window_frame::Transparent);
      pview->layout();
}

void XfplayerView::on_delete(::ca::ca * pca)
{
}