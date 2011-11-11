#include "StdAfx.h"

midi_player_callback::midi_player_callback(::ca::application * papp) :
   m_wnd(papp)
{
}

midi_player_callback::~midi_player_callback()
{
}

bool midi_player_callback::initialize()
{
   if(!m_wnd.create())
      return false;
   m_wnd.SetCallback(this);
   return true;
}

bool midi_player_callback::finalize()
{
   if(!m_wnd.IsWindow())
      return true;
   m_wnd.DestroyWindow();
   return true;
}


void midi_player_callback::OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd)
{
   UNREFERENCED_PARAMETER(pSeq);
   UNREFERENCED_PARAMETER(lpmdd);
}

void midi_player_callback::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   switch(pdata->m_enotifyevent)
   {
   case ::mus::midi::player::NotifyEventSetSequence:
//      pdata->m_pplayer->GetSequence().m_midicallbackdata.hWnd = m_wnd.GetSafeHwnd();
      break;
   }
}

void midi_player_callback::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   UNREFERENCED_PARAMETER(pevents);
}