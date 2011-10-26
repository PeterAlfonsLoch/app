#pragma once

class CLASS_DECL_ca midi_player_callback_interface :
   virtual public ::radix::object
{
public:


   midi_player_callback_interface(void);
   virtual ~midi_player_callback_interface(void);

   virtual void OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd);
   virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pevent); 
   virtual void OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents);

};
