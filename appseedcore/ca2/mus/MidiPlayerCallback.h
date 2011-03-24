#pragma once


class CLASS_DECL_ca MidiPlayerCallback :
   public MidiPlayerCallbackInterface
{
public:
   friend class MidiPlayerWnd;
   MidiPlayerWnd m_wnd;

   MidiPlayerCallback(::ca::application * papp);
   virtual ~MidiPlayerCallback();

   virtual bool initialize();
   virtual bool finalize();

   virtual void OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd);
   virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata); 
   virtual void OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents);
};
