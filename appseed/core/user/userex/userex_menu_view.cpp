#include "framework.h"


menu_view::menu_view(sp(::aura::application) papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form_interface(papp),
   ::user::form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
   m_pcallback = NULL;
}


void menu_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint) 
{
   form_view::on_update(pSender, lHint, phint);
}


bool menu_view::BaseOnControlEvent(::user::control_event * pevent)
{
   if(m_pcallback != NULL)
   {
      m_pcallback->BaseOnControlEvent(
         this,
         pevent);
   }
   else if(get_html_data()->m_pform != NULL
     && get_html_data()->m_pform->m_pcallback != NULL)
   {
      get_html_data()->m_pform->m_pcallback ->BaseOnControlEvent(
         this,
         pevent);
   }
   if(GetParent() != NULL)
   {
      return GetParent()->BaseOnControlEvent(pevent);
   }
   else
   {
      return false;
   }
}

void menu_view::install_message_handling(::message::dispatch * pinterface)
{
   form_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &menu_view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_USER + 123, pinterface, this, &menu_view::_001OnUser123);

}


void menu_view::_001OnCreate(signal_details * pobj)
{
   pobj->previous();
}


void menu_view::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer, ptimer, pobj);
   if(m_pcallback != NULL)
   {
      ::user::control_event ev;
      ev.m_eevent = ::user::event_timer;
      ev.m_uiEvent = ptimer->m_nIDEvent;
      m_pcallback->BaseOnControlEvent(this, &ev);
   }
   if(ptimer->m_nIDEvent == 24)
   {
      KillTimer(24);
      GetTopLevelFrame()->EndModalLoop(IDOK);
   }
}

void menu_view::_001OnUser123(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_wparam == 0x80000001)
   {
      GetTopLevel()->EndModalLoop(IDOK);
      return;
   }
   if(m_pcallback != NULL)
   {
      m_pcallback->OnUser123(pbase->m_wparam, pbase->m_lparam);
   }
}