#include "StdAfx.h"
#include "kar/KaraokeBouncingBall.h"
#include "_vmspConfiguration.h"
#include "libcharguess/libcharguess.h"

namespace mplite
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      gcom::backview::Interface(papp),
      gcom::backview::user::interaction(papp),
      KaraokeView(papp),
      ::mediaplay::view_interface(papp),
      mediaplay::view(papp),
      m_audiospectrum(papp),
      m_elasticslider(papp),
      m_sliderKeyShift(papp),
      MidiPlayerInterface(papp),
      audio::WavePlayerInterface(papp),
      audio::WaveRecorderInterface(papp),
      m_hglrc(NULL)
   {
      m_idPopup      = "IDR_POPUP_LYRICVIEW";
      m_idPopupLink  = "IDR_POPUP_LYRICVIEW_LINK";
      
      m_bOverrideKaraokeCodePage = false;
      m_bFileOverrideKaraokeCodePage = false;


      m_dataid = "mplite::view";
      m_bWaitingToPlay = false;
      m_bDestroy = false;

   //   m_lpbouncingball->SetIcons(get_app()->LoadIcon(IDI_BB1), get_app()->LoadIcon(IDI_BB1_PRESSED1));
      //m_lpbouncingball->SetBallType(kar::KaraokeBouncingBall::Ball);


   //   VmsDataServerInterface & db = (dynamic_cast < application * > (get_app()))->GetVmsDataServerInterface();
   //   db.AddClient(this);
      connect_update_cmd_ui("show_bk_gcom", &view::_001OnUpdateShowBkGcom);
      connect_command("show_bk_gcom", &view::_001OnShowBkGcom);
      connect_update_cmd_ui("view_gradual_filling", &view::_001OnUpdateKaraokeGradualFilling);
      connect_command("view_gradual_filling", &view::_001OnKaraokeGradualFilling);
      connect_update_cmd_ui("karaoke_bouncing_ball", &view::_001OnUpdateKaraokeBouncingBall);
      connect_command("karaoke_bouncing_ball", &view::_001OnKaraokeBouncingBall);
      connect_update_cmd_ui("execute_minus_one", &view::_001OnUpdateExecuteMinusOne);
      connect_command("execute_minus_one", &view::_001OnExecuteMinusOne);
      connect_update_cmd_ui("execute_play", &view::_001OnUpdateExecutePlay);
      connect_command("execute_play", &view::_001OnExecutePlay);
      connect_update_cmd_ui("execute_stop", &view::_001OnUpdateExecuteStop);
      connect_command("execute_stop", &view::_001OnExecuteStop);
      connect_update_cmd_ui("execute_pause", &view::_001OnUpdateExecutePause);
      connect_command("execute_pause", &view::_001OnExecutePause);
      connect_update_cmd_ui("execute_previous", &view::_001OnUpdateExecutePrevious);
      connect_command("execute_previous", &view::_001OnExecutePrevious);
      connect_update_cmd_ui("execute_next", &view::_001OnUpdateExecuteNext);
      connect_command("execute_next", &view::_001OnExecuteNext);
      connect_update_cmd_ui("execute_auto_record", &view::_001OnUpdateExecuteAutoRecord);
      connect_command("execute_auto_record", &view::_001OnExecuteAutoRecord);
      connect_command("open_link_in_new_window", &view::_001OnOpenLinkInNewWindow);
      connect_command("copy_link_location", &view::_001OnCopyLinkLocation);
      connect_update_cmd_ui("playlist_execute_play", &view::_001OnUpdatePlaylistExecutePlay);
      connect_command("playlist_execute_play", &view::_001OnPlaylistExecutePlay);
      
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::mediaplay::view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &view::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

   //   connect_command(ID_EXECUTE_PLAY             , this, this, &view::_001OnExecutePlay);
   //   connect_update_cmd_ui(ID_EXECUTE_PLAY             , this, this, &view::_001OnUpdateExecutePlay);
   //   connect_command(ID_KARAOKE_BOUNCING_BALL    , this, this, &view::_001OnKaraokeBouncingBall);
   //   connect_update_cmd_ui(ID_KARAOKE_BOUNCING_BALL    , this, this, &view::_001OnUpdateKaraokeBouncingBall);
   //   connect_command(ID_KARAOKE_GRADUAL_FILLING  , this, this, &view::_001OnKaraokeGradualFilling);
   //   connect_update_cmd_ui(ID_KARAOKE_GRADUAL_FILLING  , this, this, &view::_001OnUpdateKaraokeGradualFilling);
   //   connect_command(ID_EXECUTE_STOP             , this, this, &view::_001OnExecuteStop);
   //   connect_update_cmd_ui(ID_EXECUTE_STOP             , this, this, &view::_001OnUpdateExecuteStop);
   //   connect_command(ID_EXECUTE_PAUSE            , this, this, &view::_001OnExecutePause);
   //   connect_update_cmd_ui(ID_EXECUTE_PAUSE            , this, this, &view::_001OnUpdateExecutePause);
   //   connect_command(ID_EXECUTE_MINUS_ONE        , this, this, &view::_001OnExecuteMinusOne);
   //   connect_update_cmd_ui(ID_EXECUTE_MINUS_ONE        , this, this, &view::_001OnUpdateExecuteMinusOne);
   //   connect_command(ID_OPEN_LINK_IN_NEW_WINDOW  , this, this, &view::_001OnOpenLinkInNewWindow);
   //   connect_command(ID_COPY_LINK_LOCATION       , this, this, &view::_001OnCopyLinkLocation);
   //   connect_command(ID_PLAYLIST_EXECUTE_PLAY    , this, this, &view::_001OnPlaylistExecutePlay);
   //   connect_update_cmd_ui(ID_PLAYLIST_EXECUTE_PLAY    , this, this, &view::_001OnUpdatePlaylistExecutePlay);
   //   connect_command(ID_EXECUTE_PREVIOUS         , this, this, &view::_001OnExecutePrevious);
   //   connect_update_cmd_ui(ID_EXECUTE_PREVIOUS         , this, this, &view::_001OnUpdateExecutePrevious);
   //   connect_command(ID_EXECUTE_NEXT             , this, this, &view::_001OnExecuteNext);
   //   connect_update_cmd_ui(ID_EXECUTE_NEXT             , this, this, &view::_001OnUpdateExecuteNext);
      //}}AFX_MSG_MAP
      // Standard printing commands
   //   IGUI_WIN_MSG_LINK(WM_USER + 177              , this, this, &view::_001OnTabClick);
      /*connect_command(ID_FILE_PRINT            , this, this, &view::_001OnFilePrint);
      connect_command(ID_FILE_PRINT_DIRECT     , this, this, &view::_001OnFilePrint);
      connect_command(ID_FILE_PRINT_PREVIEW    , this, this, &view::_001OnFilePrintPreview);*/
   //   connect_command(ID_EXECUTE_AUTO_RECORD   , this, this, &view::_001OnExecuteAutoRecord);
   //   connect_update_cmd_ui(ID_EXECUTE_AUTO_RECORD   , this, this, &view::_001OnUpdateExecuteAutoRecord);

      /*IGUI_WIN_ON_COMMAND_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, this, this, &view::_001OnViewEncoding);*/
      /*IGUI_WIN_UPD_CMD_UI_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, this, this, &view::_001OnUpdateViewEncoding);*/
      
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      EncodingMapItem item;
      command_signalid signalid;
      gen::signalid * pid;
      for(int i = 0; i < papp->GetCodePageCommandCount(); i++)
      {
         papp->GetCodePageCommandData(item, i);
         signalid.m_id = item.m_id;
         pid = m_signalidaCommand.get(&signalid);
         m_dispatchUpdateCmdUi.AddMessageHandler(pid, this, &view::_001OnUpdateViewEncoding, true);
         m_dispatchCommand.AddMessageHandler(pid, this, &view::_001OnViewEncoding, true);
      }



      
   }




    // BEGIN_MESSAGE_MAP(::view, view)
      //{{AFX_MSG_MAP(::view)
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
      ON_COMMAND(ID_FILE_PRINT, view::OnFilePrint)
      ON_COMMAND(ID_FILE_PRINT_DIRECT, view::OnFilePrint)
      ON_COMMAND(ID_FILE_PRINT_PREVIEW, view::OnFilePrintPreview)
      ON_COMMAND_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnViewEncoding)
      ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnUpdateViewEncoding)
      ON_COMMAND(ID_EXECUTE_AUTO_RECORD, OnExecuteAutoRecord)
      ON_UPDATE_COMMAND_UI(ID_EXECUTE_AUTO_RECORD, OnUpdateExecuteAutoRecord)
      */
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::mediaplay::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::mediaplay::view::dump(dumpcontext);
   }
   #endif

   document * view::get_document() // non-debug version is inline
   {
      ASSERT(base < document >::bases(::view::get_document()));
      return dynamic_cast < document * > (::view::get_document());
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
      cs.style |= WS_CLIPSIBLINGS;
      return ::mediaplay::view::PreCreateWindow(cs);
   }



   /*::thread * view::GetMidiPlayerCallbackThread()
   {
      return &gen::ThreadContainer::AppGetHighThread();
   }*/

   ::mus::midi::sequence & view::GetMidiSequence()
   {
      return get_document()->get_data()->GetMidiSequence();
   }

   /*void view::ExecutePlay(bool bMakeVisible)
   {
      document * pdoc = get_document();
      if(pdoc->GetMode() == document::ModeWave)
      {
   //      audio::CWavePlayer::CCommand command;
     //    command.OpenDevice();
       //  m_pwaveplayer->ExecuteCommand(command);
         //command.Play();
         //m_pwaveplayer->ExecuteCommand(command);
         return;
      }
      
      
      ::mus::midi::sequence & midisequence = GetMidiSequence();
      ASSERT(&midisequence != NULL);
      
      ikar::data & data = GetKaraokeData();
      ikar::static_data & staticdata = data.GetStaticData();
      CKaraokeDynamicData & dynamicdata = data.GetDynamicData();

      if(midisequence.GetState() != ::mus::midi::sequence::StatusOpened)
      {
         return;
      }
      ASSERT(midisequence.GetState() == ::mus::midi::sequence::StatusOpened);
   /*   if (midisequence.GetState() == ::mus::midi::sequence::StatusNoFile)
      {
         string str;
         string str;
         
         int i3 = sizeof(MidiPlayer);
         string str3;
         str3.Format("sizeof MidiPlayer %d", i3);
         
         COleVariant var;
         
         while(pplaylistdoc->PeekNextSongPath(str))
         {
            gen::international::UnicodeToOEM(str, str);
            int i4 = sizeof(MidiPlayer);
            string str4;
            str4.Format("sizeof MidiPlayer %d", i4);
            
            var = str.AllocSysString();
            
            if(pdoc->open_document_file(var))
               break;
            UpdateReserveList();
         }
         
      }*/
      
   /*   dynamicdata.m_iPlayingTokenIndex = -1;
      dynamicdata.m_iBufferTokenIndex = 0;
      //m_iBufferingTokenIndex = 0;
      //m_iBufferingOffsetTokenIndex = 0;
      //   pApp->SetPlayingDocument(this);
      
      //GetMidiPlayer()->SetMidiOutDevice(midi_central::GetMidiCentral()->m_uiMidiOutDevice);
      
      if(GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened)
      {
         pdoc->m_bPlay = true;
         try
         {
            GetMidiSequence().SetSpecialModeV001Operation(::mus::midi::sequence::SPMV001GMReset);
            GetMidiPlayer()->Play();
         }
         catch(midi_exception * pe)
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

   void view::_001OnExecutePlay(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      imedia::position position;
      position.m_i = 0;
      _ExecutePlay(true, position);
   }

   void view::_001OnUpdateExecutePlay(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPlayEnable());
      pupdatecmdui->m_bRet = true;
   }

   void view::_001OnPlaylistExecutePlay(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      imedia::position position;
      position.m_i = 0;
      _ExecutePlay(true, position);
   }

   void view::_001OnUpdatePlaylistExecutePlay(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPlayEnable());
      pupdatecmdui->m_bRet = true;
   }


   void view::_001OnExecuteStop(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecuteNone);
   }

   /*void view::ExecuteStop()
   {
      document * pdoc = get_document();
      switch(pdoc->GetMode())
      {
      case document::ModeMidi:
         {
            if(ExecuteIsWaitingToPlay())
            {
   //            SetWaitingToPlay(false);
               m_bWaitingToPlay = false;
            }
            else
            {
               //mplite::application *pApp = (mplite::application *) get_app();
               //ASSERT(pApp != NULL);   
               //CWaveIn * pWaveIn = pApp->GetWaveIn();
               //m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_STOP, 0, 0);
               m_pmidiplayer->PostThreadMessage(MIDIPLAYERMESSAGE_COMMAND, m_pmidiplayer->CommandStop, 0);
            }
         }
      break;
      case document::ModeWave:
         {
   //         audio::CWavePlayer::CCommand command;
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



   void view::_001OnUpdateExecuteStop(gen::signal_object * pobj) 
   {
      /*bool bEnable = false;
      document * pdoc = get_document();
      switch(pdoc->get_data()->GetMode())
      {
      case mediaplay::data::ModeMidi:
         {
            bEnable = GetMidiPlayer() &&
                  (GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPaused ||
                  GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying ||
                  ExecuteIsWaitingToPlay());
            break;
         }
      case mediaplay::data::ModeWave:
         {
   //         bEnable = m_pwaveplayer != NULL
     //          && m_pwaveplayer->IsPlaying();
            break;
         }
      }*/
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      pupdatecmdui->m_pcmdui->Enable(_ExecuteGetStopEnable());
      pupdatecmdui->m_bRet = true;
   }

   void view::_001OnExecutePause(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      _ExecutePause();
   }

   /*void view::ExecutePause()
   {
      GetMidiPlayer()->Pause();
   }*/

   void view::_001OnUpdateExecutePause(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(_ExecuteGetPauseEnable());
      pupdatecmdui->m_pcmdui->_001SetCheck(_ExecuteIsPaused());
      pupdatecmdui->m_bRet = true;
   }

   /*bool view::ExecuteIsPaused()
   {
      return GetMidiPlayer() &&
         GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPaused;
   }

   bool view::ExecuteGetPauseEnable()
   {
      switch(get_document()->GetMode())
      {
      case document::ModeNone:
         {
            return false;
         }
      case document::ModeMidi:
         {
            ::mus::midi::sequence::Status  estatus = (::mus::midi::sequence::Status) GetMidiSequence().GetState();
            return estatus == ::mus::midi::sequence::StatusPaused ||
               estatus == ::mus::midi::sequence::StatusPlaying;
         }
      case document::ModeWave:
         {
            return false;
         }
      default:
         ASSERT(FALSE);
         return false;
      }
   }


   bool view::ExecuteGetPlayEnable()
   {
      document * pdoc = get_document();
      switch(pdoc->GetMode())
      {
      case document::ModeNone:
         return false;
      case document::ModeMidi:
         return GetMidiPlayer()
            && (pdoc->GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened)
            && !ExecuteIsWaitingToPlay();
      case document::ModeWave:
   //      return m_pwaveplayer->DecoderIsOpened()
   //         && ! m_pwaveplayer->IsPlaying();
      default:
         ASSERT(FALSE);
         return false;
      }
   }


   void view::ExecuteListenMinusOne(bool bMinusOne)
   {
      ikar::data & data = GetKaraokeData();
      MidiPlayer * pplayer = GetMidiPlayer();
      ::mus::midi::sequence & sequence = pplayer->GetSequence();
      CMidiFile & file = sequence.GetFile();
      int iTrack = data.GetStaticData().GetGuessMelodyTrack();
      spfile->MuteTrack(
         iTrack,
         bMinusOne);
      //DBListenMinusOne(true, pdoc->get_path_name(), bMinusOne);
      
   }

   void view::ExecuteToggleListenMinusOne()
   {
      ikar::data & data = GetKaraokeData();
      ASSERT(ExecuteGetListenMinusOneEnable());
      if(ExecuteGetListenMinusOneEnable())
      {
         MidiPlayer * pplayer = GetMidiPlayer();
         ::mus::midi::sequence & sequence = pplayer->GetSequence();
         CMidiFile & file = sequence.GetFile();
         CMidiTracks & tracks = spfile->GetTracks();
         int iTrack = data.GetStaticData().GetGuessMelodyTrack();
         bool bMute = spfile->IsTrackMute(iTrack);
         ExecuteListenMinusOne(!bMute);
      }
   }


   bool view::ExecuteGetListenMinusOneEnable()
   {
      bool bEnable = GetMidiPlayer() != NULL
         && (GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened
         || GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying);
      return bEnable;
      
   }

   int view::GetListenMinusOneCheck()
   {
      if(ExecuteGetListenMinusOneEnable())
      {
         return GetMidiPlayer()->GetSequence().GetFile().IsTrackMute(
            GetKaraokeData().GetStaticData().GetGuessMelodyTrack()) ? 1 : 0;
      }
      else
         return 0;
   }*/



   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::mediaplay::view::_001OnInitialUpdate(pobj);
   }


   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      ::mediaplay::view::on_update(pSender, lHint, phint);
      if(phint != NULL)
      {
         if(base < view_update_hint >::bases(phint))
         {
            view_update_hint * puh = (view_update_hint * ) phint;
            if(puh->is_type_of(view_update_hint::TypeAttachPlaylist)
               && puh->m_pplaylistdoc != NULL)
            {
               puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
               m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
            }
            else if(puh->is_type_of(view_update_hint::TypeGetPlaylistCallback))
            {
               puh->m_pplaylistcallback = m_pplaylistcallback;
            }
         }
         else if(base < mplite::pane_view_update_hint >::bases(phint))
         {
            mplite::pane_view_update_hint * puh = (mplite::pane_view_update_hint * ) phint;
            if(puh->is_type_of(mplite::pane_view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(mplite::pane_view_update_hint::TypeOnShowView))
            {
               int iTab;
               if(puh->m_eview == mplite::PaneViewContextMenu)
               {
                  GetParentPane()->_001AddSel(0);
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
                  GetParentPane()->_001SetSel(iTab);
               }
               
            }
         }
         else if(base < ::mediaplay::view_update_hint > :: bases(phint))
         {
            ::mediaplay::view_update_hint * puh = (::mediaplay::view_update_hint * ) phint;
            if(puh->is_type_of(::mediaplay::view_update_hint::TypeAfterOpenDocument))
            {
               data_get("OverrideKaraokeCodePage", get_document()->get_path_name(), m_bFileOverrideKaraokeCodePage);
               if(m_bFileOverrideKaraokeCodePage)
               {
                  data_get("OverridingKaraokeCodePage", get_document()->get_path_name(), (int &) m_dwFileOverrideKaraokeCodePage);
               }
            }
         }
      }


   /*   if(lHint == 1000)
      {

         PrepareLyricLines();
         m_lpbouncingball->SetQuarterNoteDuration(
             GetMidiSequence().GetFile().m_pFileHeader->GetQuarterNoteTicks());

      }

      if(phint != NULL)
      {
         if(base < view_update_hint >::bases(phint))
         {
            view_update_hint * puh = (view_update_hint * ) phint;
            if(puh->is_type_of(view_update_hint::TypeDoPlay))
            {
               ExecutePlay(true);
            }
            else if(puh->is_type_of(view_update_hint::TypePlayIfNotPlaying))
            {
               if(!GetMidiSequence().IsPlaying())
               {
                  ExecutePlay(true);
               }
            }
            else if(puh->is_type_of(view_update_hint::TypeGetMidiPlayerInterface)
               && puh->m_pmidiplayer == NULL)
            {
               puh->m_pmidiplayer = this;
            }
            else if(puh->is_type_of(view_update_hint::TypeAttachPlaylist)
               && puh->m_pplaylistdoc != NULL)
            {
               puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
               m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
            }
            else if(puh->is_type_of(view_update_hint::TypeFullScreen))
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

   /*::ca::window & view::BackViewGetWnd()
   {
      return *this;
   }

   void view::BackViewUpdateScreen(LPCRECT lpcrect)
   {
      RedrawWindow(lpcrect);
   }

   void view::BackViewUpdateScreen()
   {
      RedrawWindow();
   }

   void view::BackViewGetData(
      gcom::backview::CInterfaceData & data)
   {

      if(data.is_signalized(gcom::backview::InterfaceDataNextImagePath))
      {
         db_server * pdb = db();
         string str;
         DILoad("Images.CurrentPath", str);
         string wstrCurrentImagePath;
         wstrCurrentImagePath.SetOEM(str);
         data.m_wstrNextImagePath = pdb->GetNextImagePath(wstrCurrentImagePath);
      //   data.m_wstrNextImagePath = L"C:\\camilo.jpg";
      }
      if(data.is_signalized(gcom::backview::InterfaceDataEnhancedMetaFile))
      {
   //      data.m_henhmetafile = m_enhmetafile;
         data.m_henhmetafile = NULL;
      }

   }

   void view::BackViewSetData(
      gcom::backview::CInterfaceData & data)
   {

      if(data.is_signalized(gcom::backview::InterfaceDataCurrentImagePath))
      {
         db_server * pdb = db();
         string str;
         gen::international::UnicodeToACP(
            str,
            data.m_wstrCurrentImagePath);
         DISave("Images.CurrentPath", str);
      }

   }

   bool view::BackViewGetDestroy()
   {
      return m_bDestroy; 
   }*/

   /*bool view::BackViewIsFullScreen()
   {
      return false; // TODO
   }*/

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pplaylistcallback->OnClosePlayer();
      delete m_pplaylistcallback;
      m_pplaylistcallback = NULL;
      m_bDestroy = true;   
   }



   void view::_001OnSize(gen::signal_object * pobj) 
   {
      pobj->previous();

      rect rectClient;

      GetClientRect(rectClient);

      int iSideMargin = 64;
      int iHeight = 16;
      int iBottomMargin = 32;

      if(m_elasticslider.IsWindow())
      {
         m_elasticslider.SetWindowPos(NULL, 
            iSideMargin, 
            rectClient.bottom - iBottomMargin - iHeight, 
            max(0, rectClient.width() - 2 * iSideMargin),
            iHeight,
            SWP_SHOWWINDOW);
      }
      if(m_sliderKeyShift.IsWindow())
      {
         m_sliderKeyShift.SetWindowPos(NULL, 
            rectClient.right - iSideMargin - 200, 
            200, 
            100,
            iHeight,
            SWP_SHOWWINDOW);
      }
      //view::_001OnSize(nType, cx, cy);
      
   /*   if(m_dcBuffer.get_os_data() != NULL)
      {
         m_dcBuffer.SelectObject(m_pbmpBufferOld);
         m_dcBuffer.DeleteDC();
      }

      if(m_bmpBuffer.GetSafeHandle() != NULL)
      {
         m_bmpBuffer.delete_object();
      }

      ::ca::graphics * pdc = GetDC();

      m_dcBuffer.CreateCompatibleDC(pdc);
      m_bmpBuffer.CreateCompatibleBitmap(pdc, cx, cy);
      m_pbmpBufferOld = m_dcBuffer.SelectObject(m_bmpBuffer);
      
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


   /*void view::_001OnDraw(::ca::graphics * pdcScreen)
   {
      document * pDoc = get_document();


      CSingleLock sl(m_gdibuffer.GetSemaphore());
      ::ca::graphics * pdc = m_gdibuffer.GetBuffer();

      int count = 0;


      ::mus::midi::sequence & seq = GetMidiSequence();
      CMidiFile & file = seq.GetFile();


      ikar::data & data = GetKaraokeData();
      if(data.IsNull())
      {
         return;
      }
      CKaraokeDynamicData & dynamicdata = data.GetDynamicData();
      ikar::static_data & staticdata = data.GetStaticData();

      rect rectClient;
      GetClientRect(rectClient);
      int cx = rectClient.width();
      int cy = rectClient.height();

      

      rect rectClip;

      pdcScreen->GetClipBox(rectClip);
      
      if(rectClip.is_null())
      {
         GetClientRect(rectClip);
         pdc->SelectClipRgn(NULL);
      }
      else
      {
         ::ca::rgn rgnClip;
         rect rect(rectClip);
         rect.offset(pdc->GetViewportOrg());
         rgnClip.CreateRectRgnIndirect(rect);
         pdc->SelectClipRgn(&rgnClip);
   //      TRACE("_ONDRAW (%d, %d)\n", rectClip.width(), rectClip.height());
         ASSERT(TRUE);
      }

      // Back ::view Drawing
      {
         gcom::backview::CInterface & backview = BackViewGetInterface();
         CSingleLock slTransfer(&backview.GetTransferCS(), false);
         slTransfer.Lock();
         pdc->BitBlt(
            rectClip.left, rectClip.top,
            rectClip.width(), rectClip.height(),
            &backview.GetTransferDC(),
            rectClip.left, rectClip.top,
            SRCCOPY);
         slTransfer.Unlock();
      }

      visual::CWinGdi visual;
      visual.m_spgraphics->Attach((HDC)pdc->get_os_data());
      KaraokeRender(&visual);
      visual.m_spgraphics->Detach();
      //_001DrawChildren(pdc);

      pdcScreen->BitBlt(
         rectClip.left,
         rectClip.top,
         rectClip.width(),
         rectClip.height(),
         pdc,
         rectClip.left,
         rectClip.top,
         SRCCOPY);

      
   }*/

   void view::_001OnKaraokeBouncingBall(gen::signal_object * pobj) 
   {
      
      if(!m_bBouncingBall)
      {
         m_bBouncingBall = true;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      else
      {
         m_bBouncingBall = false;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      RedrawWindow();
      data_set("BouncingBall", ::ca::system::idEmpty, m_bBouncingBall ? 1 : 0);   
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateKaraokeBouncingBall(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_pcmdui->_001SetCheck(m_bBouncingBall);
      pupdatecmdui->m_bRet = true;
      
   }

   void view::_001OnKaraokeGradualFilling(gen::signal_object * pobj) 
   {
      
      if(!m_bGradualFilling)
      {
         m_bGradualFilling = true;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      else
      {
         m_bGradualFilling = false;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      RedrawWindow();
      data_set("GradualFilling", ::ca::system::idEmpty, m_bGradualFilling ? 1 : 0);   
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateKaraokeGradualFilling(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_pcmdui->_001SetCheck(m_bGradualFilling);
      pupdatecmdui->m_bRet = true;
   }


   void view::_001OnShowBkGcom(gen::signal_object * pobj) 
   {
      if(!m_bPassthroughBackground)
      {
         m_bPassthroughBackground = true;
      }
      else
      {
         m_bPassthroughBackground = false;
      }
      data_set("PassthroughBackground", ::ca::system::idEmpty, m_bPassthroughBackground);   
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateShowBkGcom(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_pcmdui->_001SetCheck(m_bPassthroughBackground);
      pupdatecmdui->m_bRet = true;
   }

   void view::_001OnExecuteMinusOne(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      _ExecuteToggleListenMinusOne();
   }

   void view::_001OnUpdateExecuteMinusOne(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(_ExecuteGetListenMinusOneEnable());
      pupdatecmdui->m_pcmdui->_001SetCheck(GetListenMinusOneCheck());
      pupdatecmdui->m_bRet = true;
   }


   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      
      m_iBackgroundUpdateMillis = Application.m_iBackgroundUpdateMillis;

      application * papp = dynamic_cast < application * > (get_app());

   //   ::database::client::initialize(papp);


      if(!::mediaplay::view::Initialize(&papp->GetMidiCentral()))
      {
         return;
      }


      if(pobj->previous())
         return;


      m_audiospectrum.create(this, 1);

      m_elasticslider.create(this, 2);

      m_elasticslider.SetStreamingVelocityMode(this, m_iScalarTempo, this, m_iScalarPos);


      m_audiospectrum.SetWindowPos(NULL, 0,  75, 150, 75, 0);

      m_sliderKeyShift.create(this, 23);

      m_sliderKeyShift.m_pscalar = this;
      m_sliderKeyShift.m_iScalar = m_iScalarKeyShift;


      m_pplaylistcallback = new playlist_callback(
         &musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app()),
         get_document(),
         get_document());

      SetTimer(gen::Timer::ID_HOVER, 100, NULL);



      
      //database & db = mplite::db(get_app());
      //m_spfilesetBackgroundImage = dynamic_cast < ex2::file_set * > (db.m_pimagefileset->m_p);


      //m_gdi.m_spgraphics->Attach(GetDC()->get_os_data());
   /*   GLuint PixelFormat;         // Holds The Results After Searching For A Match

      ::ca::graphics * pdc = GetDC();
      HDC hdc = (HDC)pdc->get_os_data();
      
      if (!(PixelFormat=ChoosePixelFormat(hdc, &m_pixelformatdescriptor)))   // Did Windows find A Matching Pixel Format?
      {
   //      MessageBox(NULL,"Can't find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
         return -1;                        // Return FALSE
      }
      
      if(!SetPixelFormat(hdc, PixelFormat,&m_pixelformatdescriptor))      // Are We Able To Set The Pixel Format?
      {
   //      MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
         return -1;                        // Return FALSE
      }

      if (!(m_hglrc = wglCreateContext(hdc)))            // Are We Able To get A Rendering Context?
      {
   //      MessageBox(NULL,"Can't create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
         return -1;                        // Return FALSE
      }

      if(!wglMakeCurrent(hdc, m_hglrc))               // Try To Activate The Rendering Context
      {
   //      MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
         return -1;                        // Return FALSE
      }*/


   }

   int view::InitGL()
   {
   /*   glShadeModel(GL_SMOOTH);                     // Enable Smooth Shading
      glClearColor(0.0f, 0.0f, 0.0f, 0.5f);            // Black Background
      glClearDepth(1.0f);                           // Depth buffer Setup
      glEnable(GL_DEPTH_TEST);                     // Enables Depth Testing
      glDepthFunc(GL_LEQUAL);                        // The Type Of Depth Testing To Do
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Really Nice Perspective Calculations
      glEnable(GL_LIGHT0);                        // Enable Default Light (Quick And Dirty)
      glEnable(GL_LIGHTING);                        // Enable Lighting
      glEnable(GL_COLOR_MATERIAL);                  // Enable Coloring Of Material

      BuildFont();                              // Build The font*/

      return TRUE;                              // Initialization Went OK

   }

   ::ca::graphics * view::GetGdi()
   {
      return m_gdi;
   }

   void view::_001OnRButtonUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      int iLine, iToken, iChar;
      class point ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      LyricViewLines & lyriclines = GetLyricLines();
      string str;
      if(m_lyrictemplatelines.hit_test(ptCursor, iLine, iToken, iChar)
         == ::user::line_hit_link)
      {
         lyriclines.GetLink(str, iLine, iToken, iChar);
         m_strCurrentLink = str;
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu("mplite\\popup_lyricview_link.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
         pmouse->set_lresult(1);
         pmouse->m_bRet = true;
      }
      else if(m_plinesTitle->hit_test(ptCursor, iLine, iChar)
         == user::line_hit_link)
      {
         m_plinesTitle->element_at(iLine).GetCharLink(str, iChar);
         m_strCurrentLink = str;
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu("mplite\\popup_lyricview_link.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
         pmouse->set_lresult(1);
         pmouse->m_bRet = true;
      }
      else
      {
         ::userbase::menu * pmenu = new ::userbase::menu(get_app());
         pmenu->LoadXmlMenu("mplite\\popup_lyricview.xml");
         pmenu->TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
         pmouse->set_lresult(1);
         pmouse->m_bRet = true;
      }

   }

   void view::_001OnTabClick(int iTab)
   {
      pane_view * pview = GetParentPane();
      
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
         pview->set_cur_tab_by_id(eview);
      }
   }


   void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      application * papp = dynamic_cast < application * > (get_app());
      DWORD dwCodePage = papp->CommandToCodePage(pupdatecmdui->m_pcmdui->m_id);
      
      if(GetKaraokeCodePage(NULL) == dwCodePage)
      {
         pupdatecmdui->m_pcmdui->_001SetCheck();
         pupdatecmdui->m_pcmdui->Enable(0);
      }
      else
      {
         pupdatecmdui->m_pcmdui->_001SetCheck(false);
         pupdatecmdui->m_pcmdui->Enable(1);
      }
      pupdatecmdui->m_bRet = true;
   }
   void view::_001OnViewEncoding(gen::signal_object * pobj)
   {
      SCAST_PTR(BaseCommand, pcommand, pobj)
      DWORD dwCodePage = CommandToCodePage(pcommand->m_id);
      SetKaraokeCodePage(dwCodePage, true);
   }

   DWORD view::CommandToCodePage(id id)
   {
      return Application.CommandToCodePage(id);
   }

   void view::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      /* dbbreak VmsDataChangeHint * pch = (VmsDataChangeHint *) pobj;
      if(*pch->m_pkey == "KaraokeEncoding")
      {
         PrepareLyricLines();
         RedrawWindow();
      }
      else if(*pch->m_pkey == "GlobalLyricsDelay")
      {     
         data_get("GlobalLyricsDelay", ::ca::system::idEmpty, m_iDelay);
      }
      else if(*pch->m_pkey == "ImageDirectorySet")
      {
         gcom::backview::Interface::ImageChangePostEvent(gcom::backview::EventLoadNow);
      }*/
   }

   bool view::KaraokeDoesOverrideCodePage()
   {
      return m_bOverrideKaraokeCodePage ||
         m_bFileOverrideKaraokeCodePage;
   }

   DWORD view::KaraokeGetOverridingCodePage(const char * lpsz)
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
               string str;
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

//        ::database::server & db = *(dynamic_cast < application * > (get_app()))->get_data_server();

      var var;

      //if(db.get_data(_vmsp::CConfiguration::CfgKaraokeEncoding, GetLanguage(), 0, var))
      if(data_get(
         "KaraokeEncoding", 
         ::ca::system::idEmpty,
         var))
      {
         ASSERT(var.get_type() == var::type_integer);
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


   void view::SetKaraokeCodePage(DWORD dw, bool bOverride)
   {
      UNREFERENCED_PARAMETER(bOverride);
        //::database::server & db = *(dynamic_cast < application * > (get_app()))->GetDataServer();

      var var;
      var.set_type(var::type_integer);
      var.m_i = dw;

      if(!get_document()->get_path_name().is_empty())
      {
         m_bFileOverrideKaraokeCodePage = true;
         m_dwFileOverrideKaraokeCodePage = dw;
      }
      else
      {
         m_bOverrideKaraokeCodePage = true;
      }

   /*   db.set_data(
         _vmsp::CConfiguration::CfgKaraokeEncoding,
         GetLanguage(), 
         0,
         var);*/
      data_set(
         "KaraokeEncoding",
         ::ca::system::idEmpty,
         var);

   }

   LONG GetRegKey(HKEY key, const char * subkey, LPTSTR retdata)
   {

    

       HKEY hkey;

    

       LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    

    

    

       if (retval == ERROR_SUCCESS) {

    

           long datasize = MAX_PATH;

    

           char data[MAX_PATH];

    

           RegQueryValue(hkey, NULL, data, &datasize);

    

           lstrcpy(retdata,data);

    

           RegCloseKey(hkey);

    

       }

    

    

    

       return retval;

    

   }

    

    

   void URLOpenNew(const char * lpcsz)

   {

      char key1[MAX_PATH + MAX_PATH];
      char key2[MAX_PATH + MAX_PATH];
      char key3[MAX_PATH + MAX_PATH];

      if(GetRegKey(HKEY_CLASSES_ROOT, ".html", key1) != ERROR_SUCCESS)
         if(GetRegKey(HKEY_CLASSES_ROOT, ".htm", key1) != ERROR_SUCCESS)
            return;

      lstrcpy(key2, key1);
      lstrcat(key2, "\\shell\\opennew\\command");

      if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
      {
         lstrcpy(key2, key1);
         lstrcat(key2, "\\shell\\open\\command");
         if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
         {
            return;
         }
      }

      string str(key3);

      str.replace("%1", lpcsz);

      WinExec(str,SW_SHOW);

           
   }

   void view::_001OnOpenLinkInNewWindow(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      ASSERT(!m_strCurrentLink.is_empty());   
      URLOpenNew(m_strCurrentLink);
   }

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
      
      pobj->previous();
   }

   HCURSOR view::KaraokeGetHandCursor()
   {
      /*
      return System.LoadCursor(IDC_HAND_POINTER);*/
      return NULL;

   }

   void view::_001OnCopyLinkLocation(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      System.copydesk().set_plain_text(m_strCurrentLink);
   }


   pane_view * view::GetParentPane()
   {
      return GetTypedParent < pane_view >();
   }

   void view::OnMediaPlaybackStart()
   {
      frame_window * pframewnd = GetTopLevelFrame();

      if(base < main_frame >::bases(pframewnd))
      {
         main_frame * pframe = dynamic_cast < main_frame * > (pframewnd);
         pframe->SetAnimatedStatusBarText(get_data()->GetAnimatedTitle());
         
      }

      //string str;
      //str.SetACP(get_document()->get_path_name());
      mediamanager::get(get_app())->OnOpenDocumentFile(get_document()->get_path_name());

      ::mediaplay::view::OnMediaPlaybackStart();
   }

   bool view::OnExecuteBeforePlay()
   {
      pane_view * pview = GetParentPane();
      if(pview != NULL)
      {
         pview->set_cur_tab_by_id(PaneViewKaraoke);
      }
      return true;
   }

   void view::WaveInDataProc(
      audWaveIn * pwavein,
      DWORD dwSampleTime, 
      LPWAVEHDR lpwavehdr)
   {
      
      UNREFERENCED_PARAMETER(dwSampleTime);

      ASSERT(lpwavehdr != NULL);
      
      //critical_section & csHandle = pwavein->GetHandleCriticalSection();
        

      //ikar::data & data = GetKaraokeData();
//      ikar::karaoke * pinterface = data.GetInterface();

//      ikar::static_data & staticdata = data.GetStaticData();

      
      audWaveBuffer & buffer = pwavein->GetBuffer();
      buffer.FFTProcess(lpwavehdr);

   //   DWORD msPosition;
   //   DWORD dwPositionTime;
   //   ikar::CPosition tkPosition;
   //   pinterface->GetPosition(tkPosition);
   //   dwPositionTime = timeGetTime();
   //   msPosition = pinterface->PositionToTime(tkPosition);
   //   msPosition -= dwPositionTime - dwSampleTime;

      // Valor de Correção
   //   msPosition -= 100;
      
   /*   double dDeltaScore = -100.0;
      CEventsTracksV1 * peventsa = &staticdata.m_eventsTracksForScoring;
      CLyricEventsV2 * pevents;
      if(staticdata.m_str2aRawTokens.get_size() <= 0)
         pevents = NULL;
      else if(peventsa->get_size() < staticdata.m_str2aRawTokens.get_size())
         pevents = NULL;
      else
      {
         //pEvents = (CLyricEventsV2 *) pEventsArray->operator [](pDoc->m_p2DTokens->get_size());
         pevents = (CLyricEventsV2 *) peventsa->operator [](0);
         ASSERT(pevents != NULL);
         ASSERT(pevents->GetClassOrder() == 2);
      }
         
      if(pevents != NULL)
      {
         int i;
         m_iaNotes.remove_all();
         pevents->GetMillisIntervalNotes(
            m_iaNotes,
            msPosition  - pwavein->GetAnalysisMillis() - 100,
            msPosition);
         dDeltaScore = 0;
         dword_array dwaNotes;
         for(i = 0; i < m_iaNotes.get_size(); i++)
         {
            dwaNotes.add(pevents->GetNotePitch(m_iaNotes.element_at(i)));
         }
         ikar::class time timeLength;
         pinterface->GetTimeLength(timeLength);
         Process(&dwaNotes, (double) msPosition / timeLength, &dDeltaScore );
      }*/


   }

   void view::_001OnExecutePrevious(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecutePrevious);
   }

   void view::_001OnUpdateExecutePrevious(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(true);
      pupdatecmdui->m_bRet = true;
   }

   void view::_001OnExecuteNext(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecuteNext);
   }

   void view::_001OnUpdateExecuteNext(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(true);
      pupdatecmdui->m_bRet = true;
   }

   void view::_001OnExecuteAutoRecord(gen::signal_object * pobj)
   {  
      UNREFERENCED_PARAMETER(pobj);
      _ToggleAutoRecord();
   }

   void view::_001OnUpdateExecuteAutoRecord(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable();
      pupdatecmdui->m_pcmdui->_001SetCheck(m_bAutoRecord);
      pupdatecmdui->m_bRet = true;
   }



} // namespace mplite