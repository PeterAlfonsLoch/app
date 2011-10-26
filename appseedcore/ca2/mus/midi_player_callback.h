#pragma once


class CLASS_DECL_ca midi_player_callback :
   virtual public midi_player_callback_interface
{
public:
   friend class midi_player_window;
   midi_player_window m_wnd;

   midi_player_callback(::ca::application * papp);
   virtual ~midi_player_callback();

   virtual bool initialize();
   virtual bool finalize();

   virtual void OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd);
   virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata); 
   virtual void OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents);
};
