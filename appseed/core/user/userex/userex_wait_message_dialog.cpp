//#include "framework.h"


namespace userex // ca8 + cube
{


   wait_message_dialog::wait_message_dialog(::aura::application * papp) :
      object(papp),
      html_form(papp),
      dialog(papp)
   {

      m_dwStartTime = 0;

      m_dwDelay = 0;

   }


   wait_message_dialog::~wait_message_dialog()
   {

   }


   void wait_message_dialog::install_message_handling(::message::dispatch * pdispatch)
   {

      ::dialog::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &wait_message_dialog::_001OnCreate);

   }


   void wait_message_dialog::on_show(const char * pszMatter, property_set & propertyset)
   {

      UNREFERENCED_PARAMETER(pszMatter);

      UNREFERENCED_PARAMETER(propertyset);

   }


   void wait_message_dialog::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == 5432175)
      {

         on_timeout_check();

      }

   }


   void wait_message_dialog::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if(m_dwDelay > 0)
      {
         
         SetTimer(5432175, 50, NULL);

      }

      m_dwStartTime = ::get_tick_count();

      m_pdocument = get_document();

   }


   bool wait_message_dialog::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         m_strResponse = pevent->m_puie->m_id;

         EndModalLoop(IDOK);

      }

      return false;

   }


   bool wait_message_dialog::on_timeout_check()
   {
      
      uint32_t dwTimeout = ::get_tick_count() - m_dwStartTime;

      if (dwTimeout > m_dwDelay)
      {

         if (on_timeout())
         {

            EndModalLoop(IDOK);

            return true;

         }

      }
      else
      {

         on_timer_soft_reload(dwTimeout);

      }

      return false;

   }


   bool wait_message_dialog::on_timeout()
   {
      
      m_strResponse = "timeout";

      return true;

   }


   void wait_message_dialog::on_timer_soft_reload(uint32_t dwTimeout)
   {
      
      ::user::interaction * pui = get_child_by_id("timeout");
      
      if (pui != NULL)
      {

         string str;

         str.Format("%d", (int32_t)((m_dwDelay - dwTimeout) / 1000));

         pui->_001SetText(str, ::action::source_sync);

      }

      if (m_pdocument != NULL)
      {

         m_pdocument->oprop("wait_message_dialog_timeout") = (int32_t)((m_dwDelay - dwTimeout) / 1000);

         //m_pdocument->soft_reload();

      }

   }


} // namespace userex // ca8 + cube





