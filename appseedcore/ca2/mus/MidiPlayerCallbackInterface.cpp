#include "StdAfx.h"

MidiPlayerCallbackInterface::MidiPlayerCallbackInterface(void)
{
}

MidiPlayerCallbackInterface::~MidiPlayerCallbackInterface(void)
{
}


void MidiPlayerCallbackInterface::OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd)
{
   UNREFERENCED_PARAMETER(pSeq);
   UNREFERENCED_PARAMETER(lpmdd);
}

void MidiPlayerCallbackInterface::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   UNREFERENCED_PARAMETER(pdata);
}

void MidiPlayerCallbackInterface::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   UNREFERENCED_PARAMETER(pevents);
}
