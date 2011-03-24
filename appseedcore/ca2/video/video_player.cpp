#include "StdAfx.h"

namespace video
{

   player::player(::ca::application * papp) :
      ca(papp),
      ::radix::thread(papp),
      m_decoderset(papp), 
      m_decodersetex1(papp),
      m_play(papp),
      m_decode(papp)
   {
      m_play.m_pplayer     = this;
      m_decode.m_pplayer   = this;
      m_pdecoder           = NULL;
      m_hwndCallback       = NULL;
      m_estate             = state_initial;
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
      CSingleLock sl(&m_mutexBuffer, TRUE);
      ::ca::dib & dib = m_pdecoder->m_diba[m_pdecoder->m_iPlayDib];
      dib.to(pdc, null_point(), dib.size());
   }



   bool player::step()
   {
      CSingleLock sl(&m_mutexBuffer, TRUE);
      if(!m_pdecoder->step())
      {
         m_bPlay = false;
         return false;
      }
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
      while(m_pplayer->m_bPlay && m_pplayer->m_pdecoder->m_iLastDib < 0)
      {
         while(m_pplayer->decode() && m_pplayer->m_bPlay);
         Sleep(10);
      }
      return 0;
   }


   void player::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(message_command, pinterface, this, &player::OnCommandMessage);
   }

   bool player::DecoderOpen(player_command & command)
   {
      string strDecoder;
      if(command.GetCommand() == command_open_file)
      {
         m_pdecoder = m_decodersetex1.GetNewDecoder(NULL, command.GetOpenFile());
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
            FadeOutAndStop();
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


   void player::AttachEndEvent(CEvent * pevent)
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
         m_eventStopped.Lock(10000);
         m_pdecoder->DecoderSeekBegin();
      }
   }



   /*UINT AFX_CDECL player::ThreadProcBuffer(LPVOID lpparameter)
   {
      player * pplayer = (player *) lpparameter;

      while(true)
      {
         pplayer->m_evOutBufferDone.Lock();
         pplayer->m_evPreBufferDone.Lock();
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
      //CSingleLock sl(& m_pwaveout->m_csPreBuffer, TRUE);
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
         wstraFormat.add(L"Album: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeComposer, strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add(L"Composer: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if(m_pdecoder->DecoderGetAttribute(video_decode::AttributeYear,strAttr))
      {
         strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add(L"Year: %0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }
   }











} // namespace verisimplevideo
