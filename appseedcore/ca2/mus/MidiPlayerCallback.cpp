#include "StdAfx.h"

MidiPlayerCallback::MidiPlayerCallback(::ca::application * papp) :
   m_wnd(papp)
{
}

MidiPlayerCallback::~MidiPlayerCallback()
{
}

bool MidiPlayerCallback::initialize()
{
   if(!m_wnd.create())
      return false;
   m_wnd.SetCallback(this);
   return true;
}

bool MidiPlayerCallback::finalize()
{
   if(!m_wnd.IsWindow())
      return true;
   m_wnd.DestroyWindow();
   return true;
}


void MidiPlayerCallback::OnMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd)
{
   UNREFERENCED_PARAMETER(pSeq);
   UNREFERENCED_PARAMETER(lpmdd);
}

void MidiPlayerCallback::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   switch(pdata->m_enotifyevent)
   {
   case ::mus::midi::player::NotifyEventSetSequence:
//      pdata->m_pplayer->GetSequence().m_midicallbackdata.hWnd = m_wnd.GetSafeHwnd();
      break;
   }
}

void MidiPlayerCallback::OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents)
{
   UNREFERENCED_PARAMETER(pevents);
}