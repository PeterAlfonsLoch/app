#include "StdAfx.h"
#include "WaveEffectCrescendo.h"

audWavePlayer::audWavePlayer(::ca::application * papp) :
   ca(papp),
   thread(papp), 
   m_decoderset(papp), 
   m_decodersetex1(papp)
{
   m_pdecoder = NULL;
   m_pwaveout = NULL;
   m_hwndCallback = NULL;
   m_estate = state_initial;
}

audWavePlayer::~audWavePlayer()
{

}

void audWavePlayer::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(audMessageCommand, pinterface, this, &audWavePlayer::OnaudCommandMessage);
}

bool audWavePlayer::DecoderOpen(audWavePlayerCommand & command)
{
   string strDecoder;
   if(command.GetCommand() == audCommandOpenFile)
   {
      DecoderClose();
      m_pdecoder = m_decodersetex1.GetNewDecoder(NULL, command.GetOpenFile(), command.m_bSeekable);
      m_iOutBufferSampleCount =  48 * 1024;
   }
   else
   {
      switch(command.GetCommand())
      {
      case audCommandOpenAiffFile:
         //m_pdecoder = new _vmsaiffdec::decoder();
         return false;
         break;
      case audCommandOpenCdaFile:
         {
            strDecoder = "audio_decode_cd.dll";
         }
         break;
      case audCommandOpenMp3File:
      case audCommandOpenRtpFile:
         {
            strDecoder = "audio_decode_libmpg123.dll";
         }
         break;
      case audCommandOpenVqfFile:
         //m_pdecoder = new _vmstwinvqdec::decoder();
         return false;
         break;
      case audCommandOpenWmFile:
         {
            strDecoder = "audio_decode_window_media.dll";
         }
         break;
      case audCommandOpenWavFile:
         {
            strDecoder = "audio_decode_wave.dll";
         }
         break;
      default:
         return false;
         break;
      }
      m_iOutBufferSampleCount =  48 * 1024;

      audio_decode::decoder_plugin * pplugin = m_decoderset.LoadPlugin(strDecoder);
      if(pplugin == NULL)
         return false;

      DecoderClose();
      m_pdecoder = pplugin->NewDecoder();
      if(m_pdecoder != NULL)
      {
         if(command.GetCommand() == audCommandOpenRtpFile)
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


void audWavePlayer::DecoderInitialize(ex1::file *pfile)
{
   UNREFERENCED_PARAMETER(pfile);
   ASSERT(DecoderIsActive());
   //spfile->seek_to_begin();
   //m_pdecoder->DecoderInitialize(pfile);
   m_pwaveout->SetDecoder(m_pdecoder);
}

bool audWavePlayer::DecoderIsActive()
{
   return m_pdecoder != NULL;
}

void audWavePlayer::DecoderClose()
{
   if(m_pdecoder != NULL)
   {
      delete m_pdecoder;
      m_pdecoder = NULL;
   }
}

void audWavePlayer::DecoderRun()
{
//   m_pdecoder->DecoderRun();
}


bool audWavePlayer::initialize_instance()
{
   CoInitialize(NULL);

   m_pwaveout = AfxBeginThread < audWaveOut >(get_app(), THREAD_PRIORITY_ABOVE_NORMAL);
   if(m_pwaveout == NULL)
      return false;

   m_pwaveout->m_pplayer = this;

   return true;
}

int audWavePlayer::exit_instance()
{
   CoUninitialize();
   if(m_pwaveout != NULL)
   {
      CEvent ev;
      m_pwaveout->AttachEndEvent(&ev);
      m_pwaveout->PostThreadMessage(WM_QUIT, 0, 0);
      ev.Lock();
   }
   
   return thread::exit_instance();
}



void audWavePlayer::ExecuteCommand(audWavePlayerCommand & command)
{
   switch(command.GetCommand())
   {
   case audCommandExecuteStop:
   case audCommandCloseDevice:
      {
         audCommandMessageProcedure(command);
      }
      break;
   default:
      {
         PostThreadMessage(
            audMessageCommand,
            (WPARAM) command.GetCommand(),
            (LPARAM) (new audWavePlayerCommand(command)));
      }
   }

}

audWavePlayerCommand::audWavePlayerCommand()
{
   m_pbResult = NULL;
   m_bSeekable = true;
}

audWavePlayerCommand::audWavePlayerCommand(const audWavePlayerCommand & command)
{
   operator =(command);
}

audWavePlayerCommand & audWavePlayerCommand::operator =(const audWavePlayerCommand & command)
{
   SetCommand(command.GetCommand());
   SetOpenFile(command.GetOpenFile());
   m_bResult      = command.m_bResult;
   m_pbResult     = command.m_pbResult;
   m_evptra       = command.m_evptra;
   m_bSeekable    = command.m_bSeekable;
   m_position     = command.m_position;
   return *this;

}

EaudCommand audWavePlayerCommand::GetCommand() const
{
   return m_ecommand;
}

void audWavePlayerCommand::SetCommand(EaudCommand ecommand)
{
   m_ecommand = ecommand;
}

ex1::file * audWavePlayerCommand::GetOpenFile() const
{
   return m_pfileOpen;
}

void audWavePlayerCommand::SetOpenFile(ex1::file *pfile)
{
   m_pfileOpen = pfile;
}

void audWavePlayerCommand::OpenRtpFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenRtpFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenMp3File(ex1::file * pfile)
{
   SetCommand(audCommandOpenMp3File);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenAiffFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenAiffFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenCdaFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenCdaFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenVqfFile(ex1::file *pfile)
{
   SetCommand(audCommandOpenVqfFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenWmFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenWmFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenWavFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenWavFile);
   SetOpenFile(pfile);
}

void audWavePlayerCommand::OpenFile(ex1::file * pfile, bool bSeekable)
{
   SetCommand(audCommandOpenFile);
   SetOpenFile(pfile);
   m_bSeekable = bSeekable;
}

void audWavePlayerCommand::Play(const imedia::position & position)
{
   SetCommand(audCommandExecutePlay);
   m_position = position;
}

void audWavePlayer::OnaudCommandMessage(gen::signal_object * pobj)
   //WPARAM wparam, // audCommand enumeration
   //LPARAM lparam  // audCommand object pointer
   //)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   audWavePlayerCommand * pcommand = (audWavePlayerCommand *) pbase->m_lparam;
   audCommandMessageProcedure(*pcommand);
   if(pcommand->m_pbResult != NULL)
   {
      *pcommand->m_pbResult = pcommand->m_bResult;
   }
   delete pcommand;
}

bool audWavePlayer::audCommandMessageProcedure(audWavePlayerCommand &command)
{
//   bool bSetEvents = true;
   command.m_bResult = true;  
   EaudCommand ecommand = command.GetCommand();
   switch(ecommand)
   {
   case audCommandOpenCdaFile:
   case audCommandOpenMp3File:
   case audCommandOpenRtpFile:
   case audCommandOpenAiffFile:
   case audCommandOpenVqfFile:
   case audCommandOpenWmFile:
   case audCommandOpenWavFile:
   case audCommandOpenFile:
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
   case audCommandExecutePlay:
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
            if(0 != m_pwaveout->OpenEx(
                  this, 
                  16,
                  m_iOutBufferSampleCount,
                  m_pdecoder->DecoderGetSamplesPerSecond(),
                  m_pdecoder->DecoderGetChannelCount(),
                  m_pdecoder->DecoderGetBitsPerSample()))
            {
               System.simple_message_box_timeout(NULL, "Could not play the spfile->", 5000, MB_OK | MB_ICONEXCLAMATION);
               command.m_bResult = false;
               break;
            }
            OnEvent(EventOpenDevice);
            //m_pdecoder->DecoderSeekBegin();
            m_pwaveout->Start(command.m_position);
            OnEvent(EventPlay);
         }
         else
         {
            command.m_bResult = false;
            break;
         }
      }
      break;
   case audCommandExecuteStop:
      {
         FadeOutAndStop();
      }
      break;
   case audCommandExecutePause:
      {
         if(m_commandlistStopOpen.get_count() > 0)
         {
            return false;
         }
         m_pwaveout->Pause();
      }
      break;
   case audCommandExecuteRestart:
      {
         if(m_commandlistStopOpen.get_count() > 0)
         {
            return false;
         }
         m_pwaveout->Restart();
      }
      break;
   case audCommandCloseDevice:
      {
         m_pwaveout->close();
         OnEvent(EventCloseDevice);
      }
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   command.SetEvents();
   return command.m_bResult;
}


void audWavePlayer::AttachEndEvent(CEvent *pevent)
{
   if(m_pwaveout)
   {
      m_pwaveout->AttachEndEvent(pevent);
   }
}

void audWavePlayerCommand::AttachEvent(CEvent *pevent)
{
   m_evptra.add(pevent);
}
void audWavePlayerCommand::SetEvents()
{
   for(int i = 0;  i < m_evptra.get_size(); i++)
   {
      m_evptra[i]->SetEvent();
   }
}

void audWavePlayerCommand::Stop()
{
   SetCommand(audCommandExecuteStop);
}

void audWavePlayerCommand::CloseDevice()
{
   SetCommand(audCommandCloseDevice);
}

void audWavePlayerCommand::OpenDevice()
{
   SetCommand(audCommandOpenDevice);
}

void audWavePlayer::ExecuteStop()
{
   m_pwaveout->Stop();
//   m_pdecoder->DecoderStop();
}

bool audWavePlayer::DeviceIsOpened()
{
   return GetDeviceState() == DeviceStateOpened;
}

bool audWavePlayer::DecoderIsOpened()
{
   return GetDecoderState() == DecoderStateOpened;
}

bool audWavePlayer::IsPlaying()
{
   return GetDeviceState() == DeviceStatePlaying
      || GetDeviceState() == DeviceStateStopping
      || m_estate == StateFadingOutToStop;

}

bool audWavePlayer::GetPlayEnable()
{
   return GetDecoderState() == DecoderStateOpened
      && !IsPlaying();
}

bool audWavePlayer::GetStopEnable()
{
   return IsPlaying();
}




void audWavePlayer::OnEvent(e_event eevent)
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
         audWavePlayerCommand command = m_commandlistOpenPlay.remove_head();
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
         m_pwaveout->close();
         if(m_pdecoder != NULL)
         {
            SetDecoderState(DecoderStateOpened);
         }
         SetState(state_initial);
         SetDeviceState(DeviceStateInitial);
         m_estate = state_initial;
         if(m_commandlistStopOpen.get_count() > 0)
         {
            audWavePlayerCommand command = m_commandlistStopOpen.remove_head();
            ExecuteCommand(command);
            m_commandlistStopOpen.remove_all();
         }
      }
      break;
   case EventStopped:
      {
         m_pwaveout->close();
         if(m_pdecoder != NULL)
         {
            SetDecoderState(DecoderStateOpened);
            m_pdecoder->DecoderSeekBegin();
         }
         SetState(state_initial);
         SetDeviceState(DeviceStateInitial);
         if(m_commandlistStopOpen.get_count() > 0)
         {
            audWavePlayerCommand command = m_commandlistStopOpen.remove_head();
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
void audWavePlayer::SetDeviceState(EDeviceState estate)
{
   m_edevicestate = estate;
}

void audWavePlayer::SetDecoderState(EDecoderState estate)
{
   m_edecoderstate = estate;
}

void audWavePlayer::SetState(e_state estate)
{
   m_estate = estate;
}


audWavePlayer::EDeviceState audWavePlayer::GetDeviceState()
{
   return m_edevicestate;
}

audWavePlayer::EDecoderState audWavePlayer::GetDecoderState()
{
   return m_edecoderstate;
}

audWavePlayer * audWavePlayer::BeginThread(::ca::application * papp)
{
   return AfxBeginThread < audWavePlayer > (papp, THREAD_PRIORITY_HIGHEST);
}

audWaveOut * audWavePlayer::GetWaveOut()
{
   return m_pwaveout;
}

void audWavePlayer::SetCallback(::user::interaction * hwnd)
{
   m_hwndCallback = hwnd;
}

bool audWavePlayer::ExecuteIsPaused()
{
   return m_estate == StatePaused;
}

void audWavePlayer::_Stop()
{
   if(IsPlaying())
   {
      m_eventStopped.ResetEvent();
      OnEvent(EventStop);
      m_pwaveout->Stop();
      m_eventStopped.Lock(10000);
      m_pdecoder->DecoderSeekBegin();
   }
}



/*UINT AFX_CDECL audWavePlayer::ThreadProcBuffer(LPVOID lpparameter)
{
   audWavePlayer * pplayer = (audWavePlayer *) lpparameter;

   while(true)
   {
      pplayer->m_evOutBufferDone.Lock();
      pplayer->m_evPreBufferDone.Lock();
      pplayer->PostThreadMessage(MessageKickBufferOut, 0, 0);
   }

}*/

bool audWavePlayer::IsDevocalized()
{
   return m_pwaveout->m_pprebuffer->IsDevocalized();
}

void audWavePlayer::Devocalize(bool bSet)
{
   m_pwaveout->m_pprebuffer->Devocalize(bSet);
}

void audWavePlayer::FadeOutAndStop()
{
   if(m_estate != StatePlaying)
      return;
   OnEvent(EventFadeOutAndStop);
   audWaveEffectCrescendo * pfadeout = new audWaveEffectCrescendo;

   pfadeout->m_bEnd = true;
   pfadeout->m_bSustain = true;
   pfadeout->m_bTriggerEnd = true;
   pfadeout->SetLengthMillis(5000 , m_pwaveout->GetBuffer().m_waveformatexOut.nSamplesPerSec);
   //pfadeout->m_iLength = 5000 * m_pwaveout->GetBuffer().m_waveformatexOut.nSamplesPerSec / 1000;
   pfadeout->SetFinalScale(0, (short) pfadeout->m_iLength);
   pfadeout->Initialize();
   m_pwaveout->m_pprebuffer->m_pstreameffectOut = pfadeout;
   //CSingleLock sl(& m_pwaveout->m_csPreBuffer, TRUE);
   m_pwaveout->m_pprebuffer->ClearBuffer();
}

void audWavePlayer::FillTitleInfo(
   stringa &wstraFormat, 
   string2a & wstr2aTitle)
{
   if(m_pdecoder == NULL)
      return;

   string strAttr;

   string str;
   string wstrAttr;
   if(m_pdecoder->DecoderGetAttribute(audio_decode::AttributeTitle, strAttr))
   {
      strAttr.ReleaseBuffer();
      wstrAttr = strAttr;
      wstraFormat.add("%0");
      wstr2aTitle.add_new();
      wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
   }

   if(m_pdecoder->DecoderGetAttribute(audio_decode::AttributeArtist, strAttr))
   {
      strAttr.ReleaseBuffer();
      wstrAttr = strAttr;
      wstraFormat.add("Performer: %0");
      wstr2aTitle.add_new();
      wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
   }

   if(m_pdecoder->DecoderGetAttribute(audio_decode::AttributeAlbum, strAttr))
   {
      strAttr.ReleaseBuffer();
      wstrAttr = strAttr;
      wstraFormat.add(L"Album: %0");
      wstr2aTitle.add_new();
      wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
   }

   if(m_pdecoder->DecoderGetAttribute(audio_decode::AttributeComposer, strAttr))
   {
      strAttr.ReleaseBuffer();
      wstrAttr = strAttr;
      wstraFormat.add(L"Composer: %0");
      wstr2aTitle.add_new();
      wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
   }

   if(m_pdecoder->DecoderGetAttribute(audio_decode::AttributeYear,strAttr))
   {
      strAttr.ReleaseBuffer();
      wstrAttr = strAttr;
      wstraFormat.add(L"Year: %0");
      wstr2aTitle.add_new();
      wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
   }
}










