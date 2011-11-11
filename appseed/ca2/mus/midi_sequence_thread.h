#pragma once

#define MIDISEQUENCEMESSAGE_EVENT WM_USER + 30

class CLASS_DECL_ca midi_sequence_thread : 
   public ::radix::thread
{
public:
   midi_sequence_thread(::ca::application * papp);

   midi_player *                 m_pplayer;     
   ph(::mus::midi::sequence)     m_psequence;
   event                        m_eventStop;

   void install_message_handling(::user::win::message::dispatch * pinterface);

   ::mus::midi::sequence * GetSequence();
   void Stop(DWORD dwEllapse);

   BOOL PostMidiSequenceEvent(
      ::mus::midi::sequence * pseq,
      ::mus::midi::sequence::e_event event);

   BOOL PostMidiSequenceEvent(
      ::mus::midi::sequence * pseq,
      ::mus::midi::sequence::e_event event,
      LPMIDIHDR lpmh);

   void PostNotifyEvent(::mus::midi::player::ENotifyEvent eevent);

   void PrerollAndWait(double rate = 0.0);
   void PrerollAndWait(imedia::position tkStart);
   void Play(double dRate = 0.0);
   void Play(imedia::position tkStart);
   void PostGMReset();
   void PostTempoChange();
   void SendTempoChange();

   void ExecuteCommand(::ca::smart_pointer < midi_player_command > pcommand);
   void _ExecuteCommand(::ca::smart_pointer < midi_player_command > pcommand);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual ~midi_sequence_thread();

   DECL_GEN_SIGNAL(OnCommand)
   DECL_GEN_SIGNAL(OnMidiSequenceEvent)

};
