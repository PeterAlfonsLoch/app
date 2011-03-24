#include "StdAfx.h"

namespace veiev
{

   configuration::configuration(::ca::application * papp) :
      ca(papp)
   {
      m_pdoc   = NULL;
      m_pview  = NULL;
   }

   configuration::~configuration()
   {
   }

   bool configuration::initialize(::user::interaction * puiParent)
   {
      m_pdoc = Application.create_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
         return true;
      }
      return false;
   }

   void configuration::on_show(const char * pszEmail)
   {

      m_strEmail = pszEmail;
      
      if(!m_pdoc->on_open_document(System.dir().matter("mail/configuration.xhtml")))
      {
         return;
      }

      ::user::interaction * pguie = m_pview->GetChildByName("mail_server");
      text_interface * ptext = dynamic_cast < text_interface * > (pguie);
      string strUrl = System.url().set("https://fontopus.com/get_user_string", "key" , "mail_server");
      strUrl = System.url().set(strUrl, "user" , m_strEmail);
      ptext->_001SetText(System.http().get(strUrl));

      pguie = m_pview->GetChildByName("mail_login");
      ptext = dynamic_cast < text_interface * > (pguie);
      strUrl = System.url().set("https://fontopus.com/get_user_string", "key" , "mail_login");
      strUrl = System.url().set(strUrl, "user" , m_strEmail);
      ptext->_001SetText(System.http().get(strUrl));

   }

   bool configuration::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            ::user::interaction * pguie = m_pview->GetChildByName("mail_server");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            string str;
            ptext->_001GetText(str);
            string strUrl = System.url().set("https://fontopus.com/set_user_string", "key" , "mail_server");
            strUrl = System.url().set(strUrl, "user" , m_strEmail);
            strUrl = System.url().set(strUrl, "value" , str);
            str = System.http().get(strUrl);
            ptext->_001SetText(str);

            pguie = m_pview->GetChildByName("mail_login");
            ptext = dynamic_cast < text_interface * > (pguie);
            ptext->_001GetText(str);
            strUrl = System.url().set("https://fontopus.com/set_user_string", "key" , "mail_login");
            strUrl = System.url().set(strUrl, "user" , m_strEmail);
            strUrl = System.url().set(strUrl, "value" , str);
            str = System.http().get(strUrl);
            ptext->_001SetText(str);


            ::fontopus::validate validate(get_app(), "");

            pguie = m_pview->GetChildByName("mail_password");
            ptext = dynamic_cast < text_interface * > (pguie);
            ptext->_001GetText(str);
            System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), m_strEmail, "license_auth/00003"), str, validate.calc_ca2_hash());
         }
      }
      return false;
   }

} // namespace veiev