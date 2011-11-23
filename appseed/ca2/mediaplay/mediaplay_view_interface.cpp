#include "StdAfx.h"

#include <math.h>         // Header File For Windows Math Library
#include <shlobj.h>

#include "audio/audio.h"

#include "kar/KaraokeBouncingBall.h"

#ifdef WIN32
   BOOL win_SHGetSpecialFolderPath(HWND hwnd, string &str, int csidl, BOOL fCreate)
   {
      string wstrPath;
      wchar_t * lpsz = (wchar_t *) malloc(MAX_PATH * sizeof(WCHAR) * 4);
      BOOL b = ::SHGetSpecialFolderPathW(
         hwnd,
         lpsz,
         csidl,
         fCreate);
      gen::international::unicode_to_utf8(str, lpsz);
      free(lpsz);
      return b;
   }
#endif


namespace mediaplay
{

   view_interface::view_interface(::ca::application * papp) :
      ca(papp),
      m_hglrc(NULL),
      kar::KaraokeView(papp),
      m_fileRecord(papp),
      gcom::backview::user::interaction(papp),
      gcom::backview::Interface(papp),
      midi_player_interface(papp),
      audio::WavePlayerInterface(papp),
      audio::WaveRecorderInterface(papp),
      m_viewlineaStatus(papp),
      m_spgraphics(papp),
      midi_player_callback(papp)
   /*   m_pixelformatdescriptor(
      sizeof(PIXELFORMATDESCRIPTOR),            // size Of This Pixel Format Descriptor
      1,                                 // Version Number
      PFD_DRAW_TO_WINDOW |                  // Format Must Support Window
      PFD_SUPPORT_OPENGL |                  // Format Must Support OpenGL
      PFD_DOUBLEBUFFER,                     // Must Support Double Buffering
      PFD_TYPE_RGBA,                        // Request An RGBA Format
      24,                              // Select Our color Depth
      0, 0, 0, 0, 0, 0,                     // color Bits Ignored
      0,                                 // No Alpha buffer
      0,                                 // Shift Bit Ignored
      0,                                 // No Accumulation buffer
      0, 0, 0, 0,                           // Accumulation Bits Ignored
      16,                                 // 16Bit Z-buffer (Depth buffer)
      0,                                 // No Stencil buffer
      0,                                 // No Auxiliary buffer
      PFD_MAIN_PLANE,                        // Main Drawing Layer
      0,                                 // Reserved
      0, 0, 0                              // Layer Masks Ignored
   )*/
   {
      m_dataid = "mediaplay::view_interface";
      m_precordnotifyview = new ::mediaplay::record_notify_view(papp);

      m_spgraphics->CreateCompatibleDC(NULL);

      m_bEnableShowGcomBackground   = true;
      m_bShowGcomBackground         = false;

      m_pplaylistcallback           = NULL;

      m_dBlend                      = 0.0;

      m_pdocument                   = NULL;
      //   m_tab.InstallMessageHandling(this);
      m_pixelformatdescriptor.nSize= sizeof(PIXELFORMATDESCRIPTOR);
      m_pixelformatdescriptor.nVersion = 1;
      m_pixelformatdescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      m_pixelformatdescriptor.iPixelType = PFD_TYPE_RGBA;
      m_pixelformatdescriptor.cColorBits = 24;
      m_pixelformatdescriptor.cRedBits = 0;
      m_pixelformatdescriptor.cRedShift = 0;
      m_pixelformatdescriptor.cGreenBits = 0;
      m_pixelformatdescriptor.cGreenShift = 0;
      m_pixelformatdescriptor.cBlueBits = 0;
      m_pixelformatdescriptor.cBlueShift = 0;
      m_pixelformatdescriptor.cAlphaBits = 0;
      m_pixelformatdescriptor.cAlphaShift = 0;
      m_pixelformatdescriptor.cAccumBits = 0;
      m_pixelformatdescriptor.cAccumRedBits = 0;
      m_pixelformatdescriptor.cAccumGreenBits = 0;
      m_pixelformatdescriptor.cAccumBlueBits = 0;
      m_pixelformatdescriptor.cAccumAlphaBits = 0;
      m_pixelformatdescriptor.cDepthBits = 24;
      m_pixelformatdescriptor.cStencilBits = 0;
      m_pixelformatdescriptor.cAuxBuffers = 0;
      m_pixelformatdescriptor.iLayerType = PFD_MAIN_PLANE;
      m_pixelformatdescriptor.bReserved = 0;
      m_pixelformatdescriptor.dwLayerMask = 0;
      m_pixelformatdescriptor.dwVisibleMask = 0;
      m_pixelformatdescriptor.dwDamageMask = 0;


      m_iScalarTempo = 1;
      m_iScalarPos = 2;
      m_iScalarKeyShift = 3;




      m_pwaverecorder = AfxBeginThread < audWaveRecorder > (get_app());





      m_bWaitingToPlay = false;
      m_bDestroy = false;





   //   m_lpbouncingball->SetIcons(System.LoadIcon(IDI_BB1), System.LoadIcon(IDI_BB1_PRESSED1));

   //   _000HookWndProc((gcom::backview::Interface *) &BackViewGetInterface());
      //xxxBackViewGetInterface().SetBackgroundImageChangeInterval(((CVmpLightApp *) &System)->m_iBackgroundUpdateMillis);

      //xxxCVmsDataServerInterface & db = ((CVmpLightApp *) &System)->GetVmsDataServerInterface();
      //xxxdb.AddClient(this);
      //xxxm_relCodePage.add(ID_VIEW_ENCODING_LATIN1, 1252);
      //xxxm_relCodePage.add(ID_VIEW_ENCODING_SHIFTJIS, 932);

   }

   bool view_interface::Initialize(midi_central * pmidicentral)
   {
      m_pmidicentral = pmidicentral;
      if(!midi_player_interface::Initialize(pmidicentral))
         return false;

      return true;
   }

   bool view_interface::Finalize()
   {
      if(!midi_player_interface::Finalize())
         return false;

      return true;
   }

   view_interface::~view_interface()
   {
      if(m_precordnotifyview != NULL)
      {
         delete m_precordnotifyview;
         m_precordnotifyview = NULL;
      }
   }

   void view_interface::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      gcom::backview::Interface::install_message_handling(pinterface);
      kar::KaraokeView::install_message_handling(pinterface);
      m_lyrictemplatelines.InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view_interface::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view_interface::_001OnCreate);
   }



   data * view_interface::get_data()
   {
      if(m_pdocument == NULL)
         return NULL;
      return m_pdocument->get_data();
   }




   class ::radix::thread * view_interface::GetMidiPlayerCallbackThread()
   {
      return NULL;
   }

   ::mus::midi::sequence & view_interface::GetMidiSequence()
   {
      return get_data()->GetMidiSequence();
   }

   void view_interface::_ExecutePlay(bool bMakeVisible, const imedia::position & position)
   {

      UNREFERENCED_PARAMETER(bMakeVisible);

      if(!OnExecuteBeforePlay())
         return;

      if(m_bAutoRecord)
      {
         try
         {
            _StartRecording();
         }
         catch(...)
         {
         }
      }

      data * pdata = get_data();

      switch(pdata->GetMode())
      {
      case data::ModeWave:
         {
            audWavePlayerCommand command;
   //         command.OpenDevice();
     //       GetWavePlayer()->ExecuteCommand(command);
            command.Play(position);
            GetWavePlayer()->ExecuteCommand(command);
         }
         break;
      case data::ModeMidi:
         {
            ::mus::midi::sequence & midisequence = GetMidiSequence();
            ASSERT(&midisequence != NULL);

//            ikar::data & data = GetKaraokeData();
//            ikar::static_data & staticdata = data.GetStaticData();
//            ikar::dynamic_data& dynamicdata = data.GetDynamicData();

            if(midisequence.GetState() != ::mus::midi::sequence::StatusOpened)
            {
               return;
            }
            ASSERT(midisequence.GetState() == ::mus::midi::sequence::StatusOpened);

            if(GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened)
            {
               SetTitleVisible(true);
               pdata->m_bPlay = true;

               //_ExecuteListenMinusOne(GetListenMinusOneCheck());
               GetMidiPlayer()->SendReset();
               //GetMidiSequence().SetSpecialModeV001Operation(::mus::midi::sequence::SPMV001GMReset);
               // execution continues in OnMmmsgDone
               GetMidiPlayer()->Play(position);
            }
         }
         break;
      }

   }

   void view_interface::on_delete_contents()
   {
      data * pdata = get_data();
      if(pdata == NULL)
         return;
      switch(pdata->GetMode())
      {
      case data::ModeMidi:
         {
            _ExecuteStop();
            CloseDevice();
         }
         break;
      case data::ModeWave:
         {
            _ExecuteStop();
            CloseDevice();
         }
         break;
      case data::ModeNone:
         {
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      KaraokeView::clear();
   }


   void view_interface::CloseDevice()
   {
      data * pdoc = get_data();
      switch(pdoc->GetMode())
      {
      case data::ModeMidi:
         {
            if(m_pmidiplayer == NULL)
               return;
            if(!m_pmidiplayer->ExecuteCommand(MidiPlayerCommandCloseDevice, INFINITE))
            {
               TRACE("view_interface::CloseDevice: close device seems to have been failed.");
            }
         }
         break;
      case data::ModeWave:
         {
            audWavePlayerCommand command;
            command.CloseDevice();
            GetWavePlayer()->ExecuteCommand(command);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   }

   mediaplaylist::callback_interface * view_interface::GetPlaylistCallback()
   {
      return m_pplaylistcallback;
   }


   void view_interface::_ExecuteStop()
   {
      data * pdoc = get_data();
      switch(pdoc->GetMode())
      {
      case data::ModeMidi:
         {
            if(_ExecuteIsWaitingToPlay())
            {
               m_bWaitingToPlay = false;
            }
            else
            {

               if(m_pmidiplayer == NULL)
                  return;
               if(m_pmidiplayer->IsPlaying())
               {
                  if(!m_pmidiplayer->ExecuteCommand(MidiPlayerCommandStop, 84))
                  {
                     TRACE("view_interface::_ExecuteStop: Execute stop seems to have been failed.");
                  }
               }
            }
         }
      break;
      case data::ModeWave:
         {
            audWavePlayerCommand command;
            command.Stop();
            GetWavePlayer()->ExecuteCommand(command);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

   void view_interface::_ExecuteStopAndQuit()
   {
      data * pdoc = get_data();
      switch(pdoc->GetMode())
      {
      case data::ModeMidi:
         {
            if(_ExecuteIsWaitingToPlay())
            {
               m_bWaitingToPlay = false;
            }
            else
            {

               if(m_pmidiplayer == NULL)
                  return;

               if(!m_pmidiplayer->ExecuteCommand(MidiPlayerCommandStop, 84))
               {
                  TRACE("view_interface::_ExecuteStop: Execute stop seems to have been failed.");
               }

            }
         }
      break;
      case data::ModeWave:
         {
            audWavePlayerCommand command;
            command.Stop();
            GetWavePlayer()->m_commandlistStopOpen.remove_all();
            GetWavePlayer()->ExecuteCommand(command);
            GetWavePlayer()->m_pwaveout->m_eventStopped.wait(seconds(60));
            GetWavePlayer()->PostThreadMessageA(WM_QUIT, 0, 0);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }


   /*void view_interface::OnUpdateExecuteStop(cmd_ui * pcmdui)
   {
      bool bEnable = false;
      data * pdoc = get_data();
      switch(pdoc->GetMode())
      {
      case data::ModeMidi:
         {
            bEnable = GetMidiPlayer() &&
                  (GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPaused ||
                  GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying ||
                  ExecuteIsWaitingToPlay());
            break;
         }
      case data::ModeWave:
         {
   //         bEnable = GetWavePlayer() != NULL
     //          && GetWavePlayer()->IsPlaying();
            break;
         }
      }

      pcmdui->Enable(bEnable);
   }*/

   /*void view_interface::OnExecutePause()
   {
      ExecutePause();
   }*/

   void view_interface::_ExecutePause()
   {
      GetMidiPlayer()->Pause();
   }

   /*void view_interface::OnUpdateExecutePause(cmd_ui * pcmdui)
   {
      pcmdui->Enable(ExecuteGetPauseEnable());
      pcmdui->SetCheck(ExecuteIsPaused() ? 1 : 0);
   }*/

   bool view_interface::_ExecuteIsPaused()
   {
      return GetMidiPlayer() &&
         GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPaused;
   }

   bool view_interface::_ExecuteGetPauseEnable()
   {

      if(get_data() == NULL)
         return false;

      switch(get_data()->GetMode())
      {
      case data::ModeNone:
         {
            return false;
         }
      case data::ModeMidi:
         {
            ::mus::midi::sequence::Status  estatus = (::mus::midi::sequence::Status) GetMidiSequence().GetState();
            return estatus == ::mus::midi::sequence::StatusPaused ||
               estatus == ::mus::midi::sequence::StatusPlaying;
         }
      case data::ModeWave:
         {
            return false;
         }
      default:
         ASSERT(FALSE);
         return false;
      }
   }


   bool view_interface::_ExecuteGetPlayEnable()
   {
      data * pdata = get_data();
      if(pdata == NULL)
         return false;
      switch(pdata->GetMode())
      {
      case data::ModeNone:
         return false;
      case data::ModeMidi:
         return GetMidiPlayer()
            && (pdata->GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened)
            && !_ExecuteIsWaitingToPlay();
      case data::ModeWave:
         return GetWavePlayer()->GetPlayEnable();
      default:
         ASSERT(FALSE);
         return false;
      }
   }

   bool view_interface::_ExecuteGetStopEnable()
   {
      data * pdata = get_data();
      if(pdata == NULL)
         return false;
      switch(pdata->GetMode())
      {
      case data::ModeNone:
         return false;
      case data::ModeMidi:
         return GetMidiPlayer() &&
                  (GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPaused ||
                  GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying ||
                  _ExecuteIsWaitingToPlay());
      case data::ModeWave:
         return GetWavePlayer() != NULL &&
                  GetWavePlayer()->IsPlaying();
      default:
         ASSERT(FALSE);
         return false;
      }

   }



   void view_interface::_ExecuteListenMinusOne(bool bMinusOne)
   {
      ikar::data & data = GetKaraokeData();
      if(get_data()->GetMode() == data::ModeMidi)
      {
         midi_player * pplayer = GetMidiPlayer();
         ::mus::midi::sequence & sequence = pplayer->GetSequence();
         //::mus::midi::file & file = sequence.GetFile();
         int iTrack = data.GetStaticData().GetGuessMelodyTrack();
         sequence.MuteAll(
            false,
            bMinusOne ? iTrack : -1);
         /*sequence.MuteTrack(
            iTrack,
            bMinusOne);*/
      }
      bool bPreviousMinusOne = false;
      if(!DBListenMinusOne(false, m_pdocument->get_path_name(), bPreviousMinusOne)
      || is_different(bPreviousMinusOne, bMinusOne))
      {
         DBListenMinusOne(true, m_pdocument->get_path_name(), bMinusOne);
      }

   }

   void view_interface::_ExecuteToggleListenMinusOne()
   {
      data * pdata = get_data();
      ikar::data & data = GetKaraokeData();
      ASSERT(_ExecuteGetListenMinusOneEnable());
      if(_ExecuteGetListenMinusOneEnable())
      {
         switch(pdata->GetMode())
         {
         case data::ModeWave:
            {
               GetWavePlayer()->Devocalize(!GetWavePlayer()->IsDevocalized());
            }
            break;
         case data::ModeMidi:
            {
               midi_player * pplayer = GetMidiPlayer();
               ::mus::midi::sequence & sequence = pplayer->GetSequence();
               ::mus::midi::file & file = sequence.GetFile();
//               midi_tracks & tracks = file.GetTracks();
               int iTrack = data.GetStaticData().GetGuessMelodyTrack();
               bool bMute = file.IsTrackMute(iTrack);
               _ExecuteListenMinusOne(!bMute);
            }
            break;
         default:
            ASSERT(FALSE);
            break;
         }
      }
   }


   bool view_interface::_ExecuteGetListenMinusOneEnable()
   {

      bool bEnable = (GetMidiPlayer() != NULL
         && (GetMidiSequence().GetState() == ::mus::midi::sequence::StatusOpened
         || GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying))
         ||
         (GetWavePlayer() != NULL
         && (GetWavePlayer()->IsPlaying()
            || GetWavePlayer()->DecoderIsOpened()));
      return bEnable;

   }

   bool view_interface::GetListenMinusOneCheck()
   {
      data * pdata = get_data();
      if(_ExecuteGetListenMinusOneEnable())
      {
         switch(pdata->GetMode())
         {
         case data::ModeWave:
            {
               return GetWavePlayer()->IsDevocalized();
            }
            break;
         case data::ModeMidi:
            {
               bool b;
               data * pdoc = get_data();
               if(!DBListenMinusOne(false, pdoc->get_path_name(), b))
                  return 0;
               else
                  return b ? 1 : 0;
            }
         default:
            return false;
         }
      }
      else
         return 0;
   }



   void view_interface::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
   {
      midi_player_interface::OnMidiPlayerNotifyEvent(pdata);
      ::mus::midi::sequence & seq = pdata->m_pplayer->GetSequence();
      ASSERT(&seq == &GetMidiSequence());
      data * pdoc = get_data();

      switch(pdata->m_enotifyevent)
      {
      case  ::mus::midi::player::NotifyEventPlaybackStart:
         OnMediaPlaybackStart();
         break;
      default:
         break;
      }

      if(pdata->m_enotifyevent
      == ::mus::midi::player::NotifyEventPositionSet)
      {
   //      OnProgressRateChange(); TODO
      }

      if(pdata->m_enotifyevent == ::mus::midi::player::NotifyEventGenericMmsgDone
         && pdoc->m_bPlay)
      {

   //      double dRate =   GetProgressSlider()->GetRate();

         //if(dRate == 0.0)
         {
            //Show Title
     //       ShowTitle();

            // time to let the title be visible
       //     m_msPlayTimeOut = timeGetTime() + 3000;

            //       Sleep(3000);
         }
   //      else
         {
   //         m_msPlayTimeOut = timeGetTime();
         }
         m_dwPlayWait = GetTickCount() + 1000;
         m_bWaitingToPlay = true;
         pdoc->m_bPlay = false;
      }
      //   else if(lpmdd->SequenceWasInSpecialModeV001())
      //  {
      //    TRACE("data::OnMmsgDone lpmdd->SequenceWasInSpecialModeV001()\n");
      //}
   //   else if(ExecuteIsSettingNextSong())
     /* {
         TRACE("data::OnMmsgDone IsSettingNextSong()\n");
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
      else if(pdata->m_enotifyevent == ::mus::midi::player::NotifyEventPlaybackEnd)
      {
         OnMediaPlaybackEnd();
         TRACE("data::OnMmsgDone NotifyEventPlaybackEnd \n");
      }
      else if(pdata->m_enotifyevent == ::mus::midi::player::NotifyEventMidiStreamOut)
      {
      }
      else if(pdata->m_enotifyevent
         == ::mus::midi::player::NotifyEventStop)
      {
         OnMediaPlaybackEnd();
         //m_fileRecord.close();

         TRACE("data::OnMmsgDone Else if Stopping\n");
   //      pdoc->StartScoring(false);
     //    m_dProgressRate = 0.0;
       //  CXfplayerViewUpdateHint uh;
         //uh.AddType(CXfplayerViewUpdateHint::TypeProgressRateChange);
         //pdoc->update_all_views(NULL, 0, &uh);

      }
      else
      {
         int i = 0;
         i++;
      }
   //   pdoc->OnMidiPlayerNotifyEvent(pdata);

   }

   bool view_interface::_ExecuteIsWaitingToPlay()
   {
      return m_bWaitingToPlay;
   }

   void view_interface::_001OnCreate(gen::signal_object * pobj)
   {

      if(pobj->previous())
         return;

      if(!data_get("General.AutoRecord", m_bAutoRecord))
      {
         m_bAutoRecord = true;
      }

   }

   void view_interface::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      DWORD dwNow = GetTickCount();
      switch(ptimer->m_nIDEvent)
      {
      case TimerLyric:
         {
            rect_array recta;
            ::ca::graphics * pdc = GetDC();
            m_viewlineaStatus[0].OnTimerAnimate(pdc, recta);
            pdc->SelectClipRgn(NULL);
            ReleaseDC(pdc);
            _001RedrawWindow();
         }
         break;
      case 10:
         {
            try
            {
               if(_ExecuteIsPlaying())
               {
                  if(&Application.GetPlaylistCentral() != NULL)
                  {
                     if(Application.GetPlaylistCentral().GetCurrentPlaylist() != NULL)
                     {
                        data * pdata = get_data();
                        if(pdata != NULL)
                        {
                           imedia::position pos = 0;
                           switch(pdata->GetMode())
                           {
                           case data::ModeWave:
                              pos = GetWavePlayer()->GetWaveOut()->get_position_for_synch();
                              break;
                           case data::ModeMidi:
                              GetMidiSequence().get_position(pos);
                              break;
                           }
                           Application.GetPlaylistCentral().GetCurrentPlaylist()->set_int("current_song_position", (int) pos.m_number);
                        }
                     }
                  }
               }
            }
            catch(...)
            {
            }
         }
         break;
      case TimerFadeOut:
         {
            double dRate = 3000; // Fade out completely milliseconds.
            DWORD dwNow = GetTickCount();
            m_dBlend = 1.0 - ((dwNow - m_dwLastFade) / dRate);
            if(m_dBlend <= 0.0)
            {
               m_dBlend = 0.0;
               SetTitleVisible(false);
               _001RedrawWindow();
               KillTimer(TimerFadeOut);
               OnFadeOutEnd();
            }
            else
            {
               m_plinesTitle->SetBlend(m_dBlend);
               _001RedrawWindow();
            }
         }
         break;
      case TimerFadeIn:
         {
            double dRate = 5000; // Fade out completely milliseconds.
            DWORD dwNow = GetTickCount();
            m_dBlend = (dwNow - m_dwLastFade) / dRate;
            if(m_dBlend >= 1.0)
            {
               m_dBlend = 1.0;
               m_plinesTitle->SetBlend(1.0);
               _001RedrawWindow();
               KillTimer(TimerFadeIn);
            }
            else
            {
               m_plinesTitle->SetBlend(m_dBlend);
               _001RedrawWindow();
            }
         }
         break;
      /*case TimerSongInfo:
         {
            TRACE("*");
            ::ca::graphics * pdc = GetDC();
            rect_array recta;
            m_viewlineStatus.OnTimerAnimate(pdc, recta);
            pdc->SelectClipRgn(NULL);
            ReleaseDC(pdc);
            UpdateScreen(recta, RDW_UPDATENOW | RDW_INVALIDATE);
         }*/
         break;
      }

      if(_ExecuteIsWaitingToPlay())
      {
         if(GetTickCount() > m_dwPlayWait)
         {
            StartMusicRendering();
         }
      }
      if(m_rectaUpdate.get_size() > 0)
      {
         if(dwNow - m_dwLastUpdate > 83)
         {
            rect_array recta;
            UpdateScreen(recta, 0);
         }
      }
      ptimer->m_bRet = false;
   }




   void view_interface::StartMusicRendering()
   {
   //   SetWaitingToPlay(false); TODO
      m_bWaitingToPlay = false;

//      data * pdoc = get_data();

   /*   CXfplayerViewUpdateHint uh;


      CXfplayerDoc * pdoc = get_data();
      uh.AddType(CXfplayerViewUpdateHint::UpdateSimpleLyricsNoRepaint);
      pdoc->update_all_views(NULL, 0L, &uh);*/

      //frame_window * pMainFrame = GetParentFrame();

      midi_player * pmidiplayer = GetMidiPlayer();

      ::mus::midi::sequence & midisequence = pmidiplayer->GetSequence();
      ASSERT(!midisequence.IsNull());

   //   CXfplayerScoring * pscoring = pdoc->GetScoring();
     // ASSERT(pscoring != NULL);

   //   double dRate =   GetProgressRate();

      try
      {
   //      pmidiplayer->SetMessageWindow(plyriSimpleView->m_hWnd);
     //    pmidiplayer->Play(dRate);
             pmidiplayer->Play(0.0);
         pmidiplayer
            ->GetSequence()
            .GetFile()
            .GetFlags().unsignalize(::mus::midi::DisablePlayLevel1Operations);
         pmidiplayer
            ->GetSequence()
            .GetFile()
            .GetTracks()
            .GetFlags().unsignalize(::mus::midi::DisablePlayLevel1Operations);
      }
   //   catch(midi_exception * pe)
      catch(...)
      {
   /*xxx      CErrorDialog ed;
         ed.Initialize(pe);
         ed.DoModal();
         //                      pApp->SetPlayingDocument(NULL);
         pe->Delete();*/
         return;
      }

   //   pdoc->StartScoring(true);

     // pdoc->Show(pdoc->ShowSongLabelInformation, false);

   //   uh.clear();
     // uh.AddType(CXfplayerViewUpdateHint::UpdateSongLabelInformation);
      //pdoc->update_all_views(NULL, 0L, &uh);

   }

   void view_interface::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
   {
      for(int i = 0; i < pevents->get_size(); i++)
      {
         OnLyricEvent(&pevents->element_at(i), true);
      }
   }


   VMSRESULT view_interface::UpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UNREFERENCED_PARAMETER(uiRedraw);
      m_rectaUpdate.add(recta);
      DWORD dwNow = GetTickCount();
      if(m_rectaUpdate.get_size() <= 0)
      {
         m_dwLastUpdate = dwNow;
         return 0;
      }
      DWORD dwElapseOptimization = 83;
      if(dwNow - m_dwLastUpdate < dwElapseOptimization)
      {
   //      TRACE("Great Optimization!\n");
         return 0;
      }
      m_dwLastUpdate = dwNow;
      _001RedrawWindow();
      m_rectaUpdate.remove_all();
      return 0;
   }


   bool view_interface::BackViewGetDestroy()
   {
      return m_bDestroy;
   }

   void view_interface::_001OnSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::size, psize, pobj)
      m_precordnotifyview->SetWindowPos(NULL, max(0, psize->m_size.cx - 20), max(0, psize->m_size.cy - 100), 20, 100, 0);
   }

   void view_interface::BackViewFeedback(::ca::graphics *pdc)
   {
      KaraokeRender(pdc);
   }

   void view_interface::_001OnTopDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   void view_interface::_001OnDraw(::ca::graphics * pdc)
   {
      LyricEventV1 levent;
      levent.m_iType    = ikar::event_timer;
      levent.m_pdc      = m_spgraphics;
      OnLyricEvent(&levent, false);


      rect rectClient;
      GetClientRect(rectClient);


      pdc->SelectClipRgn(NULL);

      if(m_bShowGcomBackground && m_bEnableShowGcomBackground)
      {
         if(gcom::backview::Interface::IsEnabled())
         {
            gcom::backview::Main & main = gcom::backview::Interface::GetMain();
            gcom::backview::Graphics & graphics = main.GetGraphics();

            main.DeferCheckLayout();

            if(main.IsInitialized())
            {

               ::ca::region_sp rgn(get_app());
               rect rect(graphics.m_rectFinalPlacement);
               ClientToScreen(rect);
               rgn->CreateRectRgnIndirect(rect);
               pdc->SelectClipRgn(rgn);

               gcom::backview::Interface::BackViewRender(pdc, rectClient);
               pdc->SelectClipRgn(NULL);

            }
         }
         else
         {
            //pdc->FillSolidRect(rectClient, RGB(200, 220, 180));
         }
      }

      _001OnTopDraw(pdc);

      KaraokeRender(pdc);

      if(!m_bTransferVoid)
      {
         rect rect;
         m_viewlineaStatus[0].GetRect(rect);
         rect_array recta;
         ::ca::pen_sp pen(get_app(), PS_SOLID, 1, RGB(255, 255, 255));
         m_viewlineaStatus[0].to(get_app(), pdc, true, rect, recta, NULL, false, RGB(0, 0, 0), pen);
      }

   }

   void view_interface::KaraokeBouncingBall()
   {

      if(!m_bBouncingBall)
      {
         m_bBouncingBall = true;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         System.wait_twf();
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      else
      {
         m_bBouncingBall = false;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         System.wait_twf();
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      RedrawWindow();
      data_set("BouncingBall", ::radix::system::idEmpty, m_bBouncingBall ? 1 : 0);
   }

   /*void view_interface::OnUpdateKaraokeBouncingBall(cmd_ui * pcmdui)
   {
      pcmdui->Enable();
      pcmdui->SetCheck(m_bBouncingBall ? 1: 0);

   }*/

   void view_interface::KaraokeGradualFilling()
   {

      if(!m_bGradualFilling)
      {
         m_bGradualFilling = true;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         System.wait_twf();
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      else
      {
         m_bGradualFilling = false;
         keeper < bool > keepHardWriting(&m_bHardWriting, true, false, true);
         System.wait_twf();
         PrepareLyricLines();
         PrepareLyricTemplateLines();
      }
      RedrawWindow();
      data_set("GradualFilling", ::radix::system::idEmpty, m_bGradualFilling ? 1 : 0);
   }

   /*void view_interface::OnUpdateKaraokeGradualFilling(cmd_ui * pcmdui)
   {
      pcmdui->Enable();
      pcmdui->SetCheck(m_bGradualFilling ? 1: 0);

   }*/



   /*void view_interface::OnExecuteMinusOne()
   {
      ExecuteToggleListenMinusOne();
   }

   void view_interface::OnUpdateExecuteMinusOne(cmd_ui * pcmdui)
   {
      pcmdui->Enable(ExecuteGetListenMinusOneEnable());
      pcmdui->SetCheck(GetListenMinusOneCheck());
   }*/



   int view_interface::InitGL()
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

   ::ca::graphics * view_interface::GetGdi()
   {
      return m_gdi;
   }


   DWORD view_interface::GetKaraokeCodePage(const char * lpsz)
   {
      string strLyrics;
      if(lpsz == NULL)
      {
         GetKaraokeData().GetStaticData().GetLyrics(strLyrics);
         lpsz = (const char *) strLyrics;
      }
   /*    CVmsDataServerInterface & db = ((CVmpLightApp *) &System)->GetVmsDataServerInterface();

      COleVariant var;
      var.vt = VT_I4;
      DWORD dwCodePage;

      //if(db.get_data(_vmsp::CConfiguration::CfgKaraokeEncoding, GetLanguage(), 0, var))
      if(db.get_data(
         _vmsp::CConfiguration::CfgKaraokeEncoding,
         0,
         0,
         var))
      {
         ASSERT(var.vt == VT_I4);
         dwCodePage = var.intVal;
         return dwCodePage;
      }
      else
         return CP_OEMCP;*/

      return KaraokeGetCodePage(lpsz);

   }

   DWORD view_interface::IdToCodePage(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      ASSERT(FALSE);
      dword_array dwa;
   //   m_relCodePage.GetFromA(uiId, dwa);
     // ASSERT(dwa.get_size() > 0);
      //return dwa[0];
      return 0xffffffff;
   }

   void view_interface::SetKaraokeCodePage(DWORD dw)
   {
      UNREFERENCED_PARAMETER(dw);
   /*     CVmsDataServerInterface & db = ((CVmpLightApp *) &System)->GetVmsDataServerInterface();

      COleVariant var;
      var.vt = VT_I4;
      var.lVal = dw;

   //   db.set_data(
     //    _vmsp::CConfiguration::CfgKaraokeEncoding,
       //  GetLanguage(),
         //0,
         //var);
      db.set_data(
         _vmsp::CConfiguration::CfgKaraokeEncoding,
         0,
         0,
         var);*/

   }

   LONG GetRegKey(HKEY key, const char * subkey, LPTSTR retdata)
   {
       HKEY hkey;
       LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);
       if (retval == ERROR_SUCCESS)
       {
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


   HCURSOR view_interface::KaraokeGetHandCursor()
   {
   //   return System.LoadCursor(IDC_HAND_POINTER);
      return System.LoadStandardCursor(IDC_ARROW);
   }

   void view_interface::CopyLinkLocation()
   {
   /* trans   if (!KaraokeGetWnd()->OpenClipboard())
      {
         System.simple_message_box( "Cannot open the Clipboard" );
         return;
      }

      // remove the current Clipboard contents
      if(!EmptyClipboard())
      {
         System.simple_message_box( "Cannot is_empty the Clipboard" );
         CloseClipboard();
         return;
      }
      string str;
      gen::international::UnicodeToACP(str, m_wstrCurrentLink);

      HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE,
               (str.get_length() + 1) * sizeof(char));
           if (hglbCopy == NULL)
           {
               CloseClipboard();
               return;
           }

           // lock the handle and copy the text to the buffer.

           LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy);
           memcpy(lptstrCopy, (const char *) str,
               str.get_length() * sizeof(char));
           lptstrCopy[str.get_length()] = (char) 0;    // null character
           GlobalUnlock(hglbCopy);
      // ...
      // get the currently selected data
      // ...
      // For the appropriate data formats...
      if ( ::SetClipboardData( CF_TEXT, hglbCopy ) == NULL )
      {
         System.simple_message_box( "Unable to set Clipboard data" );
         CloseClipboard();
         return;
      }
      // ...
      CloseClipboard();   */
   }


   bool view_interface::_ExecuteIsEntertaining()
   {
      return _ExecuteIsPlaying() || _ExecuteIsWaitingToPlay();
   }

   bool view_interface::_ExecuteIsPlaying()
   {
      return (GetMidiPlayer() != NULL
         && GetMidiSequence().GetState() == ::mus::midi::sequence::StatusPlaying)
         ||
         (GetWavePlayer() != NULL
         && GetWavePlayer()->IsPlaying()
         );
   }

   bool view_interface::DBListenMinusOne(bool bSave, const char * lpcszPathName, bool &bMinusOne)
   {
      string strListenMinusOne;
      strListenMinusOne.Format("%s.ListenMinusOne", lpcszPathName);
      if(bSave)
      {
         data_set(strListenMinusOne, ::radix::system::idEmpty, bMinusOne ? 1 : 0);
         data_set("General.ListenMinusOne", ::radix::system::idEmpty, bMinusOne ? 1 : 0);
         return true;
      }
      else
      {
         int i;
         if(!data_get(strListenMinusOne, ::radix::system::idEmpty, i))
         {
            if(!data_get("General.ListenMinusOne", ::radix::system::idEmpty, i))
            {
               return false;
            }
         }
         bMinusOne = (i == 0) ? false : true;
         return true;
      }

   }

   bool view_interface::OnExecuteBeforePlay()
   {
      return true;
   }

   void view_interface::OnMediaPlaybackEnd()
   {
      if(m_bAutoRecord)
      {
         _StopRecording();
      }

      if(GetPlaylistCallback() != NULL)
      {
         GetPlaylistCallback()->PlaylistOnPlaybackEnd();
      }
   }

   void view_interface::OnMediaPlaybackStart()
   {

      rect rectClient;
      GetClientRect(rectClient);
      rect rect = rectClient;

      ::ca::graphics * pdc = GetDC();

      rect.top = rect.bottom - 24;
      m_viewlineaStatus[0].SetPlacement(rect);
      string strAnimatedTitle;
      strAnimatedTitle = get_data()->GetAnimatedTitle();
      m_viewlineaStatus[0].SetAnimateType(m_viewlineaStatus[0].AnimateRHL);
      m_viewlineaStatus[0].SetFont(System.font_central().GetSongLabelFont());
      m_viewlineaStatus[0].PrepareLine(
         pdc,
         strAnimatedTitle,
         0,
         rectClient);
      m_viewlineaStatus[0].Show();
      ReleaseDC(pdc);

      StartFadeIn();

   }

   UINT AFX_CDECL view_interface::ThreadProcLyricEvent(LPVOID lpParam)
   {
      return 0;
      view_interface * pview = (view_interface *) lpParam;
      //single_lock slBuffer(pview->m_gdibuffer.GetSemaphore());
      event event;
      LyricEventV1 levent;
      levent.m_iType = ikar::event_timer;
      MMRESULT mmr;
      int iResolution = 10;
      int iDelay = 50;
      rect_array recta;
      while(true)
      {
         event.ResetEvent();
         mmr = timeSetEvent(
            max(iResolution, iDelay),
            iResolution,  // 5 ms resolution
            (LPTIMECALLBACK) (HANDLE) event,
            NULL,
            TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);

         if(pview == NULL)
            break;
         if(pview->is_ok_for_rendering())
         {
            pview->OnLyricEvent(&levent, true);
         }

         event.wait();
      }

      return 0;
   }

   void view_interface::_001OnMessageX(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(pbase->m_wparam == 1)
      {
         rect_array * precta = (rect_array *) pbase->m_lparam;
         UpdateScreen(*precta, RDW_INVALIDATE | RDW_UPDATENOW );
         delete precta;
      }
      pbase->set_lresult(0);
   }

   void view_interface::StartFadeIn()
   {
      m_dwLastFade = GetTickCount();
      KillTimer(TimerFadeOut);
      SetTimer(TimerFadeIn, 100, NULL);

   }

   void view_interface::StartFadeOut(
      EExecute eexecuteNow,
      EExecute eexecuteAfterFadeOut)
   {
      _Execute(eexecuteNow);
      m_eexecuteAfterFadeOut = eexecuteAfterFadeOut;
      m_dwLastFade = GetTickCount();
      KillTimer(TimerFadeIn);
      SetTimer(TimerFadeOut, 100, NULL);
   }
   void view_interface::OnFadeOutEnd()
   {
      _Execute(m_eexecuteAfterFadeOut);
   }
   void view_interface::_Execute(EExecute eexecute)
   {
      switch(eexecute)
      {
      case ExecuteNext:
         ASSERT(GetPlaylistCallback() != NULL);
         if(GetPlaylistCallback() != NULL)
         {
            GetPlaylistCallback()->PlaylistPlay(1);
         }
         break;
      case ExecutePrevious:
         ASSERT(GetPlaylistCallback() != NULL);
         if(GetPlaylistCallback() != NULL)
         {
            GetPlaylistCallback()->PlaylistPlay(-1);
         }
         break;
      case ExecuteStop:
         _ExecuteStop();
         break;
      default:
         break;
      }

   }

   void view_interface::_StartRecording()
   {
      try
      {
         if(m_pwaverecorder->IsRecording())
            return;

         audWaveRecorderCommand reccommand;

         string strRec;

         data * pdata = get_data();

         if(pdata == NULL)
            return;

         if(pdata->m_etype == data::TypeRtp)
            return;

         string strPath = pdata->get_path_name();


         string strTitle = System.file().name_(strPath);

         string strFolder = Application.dir().userdata(unitext("Gravações de Karaokê"));
         System.dir().mk(strFolder);


         string strBase;

         strBase = System.dir().path(strFolder, strTitle);

         int i = 1;
         while(true)
         {
            strRec.Format("%s.%d.wav", strBase, i);
            if(!System.file().exists(strRec))
               break;
            i++;
         }
         m_fileRecord->open(strRec, ::ex1::file::mode_create | ::ex1::file::mode_write | ::ex1::file::type_binary);
         reccommand.OpenWavFile(m_fileRecord);
         m_pwaverecorder->ExecuteCommand(reccommand);
         reccommand.Record();
         m_pwaverecorder->ExecuteCommand(reccommand);
      }
      catch(...)
      {
      }

   }

   void view_interface::_StopRecording()
   {
      if(!m_pwaverecorder->IsRecording())
         return;
      audWaveRecorderCommand reccommand;
      reccommand.Stop();
      m_pwaverecorder->ExecuteCommand(reccommand);
   }


   void view_interface::_ToggleAutoRecord()
   {
      _AutoRecord(!m_bAutoRecord);
   }

   void view_interface::_AutoRecord(bool bRecord)
   {
      if(m_bAutoRecord && !bRecord)
      {
         m_bAutoRecord = false;
         if(_ExecuteIsPlaying())
         {
            _StopRecording();
         }
      }
      else if(!m_bAutoRecord && bRecord)
      {
         m_bAutoRecord = true;
         if(_ExecuteIsPlaying())
         {
            _StartRecording();
         }
      }
      data_set("General.AutoRecord", m_bAutoRecord);
   }

   void view_interface::OnSetScalar(int i, double d)
   {
      if(i == m_iScalarTempo)
      {
         int iTempoShift = (int) d;
         if(iTempoShift != GetMidiSequence().GetTempoShift())
         {
            GetMidiPlayer()->SetTempoShift(iTempoShift);
         }
      }
      else
      {
         ASSERT(FALSE);
      }
   }
   double view_interface::GetMinScalar(int i)
   {
      if(i == m_iScalarPos)
      {
         return 0.0;
      }
      else
      {
         ASSERT(FALSE);
         return 0.0;
      }
   }
   double view_interface::GetScalar(int i)
   {
      if(i == m_iScalarPos)
      {
         data * pdata = get_data();
         if(pdata == NULL)
            return 0.0;
         switch(pdata->GetMode())
         {
         case data::ModeWave:
            {
               return (double) GetWavePlayer()->GetWaveOut()->GetPositionMillis();
            }
         case data::ModeMidi:
            {
               imedia::position pos;
               GetMidiSequence().get_position(pos);
               return (double) pos;
            }
         default:
            {
               return 0.0;
            }
         }
      }
      else
      {
         ASSERT(FALSE);
         return 0.0;
      }
   }
   double view_interface::GetMaxScalar(int i)
   {
      if(i == m_iScalarPos)
      {
         data * pdata = get_data();
         if(pdata == NULL)
            return 0.0;
         switch(pdata->GetMode())
         {
         case data::ModeWave:
            {
               return (double) GetWavePlayer()->GetWaveOut()->m_pprebuffer->GetMillisLength();
            }
         case data::ModeMidi:
            {
               imedia::position pos;
               GetMidiSequence().GetPositionLength(pos);
               return (double) pos;
            }
         default:
            {
               return 0.0;
            }
         }
      }
      else
      {
         ASSERT(FALSE);
         return 0.0;
      }
   }


   void view_interface::OnSetScalar(int i, int iValue)
   {
      if(i == m_iScalarKeyShift)
      {
         GetMidiSequence().SetKeyShift(iValue);
      }
      else
      {
         ASSERT(FALSE);
      }
   }
   void view_interface::GetMinScalar(int i, int & iValue)
   {
      if(i == m_iScalarKeyShift)
      {
         iValue = -12;
      }
      else
      {
         ASSERT(FALSE);
      }
   }
   void view_interface::GetScalar(int i, int & iValue)
   {
      if(i == m_iScalarKeyShift)
      {
         if(m_pdocument->get_data() == NULL)
         {
            iValue = 0;
         }
         else
         {
            iValue = GetMidiSequence().GetKeyShift();
         }
      }
      else
      {
         ASSERT(FALSE);
      }
   }
   void view_interface::GetMaxScalar(int i, int & iValue)
   {
      if(i == m_iScalarKeyShift)
      {
         iValue = 12;
      }
      else
      {
         ASSERT(FALSE);
      }
   }

   bool view_interface::is_ok_for_rendering()
   {
      if(!KaraokeView::is_ok_for_rendering())
         return false;
      if(m_pdocument == NULL)
         return false;
      try
      {
         if(m_pdocument->m_bWriting)
            return false;
      }
      catch(...)
      {
         return false;
      }
      if(m_pdocument->get_data() == NULL)
         return false;
      bool bIsWriting = true;
      try
      {
         bIsWriting = m_pdocument->get_data()->is_writing();
      }
      catch(...)
      {
         bIsWriting = true;
      }
      return !bIsWriting;
   }

   int view_interface::KaraokeGetLyricsDelay()
   {
      return m_iDelay;
   }


   bool view_interface::toggle_show_gcom_background()
   {
      return show_gcom_background(!m_bShowGcomBackground);
   }


   bool view_interface::show_gcom_background(bool bShow)
   {

      if(!m_bEnableShowGcomBackground)
         return false;


      gcom::backview::user::interaction * pbackview = NULL;

      bergedge::frame * pframe = GetTypedParent< bergedge::frame >();
      if(pframe != NULL)
      {
         try
         {
            pbackview = pframe->m_pview;
            pbackview->m_dataid = m_dataid;
         }
         catch(...)
         {
            pbackview = this;
         }
      }
      else
      {
         pbackview = this;
      }

      if(pbackview == NULL)
         return false;

      if(bShow)
      {
         if(pbackview->m_spfilesetBackgroundImage.is_set())
         {
            pbackview->m_spfilesetBackgroundImage.delete_this();
         }
         simpledb::file_set * pimagefileset = new simpledb::file_set(get_app());
         pimagefileset->initialize(get_app());
         pimagefileset->m_dataid = "ca2_fontopus_votagus.nature.ImageDirectorySet";

         stringa straFilter;
         straFilter.add("\\*.bmp");
         straFilter.add("\\*.jpg");
         straFilter.add("\\*.png");
         pimagefileset->m_p->add_filter(straFilter);

         bool bInit;
         if(!pimagefileset->data_get("initialize_default", ::radix::system::idEmpty, bInit))
         {
              bInit = true;
         }
         if(bInit)
         {
            pimagefileset->data_set("initialize_default", ::radix::system::idEmpty, false);
#ifdef WIN32
            string strDir;
            win_SHGetSpecialFolderPath(
               NULL,
               strDir,
               CSIDL_WINDOWS,
               FALSE);
            strDir = System.dir().path(strDir, "Web\\Wallpaper");
            pimagefileset->add_search(strDir);
#else
            zz
#endif
         }
         pimagefileset->refresh();

         pbackview->m_spfilesetBackgroundImage.m_p = dynamic_cast < ex2::file_set * > (pimagefileset->m_p);

         pbackview->Enable(true);
         pbackview->SetBackgroundImageChangeInterval(1000);
         if(pbackview->m_dwTimerStep > 0)
         {
            pbackview->KillTimer(pbackview->m_dwTimerStep);
         }
         pbackview->m_dwTimerStep = TimerBackView;
         pbackview->SetTimer(TimerBackView, 83, NULL);  // max. 12 fps
         pbackview->layout();
         pbackview->GetMain().m_bPendingLayout = true;
      }
      else
      {
         pbackview->Enable(false);
      }

      m_bShowGcomBackground = bShow;

      data_set("ShowGcomBackground", ::radix::system::idEmpty, bShow);   


      return true;

   }

} // namespace mediaplay




