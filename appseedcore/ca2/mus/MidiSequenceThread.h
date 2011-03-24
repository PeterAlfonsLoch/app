#pragma once

#define MIDISEQUENCEMESSAGE_EVENT WM_USER + 30

class CLASS_DECL_ca MidiSequenceThread : 
   public ::radix::thread
{
public:
   MidiSequenceThread(::ca::application * papp);

   MidiPlayer *      m_pplayer;     
   ::mus::midi::sequence *    m_psequence;
   CEvent            m_eventStop;

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

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

   void ExecuteCommand(MidiPlayerCommand * pcommand);
   void _ExecuteCommand(MidiPlayerCommand * pcommand);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual ~MidiSequenceThread();

   DECL_GEN_SIGNAL(OnCommand)
   DECL_GEN_SIGNAL(OnMidiSequenceEvent)

};
