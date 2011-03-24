#pragma once


class CLASS_DECL_ca MidiPlayerInterface :
   public MidiPlayerCallback,
   virtual public ::radix::object
{
public:
   
   
   midi_central *       m_pcentral;
   MidiPlayer   *         m_pmidiplayer;


   MidiPlayerInterface(::ca::application * papp);
   virtual ~MidiPlayerInterface();

   
   virtual ::radix::thread * GetMidiPlayerCallbackThread() = 0;
   virtual ::mus::midi::sequence & GetMidiSequence() = 0;
   virtual bool OnOpenMidiPlayer();
   MidiPlayer * GetMidiPlayer();


   virtual bool Initialize(midi_central * pcentral);
   virtual bool Finalize();


   bool OpenMidiPlayer();
   void MusicTempoMinus();
   void MusicTempoReset();
   void MusicUpdateTransposeMinusTone(cmd_ui * pcmdui);
   void MusicUpdateTransposePlusTone(cmd_ui * pcmdui);
   void MusicUpdateTransposeReset(cmd_ui * pcmdui);
   void MusicUpdateTransposePlus(cmd_ui * pcmdui);
   void MusicUpdateTransposeMinus(cmd_ui * pcmdui);
   void MusicUpdateTempoMinus(cmd_ui * pcmdui);
   void MusicUpdateTempoPlus(cmd_ui * pcmdui);
   void MusicUpdateTempoReset(cmd_ui * pcmdui);
   void MusicTransposeMinusTone();
   void MusicTransposePlusTone();
   void MusicTransposeReset();
   void MusicTransposePlus();
   void MusicTransposeMinus();
   void MusicTempoPlus();


   virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata); 

   virtual void OnChangeMidiPlayerTranspose();
   virtual void OnChangeMidiPlayerTempoShift();

};

