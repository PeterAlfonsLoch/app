#include "StdAfx.h"
#include "vmsmusresource.h"

MidiPlayer::MidiPlayer(::ca::application * papp)
: thread(papp)
{
   m_psequencethread = 
      AfxBeginThread < MidiSequenceThread >(
         papp,
         THREAD_PRIORITY_NORMAL,
         0,
         CREATE_SUSPENDED);
   m_puie               = NULL;
}

MidiPlayer::~MidiPlayer()
{
   
}

bool MidiPlayer::initialize_instance()
{
   
   m_psequencethread->ResumeThread();

   TRACE("MidiPlayer::initialize_instance %X\n", get_os_int());
   SetMainWnd(NULL);
   ASSERT(GetMainWnd() == NULL);

   SetThreadPriority(THREAD_PRIORITY_NORMAL);
   
   m_evInitialized.SetEvent();

   return true;
}

int MidiPlayer::exit_instance()
{
   // TODO:  perform any per-thread cleanup here
   //   if(!GetSequence().IsNull())
   //   {
   //      delete GetSequence();
   //   }
   //    if(m_pmidicallbackdata != NULL)
   //  {
   //    delete m_pmidicallbackdata;
   ///  m_pmidicallbackdata = NULL;
   //}
   return thread::exit_instance();
}

void MidiPlayer::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(MessageNotifyEvent, pinterface, this, &MidiPlayer::OnNotifyEvent);
   IGUI_WIN_MSG_LINK(MM_MOM_DONE, pinterface, this, &MidiPlayer::OnMultimediaMidiOutputMessageDone);
   IGUI_WIN_MSG_LINK(MM_MOM_POSITIONCB, pinterface, this, &MidiPlayer::OnMultimediaMidiOutputMessagePositionCB);
   IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &MidiPlayer::OnUserMessage);
}

bool MidiPlayer::Play(imedia::position tkStart, DWORD dwEllapse)
{
   MidiPlayerCommand * pcommand = MidiPlayerCommand::CreateObject();

   pcommand->m_ecommand = MidiPlayerCommandPlay;
   pcommand->m_dwEllapse = dwEllapse;
   pcommand->m_flags.signalize(MidiPlayerCommand::flag_ticks);
   pcommand->m_ticks = tkStart;

   m_psequencethread->ExecuteCommand(pcommand);
   
   bool bFinished = pcommand->Lock();
   
   pcommand->Release();

   return bFinished;
}

bool MidiPlayer::Play(double dRate, DWORD dwEllapse)
{
   MidiPlayerCommand * pcommand = MidiPlayerCommand::CreateObject();

   pcommand->m_ecommand = MidiPlayerCommandPlay;
   pcommand->m_dwEllapse = dwEllapse;
   pcommand->m_flags.signalize(MidiPlayerCommand::flag_dRate);
   pcommand->m_dRate = dRate;

   m_psequencethread->ExecuteCommand(pcommand);
   
   bool bFinished = pcommand->Lock();
   
   pcommand->Release();

   return bFinished;
}
imedia::position MidiPlayer::RateToTicks(double dRate)
{
   ASSERT(dRate >= 0.0);
   ASSERT(dRate <= 1.0);
   return (imedia::position) (int) (GetSequence().m_tkLength * dRate);
}



bool MidiPlayer::IsPlaying()
{
   ASSERT(!GetSequence().IsNull());
   return (bool) GetSequence().IsPlaying();
   
}

bool MidiPlayer::ExecuteCommand(
   EMidiPlayerCommand ecommand,
   DWORD dwEllapse)
{
   MidiPlayerCommand * pcommand = MidiPlayerCommand::CreateObject();

   pcommand->m_ecommand = ecommand;
   pcommand->m_dwEllapse = dwEllapse;

   m_psequencethread->ExecuteCommand(pcommand);
   
   bool bFinished = pcommand->Lock();
   
   pcommand->Release();

   return true;
}


void MidiPlayer::CloseFile()
{
   MMRESULT            mmrc;
   if(MMSYSERR_NOERROR != (mmrc = GetSequence().CloseFile()) &&
      mmrc != MCIERR_UNSUPPORTED_FUNCTION)
   {
      throw new midi_exception(mmrc, MIDIPLAYERCLOSEEXCEPTION);
   }
}

void MidiPlayer::Pause()
{
   if (GetSequence().GetState() == ::mus::midi::sequence::StatusPaused)
   {
      GetSequence().Restart();
   }
   else
   {
      GetSequence().Pause();
   }
   
}

void MidiPlayer::SetPosition(double dRate)
{
   if (::mus::midi::sequence::StatusPlaying != GetSequence().GetState() &&
      ::mus::midi::sequence::StatusStopping != GetSequence().GetState() &&
      ::mus::midi::sequence::StatusOpened != GetSequence().GetState())
      return;
   
   if(GetSequence().IsPlaying())
   {
      ::mus::midi::sequence::PlayerLink & link = GetSequence().GetPlayerLink();
      link.ModifyFlag(
         ::mus::midi::sequence::FlagSettingPos,
         ::mus::midi::sequence::FlagNull);
      link.m_tkRestart = RateToTicks(dRate);
      GetSequence().Stop();
   }
   
}

void MidiPlayer::OnMmsgDone(::mus::midi::sequence * pSeq)
{
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(FALSE);
   ASSERT(pSeq == &GetSequence());
   if(pSeq->IsSettingPosition())
   {
      GetSequence().SetSettingPositionFlag(FALSE);
      try
      {
//         PrerollAndWait(m_dNextPositionRate);
      }
      catch(midi_exception *pe)
      {
         SendMmsgDone(pSeq, NULL);
         pe->Delete();
         return;
      }
      GetSequence().Start();
   }
   else
   {
   }
   
}

void MidiPlayer::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   ASSERT(GetMainWnd() == NULL);
   //   if(pMsg->message == MM_MOM_DONE ||
   //      pMsg->message == MM_MOM_POSITIONCB ||
   //      pMsg->message == MM_MOM_OPEN ||
   //      pMsg->message == MM_MOM_OPEN)
   //   {
   //      OnMidiOutMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
   //      return TRUE;
   //   }
   if(pbase->m_hwnd == NULL)
   {
      switch(pbase->m_uiMessage)
      {
      case WM_USER + 100:
         {
            LPDOUBLESTRUCT lpds = (LPDOUBLESTRUCT) pbase->m_wparam;
            SetPosition(lpds->d);
            delete lpds;
         }
         return;
      }
   }
   if(pbase->m_uiMessage == MMSG_DONE)
   {
      OnMmsgDone((::mus::midi::sequence *) pbase->m_wparam);
      pbase->m_bRet = true;
      return;
   }
   else if(pbase->m_uiMessage == WM_USER)
   {
//      OnUserMessage(pMsg->wParam, pMsg->lParam);
   }
   return thread::pre_translate_message(pobj);
}

void MidiPlayer::SaveFile(const char * lpszPathName)
{
   MMRESULT            mmrc;
   if((mmrc = GetSequence().SaveFile(lpszPathName)) != 
      MMSYSERR_NOERROR)
   {
      throw new midi_exception(mmrc, MIDIPLAYERSAVEEXCEPTION);
   }
   
}
/*
void MidiPlayer::OnMidiPlaybackEnd(
WPARAM wParam, LPARAM lParam)
{
::mus::midi::sequence * pSeq = (::mus::midi::sequence *) wParam;
LPMIDIHDR lpmh = (LPMIDIHDR) lParam;

  ASSERT(pSeq == GetSequence());
  
    m_eventPlaybackEnd.SetEvent();
    //    GetSequence().OnMidiPlaybackEnd(lpmh, m_pmidicallbackdata);
    GetSequence().OnEvent(::mus::midi::sequence::EventMidiPlaybackEnd);
}*/

//void MidiPlayer::OnMidiSequenceEvent(gen::signal_object * pobj)
//{
/*   ::mus::midi::sequence::Event * pevent = (::mus::midi::sequence::Event *) lparam;
   ::mus::midi::sequence * pseq = (::mus::midi::sequence *) pevent->m_psequence;

   if(pevent->m_eevent == ::mus::midi::sequence::EventMidiPlaybackEnd)
   {
      m_eventPlaybackEnd.SetEvent();
   }
   
   pseq->OnEvent(pevent->m_eevent);
   
   switch(pevent->m_eevent)
   {
   case ::mus::midi::sequence::EventStopped:
      {
         ::mus::midi::sequence::PlayerLink & link = GetSequence().GetPlayerLink();
         if(link.TestFlag(
            ::mus::midi::sequence::FlagStop))
         {
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagStop);
            PostNotifyEvent(::mus::midi::player::NotifyEventStop);
         }
         else if(link.TestFlag(
            ::mus::midi::sequence::FlagTempoChange))
         {
            PrerollAndWait(link.m_tkRestart);
            GetSequence().SetTempoChangeFlag(false);
            GetSequence().Start();
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagTempoChange);
         }
         else if(link.TestFlag(
            ::mus::midi::sequence::FlagSettingPos))
         {
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagSettingPos);
            try
            {
               PrerollAndWait(link.m_tkRestart);
            }
            catch(midi_exception *pe)
            {
               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence().Start();
            PostNotifyEvent(::mus::midi::player::NotifyEventPositionSet);
         }
         else if(link.TestFlag(
            ::mus::midi::sequence::FlagMidiOutDeviceChange))
         {
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagMidiOutDeviceChange);
            try
            {
               PrerollAndWait(link.m_tkRestart);
            }
            catch(midi_exception *pe)
            {
               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence().Start();
            /*::mus::midi::player::NotifyEvent data;
            data.m_pplayer = this;
            data.m_enotifyevent = ::mus::midi::player::NotifyEventPositionSet;
            SendMessage(
            m_hWnd,
            MIDIPLAYERMESSAGE_NOTIFYEVENT,
            (WPARAM) &data,
            0);      */
            
         /*}
         else if(link.TestFlag(
            ::mus::midi::sequence::FlagStopAndRestart))
         {
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagStopAndRestart);
            try
            {
               PrerollAndWait(link.m_tkRestart);
            }
            catch(midi_exception *pe)
            {
               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence().Start();
            //PostNotifyEvent(::mus::midi::player::NotifyEventPositionSet);
         }
         
      }
      break;
   case ::mus::midi::sequence::EventSpecialModeV001End:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventGenericMmsgDone);
      }
      break;
   case ::mus::midi::sequence::EventMidiPlaybackEnd:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventPlaybackEnd);
      }
      break;
      
   }
   delete pevent;*/
//}


void MidiPlayer::OnUserMessage(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(pbase->m_wparam == 3377)
   {
      m_puie->SendMessage(WM_USER, pbase->m_wparam, pbase->m_lparam);
   }
   
}


void MidiPlayer::PostGMReset()
{
   m_psequencethread->PostGMReset();
}

void MidiPlayer::PostTempoChange()
{
   m_psequencethread->PostTempoChange();
}

void MidiPlayer::SendTempoChange()
{
   m_psequencethread->SendTempoChange();
}


VMSRESULT MidiPlayer::Initialize(thread * pthread)
{
   UNREFERENCED_PARAMETER(pthread);
   return VMSR_SUCCESS;
}

//void MidiPlayer::SetView(CXfplayerView *pview)
//{
//    m_pView = pview;
//}

VMSRESULT MidiPlayer::SetInterface(MidiPlayerInterface * pinterface)
{
   m_pinterface = pinterface;
   GetSequence().m_pthread   = m_psequencethread;
   GetSequence().m_midicallbackdata.m_psequence = &GetSequence(); 
   m_psequencethread->m_psequence = &GetSequence(); 
   m_psequencethread->m_pplayer = this; 
   PostNotifyEvent(::mus::midi::player::NotifyEventSetSequence);
   return VMSR_SUCCESS;
}


bool MidiPlayer::SetMidiOutDevice(UINT uiDevice)
{
   UNREFERENCED_PARAMETER(uiDevice);
   OnMidiOutDeviceChange();
   return true;
}



bool MidiPlayer::SetTempoShift(int iTempoShift)
{
//   if(IsPlaying())
   {/*
      GetSequence().SetTempoChangeFlag();
      ::mus::midi::sequence::PlayerLink & link = GetSequence().GetPlayerLink();
      link.ModifyFlag(
         ::mus::midi::sequence::FlagTempoChange,
         ::mus::midi::sequence::FlagNull);
      imedia::position tk = GetSequence().GetPositionTicks();
      GetSequence().m_evMmsgDone.ResetEvent();
      link.m_tkRestart = tk + GetSequence().m_tkBase;
      //m_bChangingTempo = true;
      GetSequence().Stop();
      //GetSequence().m_evMmsgDone.Lock();
      */
   bool bPlay = IsPlaying();
   imedia::position ticks = 0;
   if(bPlay)
   {
      ticks = GetSequence().GetPositionTicks();
      GetSequence().Stop();
   }
   if(!GetSequence().SetTempoShift(iTempoShift))
      return false;
   if(bPlay)
   {
      GetSequence().m_pthread->PrerollAndWait(ticks);
      GetSequence().Start();
   }

   }
   return true;
}


void MidiPlayer::PostNotifyEvent(::mus::midi::player::ENotifyEvent eevent)
{
   if(m_puie != NULL)
   {
      ::mus::midi::player::NotifyEvent * pdata = new ::mus::midi::player::NotifyEvent;
      pdata->m_pplayer = this;
      pdata->m_enotifyevent = eevent;
      m_puie->PostMessage(MessageNotifyEvent, 0 , (LPARAM) pdata);      
   }
}

void MidiPlayer::SendMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd)
{
   if(m_puie != NULL)
   {
      m_puie->SendMessage(MMSG_DONE, (WPARAM) pSeq, (LPARAM) lpmdd);      
   }
   
}

UINT MidiPlayer::GetMidiOutDevice()
{
   midi_central * pcentral = m_pinterface->m_pcentral;
   return pcentral->GetMidiOutDevice();
}

void MidiPlayer::SetCallbackWindow(::user::interaction * puie)
{
   m_puie = puie;
}

void MidiPlayer::OnAttributeChange(mus::EMidiCentralAttribute eattribute)
{
   switch(eattribute)
   {
   case mus::MidiCentralAttributeMidiOutDevice:
      OnMidiOutDeviceChange();
      break;
   }
   
}

void MidiPlayer::OnMidiOutDeviceChange()
{
   GetSequence().SetMidiOutDevice(GetMidiOutDevice());
   if(GetSequence().IsPlaying())
   {
      imedia::position tkPosition = 0;
      GetSequence().get_time(tkPosition);
      ::mus::midi::sequence::PlayerLink & link = GetSequence().GetPlayerLink();
      link.ModifyFlag(
         ::mus::midi::sequence::FlagTempoChange,
         ::mus::midi::sequence::FlagNull);
      link.m_tkRestart = tkPosition;
      GetSequence().Stop();
   }
   
}


void MidiPlayer::OnMultimediaMidiOutputMessageDone(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   HMIDISTRM hmidistream = (HMIDISTRM) pbase->m_wparam;
   LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_lparam;
   ASSERT(GetSequence().m_hMidiStream == hmidistream);
   GetSequence().OnDone(hmidistream, lpmidihdr);
}

void MidiPlayer::OnMultimediaMidiOutputMessagePositionCB(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_wparam;
   GetSequence().OnPositionCB(lpmidihdr);
}




void MidiPlayer::OnNotifyEvent(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   ::mus::midi::player::NotifyEvent * pdata = (::mus::midi::player::NotifyEvent *) pbase->m_lparam;
   pdata->m_pplayer = this;
   if(m_puie != NULL)
   {
      m_puie->PostMessage(MessageNotifyEvent, 0 , (LPARAM) pdata);      
   }
   else
   {
      delete pdata;
   }
}

void MidiPlayerCommand::AddRef()
{
   CSingleLock sl(&m_csRefCount, TRUE);
   m_iRefCount++;
}

void MidiPlayerCommand::Release()
{
   CSingleLock sl(&m_csRefCount, TRUE);
   m_iRefCount--;
   if(m_iRefCount <= 0)
   {
      sl.Unlock();
      delete this;
   }
}


MidiPlayerCommand * MidiPlayerCommand::CreateObject()
{
   MidiPlayerCommand * pobject = new MidiPlayerCommand();
   pobject->AddRef();
   return pobject;
}

/*MidiPlayerCommand::MidiPlayerCommand(EMidiPlayerCommand ecommand, DWORD dwEllapse)
{
   m_ecommand = ecommand;
   m_dwEllapse = dwEllapse;
   
}
*/

MidiPlayerCommand::MidiPlayerCommand()
{
   m_iRefCount = 0;
   m_bReady = false;
}

EMidiPlayerCommand MidiPlayerCommand::GetCommand()
{
   return m_ecommand;
}

DWORD MidiPlayerCommand::GetEllapse()
{
   return m_dwEllapse;
}

bool MidiPlayerCommand::Lock()
{
   DWORD dwStart = ::GetTickCount();
   while(!m_bReady && (::GetTickCount() - dwStart) < m_dwEllapse)
   {
      Sleep(84);
   }
   return m_bReady;
}

void MidiPlayerCommand::OnFinish()
{
   m_bReady = true;
}



void MidiPlayer::SendReset()
{
   HMIDIOUT hmidiout = NULL;
   MMRESULT mmrc;
   UINT uDeviceID = 0;
   mmrc = midiOutOpen(&hmidiout, uDeviceID,  NULL, 0, CALLBACK_NULL);
   if(mmrc != MMSYSERR_NOERROR)
      return;
   Sleep(284);
   const unsigned char gmModeOn[] = {
      //        0x00, 0x00, 0x00, 0x00,
      //        0x00, 0x00, 0x00, 0x00,
      //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, MEVT_LONGMSG,
      0xf0, 0x7e, 0x7f, 0x09,
      0x01, 0xf7, 0x00, 0x00};
      //        0x70, 0x01, 0x00, 0x00,
      //      0x00, 0x00, 0x00, 0x00 };
      //      0x09, 0x00, 0x00, MEVT_LONGMSG,
      //      0x43, 0x10, 0x4c,
      //    0x00, 0x00, 0x7e, 0x00,
      //  0xf7, 0x00, 0x00, 0x00,};
   MIDIHDR mh;
   LPMIDIHDR lpmh = &mh;
   lpmh->lpData = (char *) gmModeOn;
   lpmh->dwBufferLength = sizeof(gmModeOn);
   lpmh->dwBytesRecorded = 0;
   lpmh->dwFlags = 0;
   mmrc = midiOutPrepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
   if(mmrc != MMSYSERR_NOERROR)
      goto End;
   lpmh->dwBytesRecorded = sizeof(gmModeOn);
   if(mmrc != MMSYSERR_NOERROR)
      goto End;
   mmrc = midiOutLongMsg( hmidiout, lpmh, sizeof(MIDIHDR));
   Sleep(284);
   mmrc = midiOutUnprepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
   if(mmrc != MMSYSERR_NOERROR)
      goto End;
End:
   midiOutClose( hmidiout);
}

::mus::midi::sequence & MidiPlayer::GetSequence()
{
   return m_pinterface->GetMidiSequence();
}


