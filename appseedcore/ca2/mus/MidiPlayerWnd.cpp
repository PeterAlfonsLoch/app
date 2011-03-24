#include "StdAfx.h"

MidiPlayerWnd::MidiPlayerWnd(::ca::application * papp) :
   ca(papp)
{
   m_pcallback = NULL;
}

MidiPlayerWnd::~MidiPlayerWnd()
{
}

void MidiPlayerWnd::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::user::interaction::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(MMSG_DONE                        , pinterface, this, &MidiPlayerWnd::_001OnMmsgDone);
   IGUI_WIN_MSG_LINK(MidiPlayer::MessageNotifyEvent   , pinterface, this, &MidiPlayerWnd::_001OnNotifyEvent);
   IGUI_WIN_MSG_LINK(WM_USER                          , pinterface, this, &MidiPlayerWnd::_001OnUserMessage);
   IGUI_WIN_MSG_LINK(WM_APP + 3388                    , pinterface, this, &MidiPlayerWnd::_001OnApp3388Message);
}

void MidiPlayerWnd::_001OnMmsgDone(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(GetCallback() != NULL)
   {
      ::mus::midi::sequence * pseq = (::mus::midi::sequence *) pbase->m_wparam;
      ::mus::midi::LPMIDIDONEDATA lpmdd = (::mus::midi::LPMIDIDONEDATA) pbase->m_lparam;
   
   
      GetCallback()->OnMmsgDone(pseq, lpmdd);
      pbase->set_lresult(0);
   }
   else
   {
      pbase->set_lresult(-1);
   }
}

void MidiPlayerWnd::_001OnNotifyEvent(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   ::mus::midi::player::NotifyEvent * pdata = (::mus::midi::player::NotifyEvent *) pbase->m_lparam;
   if(GetCallback() != NULL)
   {
      GetCallback()->OnMidiPlayerNotifyEvent(pdata);
      pbase->set_lresult(0);
   }
   else
   {
      pbase->set_lresult(-1);
   }
   if(pdata != NULL)
      delete pdata;
}


MidiPlayerCallback * MidiPlayerWnd::GetCallback()
{
   return m_pcallback;
}

void MidiPlayerWnd::SetCallback(MidiPlayerCallback *pcallback)
{
   m_pcallback = pcallback;
}


bool MidiPlayerWnd::create()
{
   if(!create_message_window("ca2::music::::mus::midi::MidiPlayerWnd"))
   {
      return false;
   }
   return true;
}

void MidiPlayerWnd::_001OnUserMessage(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   switch(pbase->m_wparam)
   {
   case 3388:
      {
         // Lyric ::view Event 
         if(GetCallback() != NULL)
         {
            GetCallback()->OnMidiLyricEvent((base_array<LyricEventV1, LyricEventV1&> *) pbase->m_lparam);
            delete (base_array<LyricEventV1, LyricEventV1&> *) pbase->m_lparam;
         }
      }
      break;
   }
   pbase->set_lresult(0);
}

void MidiPlayerWnd::_001OnApp3388Message(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   MSG msg;

   while(PeekMessage(
      &msg,
      (HWND) get_wnd()->get_os_data(),
      WM_APP + 3388,
      WM_APP + 3388,
      PM_REMOVE))
   {
      if(pbase->m_wparam == 3388)
      {
         delete (base_array<LyricEventV1, LyricEventV1&> * ) pbase->m_lparam;
      }

      pbase->m_wparam = msg.wParam;
      pbase->m_lparam = msg.lParam;
   }
   switch(pbase->m_wparam)
   {
   case 3388:
      {
         // Lyric ::view Event 
         if(GetCallback() != NULL)
         {
            GetCallback()->OnMidiLyricEvent((base_array<LyricEventV1, LyricEventV1&> *) pbase->m_lparam);
            delete (base_array<LyricEventV1, LyricEventV1&> *) pbase->m_lparam;
         }
      }
      break;
   }

   pbase->set_lresult(0);
}

