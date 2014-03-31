#include "framework.h"

form_view::form_view(sp(base_application) papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form(papp),
   html_form(papp),
   html_form_view(papp)
{
   m_pcallback = NULL;
}


void form_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
{

   html_form_view::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      form_update_hint * puh = dynamic_cast < form_update_hint * > (phint);
      if(puh != NULL)
      {
         if(puh->m_etype == form_update_hint::type_browse)
         {
            if(!puh->m_strForm.is_empty())
            {
               string str;
               str = Application.dir().matter(puh->m_strForm);
               if(get_document()->on_open_document(str))
               {
                  m_strPath = puh->m_strForm;
               }
            }
         }
         else if(puh->m_etype == form_update_hint::type_get_form_view)
         {
            puh->m_pformview = this;
         }
      }
      else
      {
         html_view_update_hint * puh = dynamic_cast < html_view_update_hint * > (phint);
         if(puh != NULL)
         {
            if(puh->m_etype == html_view_update_hint::type_document_complete)
            {
               for(int32_t i = 0; i < get_html_data()->m_propertyset.m_propertya.get_count(); i++)
               {
                  html::elemental * pelemental = get_html_data()->get_element_by_id(get_html_data()->m_propertyset.m_propertya[i].name());
                  if(pelemental != NULL)
                  {
                     pelemental->set_string(get_html_data()->m_propertyset.m_propertya[i].get_string(), ::action::source_data);
                  }
               }
            }

            {

               sp(::draw2d::graphics) dc(allocer());

               dc->CreateCompatibleDC(NULL);

               get_html_data()->implement(dc);

            }
            
         }

      }

   }

   if(m_pcallback != NULL)
   {

      m_pcallback->on_update(this, pSender, lHint, phint);

   }

}


bool form_view::BaseOnControlEvent(::user::control_event * pevent)
{
   if(m_pcallback != NULL)
   {
      if(m_pcallback->BaseOnControlEvent(
         this,
         pevent))
         return true;
   }
   else if(get_html_data()->m_pform != NULL
      && get_html_data()->m_pform->m_pcallback != NULL)
   {
      if(get_html_data()->m_pform->m_pcallback->BaseOnControlEvent(
         this,
         pevent))
         return true;
   }
   if(form::BaseOnControlEvent(pevent))
      return true;
   return false;
}

void form_view::install_message_handling(::message::dispatch * pinterface)
{
   html_form_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &form_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &form_view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_USER + 123, pinterface, this, &form_view::_001OnUser123);

}


void form_view::_001OnCreate(signal_details * pobj)
{
   pobj->previous();
}


void form_view::_001OnTimer(signal_details * pobj)
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

void form_view::_001OnUser123(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_wparam == 0x80000001)
   {
      if(GetTopLevelParent() != NULL)
      {
         GetTopLevelParent()->EndModalLoop(IDOK);
      }
      return;
   }
   if(m_pcallback != NULL)
   {
      m_pcallback->OnUser123(pbase->m_wparam, pbase->m_lparam);
   }
}
