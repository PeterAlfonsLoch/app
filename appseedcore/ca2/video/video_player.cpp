#include "StdAfx.h"

namespace video
{

   player::player(::ca::application * papp) :
      ca(papp),
      m_diba(papp),
      ::radix::thread(papp),
      m_decoderset(papp),
      m_decodersetex1(papp),
      m_play(papp),
      m_decode(papp),
      ::audio::WavePlayerInterface(papp)
   {
      m_play.m_pplayer     = this;
      m_decode.m_pplayer   = this;
      m_pdecoder           = NULL;
      m_hwndCallback       = NULL;
      m_estate             = state_initial;
      m_pmediaplaydocument = NULL;
      m_iLastDib           = -1;
      m_diba.set_size(84);
      m_ptsa.set_size(m_diba.get_size());
      m_scaleda.set_size(m_diba.get_size());
      m_iaFrame.set_size(m_diba.get_size());
      m_iPlayDib           = 0;
   }

   player::~player()
   {
   }


#ifdef _DEBUG
   void player::assert_valid() const
   {
      ::radix::thread::assert_valid();
   }

   void player::dump(dump_context & dumpcontext) const
   {
      ::radix::thread::dump(dumpcontext);
   }
#endif //_DEBUG


   void player::_001OnDraw(::ca::graphics * pdc)
   {
      
      uint64_t pts = get_pts();

//      int iAttempt = 0;

      int iDibFound = m_iPlayDib;
      bool bFound = false;

      uint64_t ptsMin = (uint64_t) -1;

      for(int iDib = 0; iDib < m_diba.get_size(); iDib++)
      {
         uint64_t    ptsFrame    = m_ptsa    [iDib];
         bool        bScaled     = m_scaleda [iDib];
         if(bScaled && ptsFrame != (uint64_t) -1 && ptsFrame < ptsMin && ptsFrame >= pts)
         {
            ptsMin = ptsFrame;
            iDibFound = iDib;
            bFound = true;
         }
      }

      if(bFound && !m_pdecoder->m_bDraw)
      {
         m_pdecoder->m_bDraw = true;
         m_pdecoder->m_dwStartTime = ::GetTickCount();
      }

      m_iPlayDib = iDibFound;

      
      ::ca::dib * pdib =  m_pdecoder->decoder_get_frame(m_iPlayDib);
      if(pdib != NULL)
      {
         pdib->to(pdc, m_ptView, pdib->size());
      }

      if(!bFound && m_pdecoder->m_bEmpty && !m_pdecoder->m_bDecoding && !m_pdecoder->m_bScaling)
      {
         pdc->SetBkMode(OPAQUE);
         pdc->SetBkColor(RGB(0, 0, 0));
         pdc->SetTextColor(RGB(215, 255, 220));
         pdc->TextOut(100, 100, unitext("To be Continued... つづく"));
      }

   }


   int player::get_free_frame()
   {

      uint64_t ptsMin = (uint64_t) -1;

      int iDibFound = -1;

      for(int iDib = 0; iDib < m_diba.get_size(); iDib++)
      {
         if(m_ptsa[iDib] < ptsMin)
         {
            ptsMin = m_ptsa[iDib];
            iDibFound = iDib;
         }
         else if(m_ptsa[iDib] == (uint64_t) -1)
         {
            ptsMin = (uint64_t) -1;
            iDibFound = iDib;
            break;
         }
      }

      if(ptsMin < get_pts() || ptsMin == (uint64_t) -1)
      {
         if(iDibFound >= 0)
         {
            m_scaleda[iDibFound] = false;
         }
         return iDibFound;
      }

      return -1;

   }



   bool player::step()
   {
      if(m_iPlayDib == m_iLastDib)
      {
         return false;
      }
      if(!m_pdecoder->step())
      {
         m_bPlay = false;
         return false;
      }
      Sleep(23);
      return true;
   }


   bool player::decode()
   {
      return !m_pdecoder->DecoderEOF();
   }


   player::play_thread::play_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
   }

   int player::play_thread::run()
   {
      while(m_pplayer->step());
      m_pplayer->OnEvent(EventPlaybackEnd);
      return 0;
   }

   player::decode_thread::decode_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
   }

   int player::decode_thread::run()
   {
/*      while(m_pplayer->m_bPlay && m_pplayer->m_pdecoder->m_iLastDib < 0)
      {
         while(m_pplayer->decode() && m_pplayer->m_bPlay);
         Sleep(10);
      }*/
      return 0;
   }


   void player::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(message_command, pinterface, this, &player::OnCommandMessage);
   }

   bool player::DecoderOpen(player_command & command)
   {
      string strDecoder;
      if(command.GetCommand() == command_open_file)
      {
         m_pdecoder = m_decodersetex1.GetNewDecoder(NULL, command.GetOpenFile());
         m_pdecoder->m_pplayer = this;
         m_iOutBufferSampleCount =  48 * 1024;
      }
      else
      {
         switch(command.GetCommand())
         {
         case command_open_file:
            strDecoder = "video_decode_ffmpeg.dll";
            break;
         default:
            return false;
            break;
         }
         m_iOutBufferSampleCount =  48 * 1024;

         video_decode::decoder_plugin * pplugin = m_decoderset.LoadPlugin(strDecoder);
         if(pplugin == NULL)
            return false;

         m_pdecoder = pplugin->NewDecoder();
         if(m_pdecoder != NULL)
         {
            
            m_pdecoder->m_pplayer = this;

            if(command.GetCommand() == command_open_rtp_file)
            {
               if(m_pdecoder->DecoderSetSeekable(false))
               {
                  delete m_pdecoder;
                  return false;
               }
               if(m_pdecoder->DecoderSetReadBlockSize(1024) != 1024)
               {
                  delete m_pdecoder;
                  return false;
               }
               m_iOutBufferSampleCount = 1024; // samples are samples, bytes are bytes
               // each sample may have e.g. n channels * sizeof(short) bytes
            }
            if(!m_pdecoder->DecoderInitialize(command.GetOpenFile()))
            {
               delete m_pdecoder;
               return false;
            }
         }
      }


      return m_pdecoder != NULL;
   }


   void player::DecoderInitialize(ex1::file *pfile)
   {
      UNREFERENCED_PARAMETER(pfile);
      ASSERT(DecoderIsActive());
      //spfile->seek_to_begin();
      //m_pdecoder->DecoderInitialize(pfile);
//      m_pwaveout->SetDecoder(m_pdecoder);
   }

   bool player::DecoderIsActive()
   {
      return m_pdecoder != NULL;
   }

   void player::DecoderClose()
   {
      delete m_pdecoder;
      m_pdecoder = NULL;
   }

   void player::DecoderRun()
   {
   //   m_pdecoder->DecoderRun();
   }


   bool player::initialize_instance()
   {

      return true;
   }

   int player::exit_instance()
   {

      return thread::exit_instance();
   }



   void player::ExecuteCommand(player_command & command)
   {
      switch(command.GetCommand())
      {
      case command_execute_stop:
         {
            CommandMessageProcedure(command);
         }
         break;
      default:
         {
            PostThreadMessage(
               message_command,
               (WPARAM) command.GetCommand(),
               (LPARAM) (new player_command(command)));
         }
      }

   }


   void player::OnCommandMessage(gen::signal_object * pobj)
      //WPARAM wparam, // audCommand enumeration
      //LPARAM lparam  // audCommand object pointer
      //)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      player_command * pcommand = (player_command *) pbase->m_lparam;
      CommandMessageProcedure(*pcommand);
      if(pcommand->m_pbResult != NULL)
      {
         *pcommand->m_pbResult = pcommand->m_bResult;
      }
      delete pcommand;
   }

   bool player::CommandMessageProcedure(player_command &command)
   {
   //   bool bSetEvents = true;
      command.m_bResult = true;
      e_command ecommand = command.GetCommand();
      switch(ecommand)
      {
      case command_open_file:
      case command_open_rtp_file:
         {

            if(IsPlaying())
            {
               return true;
            }

            if(DecoderIsActive())
            {
               DecoderClose();
            }
            if(!DecoderOpen(command))
            {
               command.m_bResult = false;
               break;
            }
            DecoderInitialize(command.GetOpenFile());
            OnEvent(EventOpenDecoder);
         }
         break;
   //xxx   case audCommandOpenDevice:
        // {
          //  m_pwaveout->open(this, 4, m_iOutBufferSampleCount);
            //OnEvent(EventOpenDevice);
         //}
         //break;
      case command_execute_play:
         {
            if(m_commandlistStopOpen.get_count() > 0)
            {
               if(IsPlaying())
               {
                  m_commandlistOpenPlay.add_tail(command);
                  return true;
               }
               else
               {
                  m_commandlistStopOpen.remove_all();
               }
            }
            if(m_pdecoder != NULL)
            {
               if(!IsPlaying())
               {
                  OnEvent(EventOpenDevice);
                  m_pdecoder->DecoderSeekBegin();

                  m_bPlay = true;

                  m_iLastDib = -1;

                  if(m_pdecoder->DecoderGetChannelCount() > 0)
                  {

                     m_paudiodecoder = dynamic_cast < ::audio_decode::decoder * > (m_pdecoder);

                     if(m_paudiodecoder != NULL)
                     {
                        m_paudiodecoder->DecoderSetReadBlockSize(1024 * 512);

                        audWavePlayerCommand command;
                     
                        command.OpenDecoder(m_paudiodecoder);

                        GetWavePlayer()->ExecuteCommand(command);

                     


                        synch_lock lock(m_paudiodecoder);
                        m_paudiodecoder->m_iaLostPosition.remove_all();
                        m_paudiodecoder->m_iaLostCount.remove_all();
                        m_paudiodecoder->m_iRead = 0;
                        m_paudiodecoder->m_iReadExpanded = 0;
                        lock.unlock();

                        m_paudiodecoder->Begin();

                        imedia::position position;

                        command.Play(position);

                        GetWavePlayer()->ExecuteCommand(command);

                     }
                     else if(m_pmediaplaydocument != NULL)
                     {
                        var varFile;
                        varFile["file"] = &m_pdecoder->m_transferfileAudio;
                        varFile["url"] = "untitled.mp3";
                        m_pmediaplaydocument->::mediaplay::document::on_open_document(varFile);
                     }
                  }

                  OnEvent(EventPlay);
                  m_play.Begin();
                  m_decode.Begin();
               }
            }
            else
            {
               command.m_bResult = false;
               break;
            }
         }
         break;
      case command_execute_stop:
         {
            if(m_pdecoder == NULL)
            {
               m_eventStopped.SetEvent();
               command.m_bResult = true;
               break;
            }

            if(m_pdecoder->DecoderGetChannelCount() > 0)
            {
               if(m_paudiodecoder != NULL)
               {
                  GetWavePlayer()->FadeOutAndStop();

                  GetWavePlayer()->m_pwaveout->m_eventStopped.wait(seconds(60));
               }

            }

            m_pdecoder->m_bStop = true;
            
         }
         break;
      case command_execute_pause:
         {
            if(m_commandlistStopOpen.get_count() > 0)
            {
               return false;
            }
         }
         break;
      case command_execute_restart:
         {
            if(m_commandlistStopOpen.get_count() > 0)
            {
               return false;
            }
         }
         break;
   //   case audCommandCloseDevice:
     //    {
       //     m_pwaveout->PostClose();
         //   OnEvent(EventCloseDevice);
         //}
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      command.SetEvents();
      return command.m_bResult;
   }


   void player::AttachEndEvent(event * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
   }


   void player::ExecuteStop()
   {
   }

   bool player::DeviceIsOpened()
   {
      return GetDeviceState() == DeviceStateOpened;
   }

   bool player::DecoderIsOpened()
   {
      return GetDecoderState() == DecoderStateOpened;
   }

   bool player::IsPlaying()
   {
      return GetDeviceState() == DeviceStatePlaying
         || GetDeviceState() == DeviceStateStopping
         || m_estate == StateFadingOutToStop;

   }

   bool player::GetPlayEnable()
   {
      return GetDecoderState() == DecoderStateOpened
         && !IsPlaying();
   }

   bool player::GetStopEnable()
   {
      return IsPlaying();
   }




   void player::OnEvent(e_event eevent)
   {
      switch(eevent)
      {
      case EventOpenDevice:
         SetDeviceState(DeviceStateOpened);
         break;
      case EventOpenDecoder:
         SetDecoderState(DecoderStateOpened);
         if(m_commandlistOpenPlay.get_count() > 0)
         {
            player_command command = m_commandlistOpenPlay.remove_head();
            ExecuteCommand(command);
            m_commandlistOpenPlay.remove_all();
         }
         break;
      case EventPlay:
         SetDeviceState(DeviceStatePlaying);
         SetState(StatePlaying);
         break;
      case EventStop:
         SetDeviceState(DeviceStateStopping);
         SetState(state_initial);
         break;
      case EventFadeOutAndStop:
         SetState(StateFadingOutToStop);
         break;
      case EventExecutePause:
         SetDeviceState(DeviceStatePaused);
         SetState(StatePaused);
         break;
      case EventExecuteRestart:
         SetDeviceState(DeviceStatePlaying);
         SetState(StatePlaying);
         break;
      case EventEOF:
         break;
      case EventPlaybackEnd:
         {
            if(m_pdecoder != NULL)
            {
               m_pdecoder->DecoderSeekBegin();
               SetDecoderState(DecoderStateOpened);
            }
            SetState(state_initial);
            SetDeviceState(DeviceStateInitial);
            m_estate = state_initial;
            if(m_commandlistStopOpen.get_count() > 0)
            {
               player_command command = m_commandlistStopOpen.remove_head();
               ExecuteCommand(command);
               m_commandlistStopOpen.remove_all();
            }
         }
         break;
      case EventStopped:
         {
            if(m_pdecoder != NULL)
            {
               SetDecoderState(DecoderStateOpened);
               m_pdecoder->DecoderSeekBegin();
            }
            SetState(state_initial);
            SetDeviceState(DeviceStateInitial);
            if(m_commandlistStopOpen.get_count() > 0)
            {
               player_command command = m_commandlistStopOpen.remove_head();
               ExecuteCommand(command);
               m_commandlistStopOpen.remove_all();
            }
         }
         break;
      case EventCloseDevice:
         SetDeviceState(DeviceStateInitial);
         break;
      case EventCloseDecoder:
         SetDecoderState(DecoderStateInitial);
         break;

      }

      if(m_hwndCallback != NULL)
      {
         m_hwndCallback->PostMessage(WM_APP + 119, (WPARAM) eevent, 0);
      }

   }
   void player::SetDeviceState(EDeviceState estate)
   {
      m_edevicestate = estate;
   }

   void player::SetDecoderState(EDecoderState estate)
   {
      m_edecoderstate = estate;
   }

   void player::SetState(e_state estate)
   {
      m_estate = estate;
   }


   player::EDeviceState player::GetDeviceState()
   {
      return m_edevicestate;
   }

   player::EDecoderState player::GetDecoderState()
   {
      return m_edecoderstate;
   }

   player * player::BeginThread(::ca::application * papp)
   {
      return AfxBeginThread < player > (papp, THREAD_PRIORITY_HIGHEST);
   }

   void player::SetCallback(::user::interaction * hwnd)
   {
      m_hwndCallback = hwnd;
   }

   bool player::ExecuteIsPaused()
   {
      return m_estate == StatePaused;
   }

   void player::_Stop()
   {
      if(IsPlaying())
      {
         m_eventStopped.ResetEvent();
         OnEvent(EventStop);
         m_eventStopped.wait(seconds(10));
         m_pdecoder->DecoderSeekBegin();
      }
   }



   /*UINT AFX_CDECL player::ThreadProcBuffer(LPVOID lpparameter)
   {
      player * pplayer = (player *) lpparameter;

      while(true)
      {
         pplayer->m_evOutBufferDone.lock();
         pplayer->m_evPreBufferDone.lock();
         pplayer->PostThreadMessage(MessageKickBufferOut, 0, 0);
      }

   }*/

   bool player::IsDevocalized()
   {
      return false;
   }

   void player::Devocalize(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
   }

   void player::FadeOutAndStop()
   {
      if(m_estate != StatePlaying)
         return;
      OnEvent(EventFadeOutAndStop);
//      audWaveEffectCrescendo * pfadeout = new audWaveEffectCrescendo;

      /*pfadeout->m_bEnd = true;
      pfadeout->m_bSustain = true;
      pfadeout->m_bTriggerEnd = true;
      pfadeout->SetLengthMillis(5000 , m_pwaveout->GetBuffer().m_waveformatexOut.nSamplesPerSec);
      //pfadeout->m_iLength = 5000 * m_pwaveout->GetBuffer().m_waveformatexOut.nSamplesPerSec / 1000;
      pfadeout->SetFinalScale(0, (short) pfadeout->m_iLength);
      pfadeout->Initialize();
      m_pwaveout->m_pprebuffer->m_pstreameffectOut = pfadeout;
      //single_lock sl(& m_pwaveout->m_csPreBuffer, TRUE);
      m_pwaveout->m_pprebuffer->ClearBuffer();*/
   }

   void player::FillTitleInfo(
      stringa &wstraFormat,
      string2a & wstr2aTitle)
   {
      if(m_pdecoder == NULL)
         return;

      string strAttr;

      string str;
      string wstrAttr;
      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeTitle, strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("%0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeArtist, strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("Performer: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeAlbum, strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("Album: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeComposer, strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("Composer: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeYear,strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("Year: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }
   }



   uint64_t player::get_pts()
   {
      if(GetWavePlayer()->IsPlaying())
      {
         return GetWavePlayer()->GetWaveOut()->GetPositionMillisForSynch();
      }
      else if(m_bPlay && m_pdecoder->m_bDraw)
      {
         if((UINT) m_pdecoder->m_iFrameDelayTolerance > (::GetTickCount() - m_pdecoder->m_dwStartTime))
            return 0;
         else
            return ::GetTickCount() - m_pdecoder->m_dwStartTime - m_pdecoder->m_iFrameDelayTolerance;
      }
      else
      {
         return 0;
      }
   }

   void player::layout()
   {

      if(m_sizeVideo.area() <= 0)
         return;

      double dx = (double) m_rectClient.width()  / (double) m_sizeVideo.cx;
      double dy = (double) m_rectClient.height() / (double) m_sizeVideo.cy;

      double d = min(dx, dy);

      m_sizeView.cx = (long) (d * m_sizeVideo.cx);
      m_sizeView.cy = (long) (d * m_sizeVideo.cy);

      for(int i = 0; i < m_scaleda.get_size(); i++)
      {
         m_scaleda[i] = false;
      }


   }


} // namespace verisimplevideo
