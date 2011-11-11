#include "StdAfx.h"

midi_player_callback_interface::midi_player_callback_interface(void)
{
}

midi_player_callback_interface::~midi_player_callback_interface(void)
{
}


void midi_player_callback_interface::OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd)
{
   UNREFERENCED_PARAMETER(pSeq);
   UNREFERENCED_PARAMETER(lpmdd);
}

void midi_player_callback_interface::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   UNREFERENCED_PARAMETER(pdata);
}

void midi_player_callback_interface::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   UNREFERENCED_PARAMETER(pevents);
}
