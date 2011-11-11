#include "StdAfx.h"
#include "vmsmusresource.h"


midi_sequence_thread::midi_sequence_thread(::ca::application * papp) :
   ca(papp),
   thread(papp)
{
}

midi_sequence_thread::~midi_sequence_thread()
{
}

bool midi_sequence_thread::initialize_instance()
{
   SetThreadPriority(THREAD_PRIORITY_HIGHEST);
   return true;
}

int midi_sequence_thread::exit_instance()
{
   return thread::exit_instance();
}

void midi_sequence_thread::install_message_handling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(MIDIPLAYERMESSAGE_COMMAND, pinterface, this, &midi_sequence_thread::OnCommand);
   IGUI_WIN_MSG_LINK(MIDISEQUENCEMESSAGE_EVENT, pinterface, this, &midi_sequence_thread::OnMidiSequenceEvent);
}

void midi_sequence_thread::Stop(DWORD dwEllapse)
{
   GetSequence()->Stop();
   m_eventStop.wait(millis(dwEllapse));
}

::mus::midi::sequence * midi_sequence_thread::GetSequence()
{
   return m_psequence;
}

BOOL midi_sequence_thread::PostMidiSequenceEvent(
   ::mus::midi::sequence * pseq,
   ::mus::midi::sequence::e_event eevent)
{
   return PostMidiSequenceEvent(
      pseq,
      eevent,
      (LPMIDIHDR) NULL);
}

BOOL midi_sequence_thread::PostMidiSequenceEvent(
   ::mus::midi::sequence * pseq,
   ::mus::midi::sequence::e_event eevent,
   LPMIDIHDR lpmh)
{
   ::mus::midi::sequence::Event * pevent = new ::mus::midi::sequence::Event;
   pevent->m_psequence  = pseq;
   pevent->m_eevent     = eevent;
   pevent->m_lpmh       = lpmh;
   return PostThreadMessage(
      MIDISEQUENCEMESSAGE_EVENT, 
      (WPARAM) pseq, 
      (LPARAM) pevent);
}

void midi_sequence_thread::OnMidiSequenceEvent(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);

   ::mus::midi::sequence::Event * pevent = (::mus::midi::sequence::Event *) pbase->m_lparam;
   ::mus::midi::sequence * pseq = (::mus::midi::sequence *) pevent->m_psequence;

   pseq->OnEvent(pevent);
   
   switch(pevent->m_eevent)
   {
   case ::mus::midi::sequence::EventStopped:
      {
         ::mus::midi::sequence::PlayerLink & link = GetSequence()->GetPlayerLink();
         if(link.TestFlag(::mus::midi::sequence::FlagStop))
         {
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagStop);
            link.OnFinishCommand(MidiPlayerCommandStop);
            PostNotifyEvent(::mus::midi::player::NotifyEventStop);
            
         }
         else if(link.TestFlag(::mus::midi::sequence::FlagTempoChange))
         {
            PrerollAndWait(link.m_tkRestart);
            GetSequence()->SetTempoChangeFlag(false);
            GetSequence()->Start();
            link.ModifyFlag(
               ::mus::midi::sequence::FlagNull,
               ::mus::midi::sequence::FlagTempoChange);
         }
         else if(link.TestFlag(::mus::midi::sequence::FlagSettingPos))
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
//               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence()->Start();
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
//               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence()->Start();
            /*CNotifyEventData data;
            data.m_pplayer = this;
            data.m_enotifyevent = NotifyEventPositionSet;
            SendMessage(
            m_hWnd,
            MIDIPLAYERMESSAGE_NOTIFYEVENT,
            (WPARAM) &data,
            0);      */
            
         }
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
//               SendMmsgDone(pseq, NULL);      
               pe->Delete();
               return;
            }
            GetSequence()->Start();
            //PostNotifyEvent(NotifyEventPositionSet);
         }
         
      }
      break;
   case ::mus::midi::sequence::EventSpecialModeV001End:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventGenericMmsgDone);
      }
      break;
   case ::mus::midi::sequence::EventMidiPlaybackStart:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventPlaybackStart);
      }
      break;
   case ::mus::midi::sequence::EventMidiStreamOut:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventMidiStreamOut);
      }
      break;
   case ::mus::midi::sequence::EventMidiPlaybackEnd:
      {
         PostNotifyEvent(::mus::midi::player::NotifyEventPlaybackEnd);
      }
      break;
      
   }
   delete pevent;
}

void midi_sequence_thread::PostNotifyEvent(::mus::midi::player::ENotifyEvent eevent)
{
   if(m_pplayer != NULL)
   {
      ::mus::midi::player::NotifyEvent * pdata = new ::mus::midi::player::NotifyEvent;
      pdata->m_enotifyevent = eevent;
      m_pplayer->PostThreadMessage(
         midi_player::MessageNotifyEvent,
         0, 
         (LPARAM) pdata);      
   }
}

void midi_sequence_thread::Play(imedia::position tkStart)
{
   ASSERT(GetSequence() != NULL);
   ASSERT(GetSequence()->GetState() == ::mus::midi::sequence::StatusOpened);
   
   PrerollAndWait(tkStart);
   GetSequence()->Start();
}

void midi_sequence_thread::Play(double dRate)
{
   ASSERT(GetSequence() != NULL);
   ASSERT(GetSequence()->GetState() == ::mus::midi::sequence::StatusOpened);
   
   PrerollAndWait(dRate);
   GetSequence()->Start();
}


void midi_sequence_thread::PrerollAndWait(imedia::position tkStart)
{
   ::mus::midi::PREROLL                 preroll;
   
   preroll.tkBase = tkStart;
   preroll.tkEnd  = GetSequence()->m_tkLength;
   
   GetSequence()->SetMidiOutDevice(m_pplayer->GetMidiOutDevice());
   
   try
   {
      GetSequence()->Preroll(this, &preroll, true);
   }
   catch (midi_exception * pme)
   {
      string str;
      ASSERT(FALSE);

/* super merge module      CVmsMusDll::load_string(str, IDS_PREROLLUSERERROR001);
      pme->SetUserText(str);*/
      throw pme;
   }
   
}


void midi_sequence_thread::PrerollAndWait(double dRate)
{
   ::mus::midi::PREROLL                 preroll;
   
   gen::math::math::MaxClip(&dRate, 1.0);
   gen::math::math::MinClip(&dRate,  0.0);
   
   preroll.tkBase = (imedia::position) (int) ((double) GetSequence()->m_tkLength * dRate);
   preroll.tkEnd  = GetSequence()->m_tkLength;
   
   GetSequence()->SetMidiOutDevice(m_pplayer->GetMidiOutDevice());
   
   try
   {
      GetSequence()->Preroll(this, &preroll, true);
   }
   catch (midi_exception * pme)
   {
      throw not_implemented_exception();
      /*string str;
      str.load_string(IDS_PREROLLUSERERROR001);
      pme->SetUserText(str);*/
      throw pme;
   }
   
   //    if(!GetSequence()->IsInSpecialModeV001())
   //  {
   //    SendMessage(m_hWnd, WM_USER, 33, preroll.tkBase);
   //}
}


void midi_sequence_thread::PostGMReset()
{
   ASSERT(!GetSequence()->IsPlaying());
   GetSequence()->SetSpecialModeV001Operation(::mus::midi::sequence::SPMV001GMReset);
   PrerollAndWait(0.0);
   GetSequence()->Start();
   
}

void midi_sequence_thread::PostTempoChange()
{
   ASSERT(!GetSequence()->IsPlaying());
   GetSequence()->SetSpecialModeV001Operation(::mus::midi::sequence::SPMV001TempoChange);
   PrerollAndWait(0.0);
   GetSequence()->Start();
}

void midi_sequence_thread::SendTempoChange()
{
   ASSERT(!GetSequence()->IsPlaying());
   GetSequence()->m_evMmsgDone.ResetEvent();
   PostTempoChange();
   GetSequence()->m_evMmsgDone.wait();
}


void midi_sequence_thread::ExecuteCommand(::ca::smart_pointer < midi_player_command > spcommand)
{
   spcommand->add_ref();
   PostThreadMessage(
      MIDIPLAYERMESSAGE_COMMAND,
      0,
      (LPARAM) (midi_player_command *) spcommand);
}


void midi_sequence_thread::OnCommand(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   ::ca::smart_pointer < midi_player_command > spcommand;
   spcommand((midi_player_command *) pbase->m_lparam);
   try
   {
      _ExecuteCommand(spcommand);
   }
   catch(midi_exception * pe)
   {
      pe->Delete();
   }
   catch(...)
   {
   }
}


void midi_sequence_thread::_ExecuteCommand(::ca::smart_pointer < midi_player_command > spcommand)
{
   switch(spcommand->GetCommand())
   {
   case MidiPlayerCommandPlay:
      {
         if(spcommand->m_flags.is_signalized(midi_player_command::flag_dRate))
         {
            Play(spcommand->m_dRate);
         }
         else if(spcommand->m_flags.is_signalized(midi_player_command::flag_ticks))
         {
            Play(spcommand->m_ticks);
         }
         else 
         {
            Play();
         }
         spcommand->OnFinish();
      }
      break;
   case MidiPlayerCommandCloseDevice:
      {
         if(GetSequence() != NULL)
         {
            GetSequence()->CloseFile();
         }
         spcommand->OnFinish();
      }
      break;
   case MidiPlayerCommandStop:
      {
         m_eventStop.ResetEvent();
         MMRESULT            mmrc;
         ::mus::midi::sequence::PlayerLink & link = GetSequence()->GetPlayerLink();
         link.SetCommand(spcommand);
         link.ModifyFlag(::mus::midi::sequence::FlagStop, ::mus::midi::sequence::FlagNull);
         if(MMSYSERR_NOERROR != (mmrc = GetSequence()->Stop()))
         {
            throw new midi_exception(mmrc, MIDIPLAYERSTOPEXCEPTION);
         }
      }
      break;
   case MidiPlayerCommandStopAndRestart:
      {
         MMRESULT            mmrc;
         ::mus::midi::sequence::PlayerLink & link = GetSequence()->GetPlayerLink();
         link.SetCommand(spcommand);
         link.ModifyFlag(
            ::mus::midi::sequence::FlagStopAndRestart,
            ::mus::midi::sequence::FlagNull);
         link.m_tkRestart = GetSequence()->GetPositionTicks();
         if(MMSYSERR_NOERROR != (mmrc = GetSequence()->Stop()))
         {
            throw new midi_exception(mmrc, MIDIPLAYERSTOPEXCEPTION);
         }
      }
      break;
   }
}


