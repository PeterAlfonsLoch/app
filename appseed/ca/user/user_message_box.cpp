#include "framework.h"

message_box::message_box(::ca::application * papp) :
   ca(papp)/*,
   dialog(papp)*/,
   wait_message_dialog(papp)
{
}

void message_box::on_show(const char * pszMatter, gen::property_set & propertyset)
{
   if(!propertyset.has_property("application_name"))
      propertyset["application_name"] = System.m_strAppName;
   if(propertyset.has_property("simple_message_box_timeout_ms"))
   {
      m_dwDelay = propertyset.has_property("simple_message_box_timeout_ms");
      if(m_dwDelay > 0)
      {
//         m_pdocument->get_html_data()->m_propertyset["simple_message_box_timeout"] = (int) (m_dwDelay / 1000);
      }
   }
   wait_message_dialog::on_show(pszMatter, propertyset);
}

bool message_box::on_timeout()
{
   m_strResponse = "ok";
   return wait_message_dialog::on_timeout();
}

void message_box::on_timer_soft_reload(DWORD dwTimeout)
{
   //m_pdocument->get_html_data()->m_propertyset["simple_message_box_timeout"] = (int) ((m_pdocument->get_html_data()->m_propertyset["simple_message_box_timeout_ms"]) / 1000);
   wait_message_dialog::on_timer_soft_reload(dwTimeout);
}
